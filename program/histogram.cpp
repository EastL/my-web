#include <iostream>
#include "read.h"
#include <Cmath>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct pixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

int main(int argc, char **argv )
{
	//read
	LoadBMP bmp(argv[1]);
	
	vector<vector<pixel>> pix;
	for (unsigned int i = 0 ; i < bmp.get_Width(); i++)
	{
		vector<pixel> temp;
		for (unsigned int j = 0 ; j < bmp.get_Height(); j++)
		{
			pixel t_pixel;
			t_pixel.red = (bmp.get_pixel(i,j)& 0xff);
			t_pixel.green = (bmp.get_pixel(i,j)& 0xff00) >> 8;
			t_pixel.blue = (bmp.get_pixel(i,j)& 0xff0000) >> 16;
			temp.push_back(t_pixel);
		}
		pix.push_back(temp);
	}

	//2D¡÷1D

	int pix_size = bmp.get_Width() * bmp.get_Height() * 3;

	vector<unsigned char> pix_dir;
	for(int i = 0; i < bmp.get_Width(); i++)
		for(int j = 0; j < bmp.get_Height(); j++)
		{
			pix_dir.push_back(pix[i][j].red);
			pix_dir.push_back(pix[i][j].green);
			pix_dir.push_back(pix[i][j].blue);
		}
	
	//work
	//red
	int Rsum[255 * 2 + 1] = {0};
	for(int i = 0; i < pix_dir.size(); i+=6)
	{
		int diff = pix_dir[i+3] - pix_dir[i];
		for(int j = 0; j < 255 * 2 + 1; j++)
		{
			if((diff + 255) == j)
				Rsum[j] ++;
		}
	}
	fstream Rtxt;
	Rtxt.open(argv[2],ios::out);

	Rtxt << "This is Red PD histogram." << endl << endl;
	for(int i = 0; i < 255*2+1; i++)
		Rtxt << i - 255 << '\t' << Rsum[i] << endl;
	Rtxt.close();

	//green
	int Gsum[255 * 2 + 1] = {0};
	for(int i = 1; i < pix_dir.size(); i+=6)
	{
		int diff = pix_dir[i+3] - pix_dir[i];
		for(int j = 0; j < 255 * 2 + 1; j++)
		{
			if((diff + 255) == j)
				Gsum[j] ++;
		}
	}

	fstream Gtxt;
	Gtxt.open(argv[3],ios::out);

	Gtxt << "This is Green PD histogram." << endl << endl;
	for(int i = 0; i < 255*2+1; i++)
		Gtxt << i - 255 << '\t' << Gsum[i] << endl;
	Gtxt.close();

	//blue
	int Bsum[255 * 2 + 1] = {0};
	for(int i = 2; i < pix_dir.size(); i+=6)
	{
		int diff = pix_dir[i+3] - pix_dir[i];
		for(int j = 0; j < 255 * 2 + 1; j++)
		{
			if((diff + 255) == j)
				Bsum[j] ++;
		}
	}

	fstream Btxt;
	Btxt.open(argv[4],ios::out);

	Btxt << "This is Blue PD histogram." << endl << endl;
	for(int i = 0; i < 255*2+1; i++)
		Btxt << i - 255 << '\t' << Bsum[i] << endl;
	Btxt.close();
	return 0;
}