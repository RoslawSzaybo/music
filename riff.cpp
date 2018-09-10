#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

const string file_name_0 = "383940.wav";
const string file_name_1 = "../Klocuch/klocych.wav";


bool read_RIFF(ifstream& wave, bool print = true)
{
	char RIFF[4];
	for(int i=0; i<4; i++)
		wave >> RIFF[i];

	if (print)
		cout << "Chunk ID:\t" << RIFF << endl;

	return wave.good();
}


uint32_t get_file_size(ifstream& wave)
{
	/* for 383940.wav this bytes are
	11011100 11011000 00001100 00000000
 	*/
	uint8_t* input = new uint8_t[4];

	for(int i=0; i < 4; i++)
		wave >> input[i];

	/* debug
	for(int i=0; i <4; i++)
		cout << bitset<8>(input[3-i]) << "\t";
	cout << endl;
	*/

	int32_t file_size = 0;
    file_size  = input[3] << 24;
	file_size |= input[2] << 16;
   	file_size |= input[1] << 8;
   	file_size |= input[0];

	return file_size;
}

bool read_WAVE(ifstream& wave, bool print = true)
{
	char* WAVE = new char[4];
	for(int i=0; i<4; i++)
		wave >> WAVE[i];

	if (print)
		cout << "WAVE:\t\t" << WAVE << endl;

	return wave.good();
}

int main(int argc, char** argv){
	string file_name;
	if( argc == 2)
		file_name = file_name_0;
	else
		file_name = file_name_1;

	cout << "Dear sound!" << endl;
	cout << "Here I display the content of " << file_name << endl;
	cout << endl;

	ifstream is( file_name, ios::binary );
	if( is.is_open() )
	{
		uint32_t file_size;
		is >> noskipws;
		read_RIFF(is);
		file_size = get_file_size(is);
		cout << "File size:\t" << file_size << endl;
		read_WAVE(is);
		is.close();
	}
	else 
		cout << "Cannot open " << file_name << endl;

	return 0;
}
