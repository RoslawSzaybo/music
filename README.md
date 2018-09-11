# Music

Here I will practice what I learned abut audio formats.

First one is .wav. Specification that I realy on is available here http://soundfile.sapp.org/doc/WaveFormat/ for free. I looks like this format just contains a series of amplitudes of selected sines.


The first four bytes of .wav file are 4 ASCII letters RIFF.
I read them with the use of ifsteam (http://www.cplusplus.com/doc/tutorial/files/).

	#include <fstream>

	char* RIFF = new char[4];

	ifstream wave(file_name, ios::binary);
	if( wave.is_open() )
	{
		for( int i=0; i < 4; i++ )
			wave >> RIFF[i];
	}

Here is a reportedly good approach to read bytes:
https://en.cppreference.com/w/cpp/iterator/istreambuf_iterator

