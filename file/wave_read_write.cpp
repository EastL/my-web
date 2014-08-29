/*wav_read_write.cpp
Author: K. L. Srinivas
Problem statement :
1. opens a wav file for reading; opens another wav file for writing
2. detects the samp. rate and #samples from the header of input wav

Next, we wish to read in sequentially blocks of data from the wav file
for processing one block ("frame") at a time.

In the loop (until last frame):
 3. reads in the data (16-bit integers) in blocks of BUFSIZE samples
 4. dummy processing()
 5. writes out BUFSIZE output samples in the output wav file
end loop
*/

// This program is tested on linux machine with g++ compiler.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// WAVE PCM soundfile format (you can find more in https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ )
typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;




int main()

{
	FILE * infile = fopen("machali_male.wav","rb");		// Open wave file in read mode
	FILE * outfile = fopen("Output.wav","wb");		// Create output ( wave format) file in write mode

	int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)
	int count = 0;						// For counting number of frames in wave file.
	short int buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
	int nb;							// variable storing number of byes returned
	if (infile)
	{
		fread(meta, 1, sizeof(header), infile);
		fwrite(meta,1, sizeof(*meta), outfile);
		cout << " Size of Header file is "<<sizeof(*meta)<<" bytes" << endl;
		cout << " Sampling rate of the input wave file is "<< meta->sample_rate <<" Hz" << endl;
		cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << endl;



		while (!feof(infile))
		{
			nb = fread(buff16,1,BUFSIZE,infile);		// Reading data in chunks of BUFSIZE
			//cout << nb <<endl;
			count++;					// Incrementing Number of frames

			/* Insert your processing code here*/

			fwrite(buff16,1,nb,outfile);			// Writing read data into output file
		}
	cout << " Number of frames in the input wave file are " <<count << endl;
	}
return 0;
}
