#include <iostream>
#include "read.h"
#include "write.h"
#include <math.h>
#include <string>
#include <vector>


using namespace std;


struct pixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

int main( int argc, char **argv )
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
	//work

	string message;
	cin >> message;
	for(int index = 0; index < message.length(); index++)
	{
		bool temp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		int make = message[index];
		int i = 8;
		while (make >= 2)
		{
			i--;
			temp[i] = make % 2;
			make /= 2;
		}
		temp[i - 1] = make;
		int testindex = index * 4;
		for(int j = testindex, k = 0; j < testindex + 4; j++, k += 2)
		{
			int hide = temp[k] * 2 + temp[k+1];
			pix[0][j].red += hide;
		}
	}


	//write
	SaveBMP new_bmp(argv[2]);
	new_bmp.initBMP(bmp.get_Width(), bmp.get_Height());

	for(int i = 0; i < bmp.get_Width(); i++)
		for(int j = 0; j < bmp.get_Height(); j++)
			new_bmp.put_pixel(i, j, pix[i][j].red | (pix[i][j].green << 8) | (pix[i][j].blue << 16));

	new_bmp.Save();
	return 0;
}