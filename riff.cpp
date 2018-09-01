#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string file_name = "383940.wav";

int read_RIFF(ifstream& wave, bool print = true)
{
	char* RIFF = new char[4];
	for(int i=0; i<4; i++)
		wave >> RIFF[i];

	int cksize = 0;

	if (print)
	{
		cout << "Chunk ID:\t" << RIFF << endl;
	}

	return  cksize;
}

int main(int argc, char** argv){
	cout << "Dear sound!" << endl;

	cout << "Here I display the content of " << file_name << endl;
	cout << endl;

	ifstream is( file_name, ios::binary );
	if( is.is_open() )
		read_RIFF( is );
	else 
		cout << "Cannot open " << file_name << endl;

	return 0;
}
