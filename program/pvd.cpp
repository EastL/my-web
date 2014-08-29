#include <iostream>
#include "read.h"
#include "write.h"
#include <Cmath>
#include <string>
#include <vector>

using namespace std;

struct pixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

int classify(int data)
{
	if(data >=0 && data <= 7)
		return 1;
	if(data >=8 && data <= 15)
		return 2;
	if(data >=16 && data <= 31)
		return 3;
	if(data >=32 && data <= 63)
		return 4;
	if(data >=64 && data <= 127)
		return 5;
	if(data >=128 && data <= 255)
		return 6;
}

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

	//2D→1D

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

	//pvd steganography
	string pvd_message;
	cout << "Please input the secret message:";
	cin >> pvd_message;
	cout << endl;

	//check 
	int message_size = pvd_message.size() * 8;
	int pic_size = bmp.get_Width() * bmp.get_Height() * 9;
	if(message_size > pic_size)
	{
		cout << "message 檔案太大\n";
		exit(0);
	}
	
	//char to binary
	vector<bool> binary_message;
	for(int i = 0; i < pvd_message.size(); i++)
	{
		bool temp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		int make = pvd_message[i];
		int index = 8;
		while (make >= 2)
		{
			index--;
			temp[index] = make % 2;
			make /= 2;
		}
		temp[index - 1] = make;

		for(int j = 0; j < 8; j++)
			binary_message.push_back(temp[j]);
	}

	//start pvd
	int BinMessCount = 0; // 記錄binary message位置
	//像素兩兩一組
	for(int i = 0; i < pix_dir.size(); i+=2)
	{
		
		//計算差值
		int diff = pix_dir[i+1] - pix_dir[i], classify_group;
		if(diff < 0)
			classify_group = -diff;
		else
			classify_group = diff;
		//依照差值分類
		int K = classify(classify_group);
		int BIT, Lk;
		switch(K)
		{
			case 1:
				BIT = 3;
				Lk = 0;
				break;
			case 2:
				BIT = 3;
				Lk = 8;
				break;
			case 3:
				BIT = 4;
				Lk = 16;
				break;
			case 4:
				BIT = 5;
				Lk = 32;
				break;
			case 5:
				BIT = 6;
				Lk = 64;
				break;
			case 6:
				BIT = 7;
				Lk = 128;
				break;
		}

		//將對應的bit數轉成10進位
		int dec/*存取轉好的10進位訊息*/, nowBMC = BinMessCount;
		vector<bool> tempBinMes;//暫時存取2進位的訊息

		//檢查是否為最後一筆藏入資訊(須做特殊處理)
		int remain = binary_message.size() - BinMessCount;
		if(remain < BIT)
		{
			for(;BinMessCount < binary_message.size(); BinMessCount++)
				tempBinMes.push_back(binary_message[BinMessCount]);
			break;
		}

		for(;BinMessCount < nowBMC + BIT; BinMessCount++)
			tempBinMes.push_back(binary_message[BinMessCount]);
		
		BinMessCount++;//讓下一次從還未藏入的位置開始

		int sum = 0;
		for(int j = 0; j < tempBinMes.size(); j++)
			sum += pow(2,tempBinMes.size() - 1.0 - j) * tempBinMes[j];		//將2進為轉為10進位(2^n * k)
		dec = sum + Lk;	//加上該區間的下限值
		if(diff < 0)
			dec = -dec;
		cout << (int)pix_dir[i] << ' ' << (int)pix_dir[i+1] << endl;
		//平均分配到像素質上
		int NewOldDiff = dec - diff;
		if(NewOldDiff % 2 == 0)
		{
			pix_dir[i] -= NewOldDiff / 2;
			pix_dir[i+1] += NewOldDiff / 2;
		}
		else
		{
			if( NewOldDiff > 0)
			{
				pix_dir[i] -= NewOldDiff / 2 + 1;
				pix_dir[i+1] += NewOldDiff / 2;
			}
			else
			{
				pix_dir[i] -= NewOldDiff / 2 - 1;
				pix_dir[i+1] += NewOldDiff / 2;
			}
		}

		//test
		/*cout << K << ' ' << diff << ' ' << dec << endl;
		cout << (int)pix_dir[i] << ' ' << (int)pix_dir[i+1] << endl;
		cout << endl;*/
	}

	//1D→2D
	int pix_dir_count = -1;
	for(int i = 0; i < bmp.get_Width(); i++)
		for(int j = 0; j < bmp.get_Height(); j++)
		{
			pix[i][j].red = pix_dir[++pix_dir_count];
			pix[i][j].green = pix_dir[++pix_dir_count];
			pix[i][j].blue = pix_dir[++pix_dir_count];
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