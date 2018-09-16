/* RIFF stands for Resource Interchangange File Format */
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

const string file_name_0 = "383940.wav";
const string file_name_1 = "../Klocuch/klocych.wav";

bool read_characters(ifstream& wave, int how_many,
		string label, bool print = true)
{
	char* characters = new char[how_many];
	for(int i=0; i< how_many; i++)
		wave >> characters[i];

	if (print)
		cout << label 
			<<":\t" << characters << endl;

	return wave.good();
}

bool read_characters_and_compare(ifstream& wave, int how_many,
		string label, string pattern,  bool print = true)
{
	char* characters = new char[how_many];
	for(int i=0; i< how_many; i++)
		wave >> characters[i];

	if (print)
		cout << label 
			<<":\t" << characters << endl;

	bool characters_same_as_pattern = true;
	int len_of_pattern = pattern.length();
	for(int i=0; i < len_of_pattern; i++)
		if( pattern[i] != characters[i]) 
		{
			characters_same_as_pattern = false;
			break;
		}

	return characters_same_as_pattern;
}

uint32_t get_four_byte_int(ifstream& wave)
{
	uint8_t* input = new uint8_t[4];

	for(int i=0; i < 4; i++)
		wave >> input[i];

	uint32_t number = 0;
    number  = input[3] << 24;
	number |= input[2] << 16;
   	number |= input[1] << 8;
   	number |= input[0];

	return number;
}

uint16_t get_two_byte_int(ifstream& wave)
{
	uint8_t* input = new uint8_t[2];

	for(int i=0; i < 2; i++)
		wave >> input[i];

	uint16_t number = 0;
   	number |= input[1] << 8;
   	number |= input[0];

	return number;
}


/* Main starts here */
/* Main starts here */
/* Main starts here */
/* Main starts here */

int main(int argc, char** argv){
	/* pick one of two slightly different files */
	string file_name;
	if( argc > 1)
		file_name = file_name_0;
	else
		file_name = file_name_1;

	bool print_data = true;
	if(argc == 3)
		print_data = false;

	cout << "Dear sound!" << endl;
	cout << "Here I display the content of " << file_name << endl;
	cout << endl;

	ifstream is( file_name, ios::binary );
	if( is.is_open() )
	{
		is >> noskipws;
		bool all_good = true;

		// "RIFF" chunk descriptor data
		uint32_t file_size;
		all_good &= read_characters(is, 4, "ChunkID");
		file_size = get_four_byte_int(is);
		cout << "File size:\t" << file_size << endl;
		all_good &= read_characters(is, 4, "Format\t");
		file_size -= 4;

		// "fmt" sub-chunk 
		cout << endl << endl;
		all_good &= read_characters(is, 4, "Subchunk1ID");
		file_size -= 4;

		uint32_t subchunk1_size = get_four_byte_int(is);
		cout << "Subchunk1 size:\t" << subchunk1_size << endl;
		file_size -= 4;

		uint16_t audio_format = get_two_byte_int(is);
		cout << "Audio format:\t" << audio_format << endl;
		file_size -= 2;
		subchunk1_size -= 2;
		
		uint16_t num_channels = get_two_byte_int(is);
		cout << "No of Channels:\t" << num_channels << endl;
		file_size -= 2;
		subchunk1_size -= 2;

		uint32_t sample_rate = get_four_byte_int(is);
		cout << "Sample rate:\t" << sample_rate << endl;
		file_size -= 4;
		subchunk1_size -= 4;

		// byte_rate = SampleRate * NumChannels * BitsPerSample/8
		uint32_t byte_rate = get_four_byte_int(is);
		cout << "Byte rate:\t" << byte_rate << endl;
		file_size -= 4;
		subchunk1_size -= 4;

		// block_align = Num_channels * BitsPerSample/8
		uint16_t block_align = get_two_byte_int(is);
		cout << "Block align:\t" << block_align << endl;
		file_size -= 2;
		subchunk1_size -= 2;

		uint16_t bits_per_sample = get_two_byte_int(is);
		cout << "Bits per sample:\t" << bits_per_sample << endl;
		file_size -= 2;
		subchunk1_size -= 2;

		cout << "Remaining size of sub-chunk 1:\t" 
			<< subchunk1_size << endl << endl << endl;

		// "data" sub-chunk 
		bool supported = read_characters_and_compare(is, 4, "Subchunk2ID",
				"data");
		file_size -= 4;

		if(!supported)
		{
			cout << "The file format is not supported." << endl;
			cout << "Only data with Subchunk2ID equal to data is supported"
				<< endl;
			return 0;
		}

		uint32_t subchunk2_size = get_four_byte_int(is);
		cout << "Sub-chunk 2 size:\t" << subchunk2_size << endl;
		file_size -= 4;
		cout << "remaining file size:\t" << file_size << endl;

		cout << endl << endl;
		cout << "Now there will be printed all data" << endl;
		cout << "Sample No\t left channel\tright channel" << endl;

		int data_samples = subchunk2_size/num_channels/bits_per_sample*8;
		if(bits_per_sample == 16 && num_channels == 2)
		{
			uint16_t left_channel;
			uint16_t right_channel;
			for(int j = 0; j < data_samples; j++)
			{
				left_channel =  get_two_byte_int(is);
				right_channel =  get_two_byte_int(is);
				if(print_data)
					cout << j << "\t"
						<< bitset<16>(left_channel) << "\t"
						<< bitset<16>(right_channel) << endl;
			}
			file_size -= 4*data_samples;
			subchunk2_size -= 4*data_samples;
			cout << endl << endl << "End of data" << endl;
			cout << "remaining sub-chunk 2 size:\t" 
				<< subchunk2_size << endl;
			cout << "remaining file size:\t" << file_size << endl;
		}

		is.close();
	}
	else 
		cout << "Cannot open " << file_name << endl;

	return 0;
}


/*
 * Deprecated functions
 */
bool read_RIFF(ifstream& wave, bool print = true)
{
	char RIFF[4];
	for(int i=0; i<4; i++)
		wave >> RIFF[i];

	if (print)
		cout << "Chunk ID:\t" << RIFF << endl;

	return wave.good();
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
