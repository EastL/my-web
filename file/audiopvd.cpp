#include <iostream>
#include <string>
#include <cstdlib>
#include <sndfile.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int size;
SF_INFO Info;
short *buffer;
int num_item;
short *buffer_left;
short *buffer_right;

void snd_read(char input[]);
void snd_write(char output[]);
void hide_message(string Message);
string Tobinary(string str);
void testlsb();
void pvd_message(string str);
void spread();
int classify(int data);

int main (int argc, char **argv)
{
    snd_read(argv[1]);

    string message;
    //cout << "please input the message:\n";
    //cin >> message;

    //cout << Info.format << ' ' << Info.sections << ' ' << Info.seekable << endl;
    testlsb();
    //hide_message(message);
    //spread();
    snd_write(argv[2]);
    return 0;
}

void snd_read(char input[])
{
    SNDFILE *InputAudio;

    InputAudio = sf_open (input, SFM_READ, &Info);
    if (InputAudio == NULL)
        cout << "Failed to open the file !!" << endl;
    
    num_item = Info.frames * Info.channels;
    buffer = (short *)malloc(num_item * sizeof (short));
    size = sf_read_short (InputAudio, buffer, num_item);

    sf_close(InputAudio);
}

void snd_write(char output[])
{
    SNDFILE *OutputAudio;
    OutputAudio = sf_open (output, SFM_WRITE, &Info);
    
    sf_write_short(OutputAudio, buffer, num_item);
    sf_close(OutputAudio);   
}

void hide_message(string Message)
{
    string stream = Tobinary(Message);
    //cout << stream;
    for(int i = 0; i < stream.size(); i++)
    {
        if(stream[i] == '1')
            if(buffer[i] % 2 == 0)
                buffer[i] += 1;
        else
            if(buffer[i] % 2 == 1)
                buffer[i] -= 1;
    }
}

string Tobinary(string str)
{
    string binary;
    for(int i = 0; i < str.size(); i++)
    {
        bool temp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        int make = str[i];
        int j = 8;
        while(make >= 2)
        {
            j--;
            temp[j] = make % 2;
            make /= 2;
        }
        temp[j-1] = make;
        
        for(int k = 0; k < 8; k++)
            binary.push_back(temp[k]);
    }

    for(int i = 0; i < binary.size(); i++)
        binary[i] += 48;
    return binary;
}

void testlsb()
{
    for(int i = 0; i < size; i++)
        buffer[i] |= 63;
}

void pvd_message(string str)
{
    string message = Tobinary(str);

    for(int index = 0; index < size; index += 2)
    {
        int diff = buffer[index+1] - buffer[i], classify_group;
        if(diff < 0)
            classify_group = -diff;
        else
            classify_group = diff;

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
            case 7:
                    BIT = 8;
                    Lk = 256;
                    break;
            case 8:
                    BIT = 9;
                    Lk = 512;
                    break;
            case 9:
                    BIT = 10;
                    Lk = 1024;
                    break;
            case 10:
                    BIT = 11;
                    Lk = 2048;
                    break;
            case 11:
                    BIT = 12;
                    Lk = 4096;
                    break;
            case 12:
                    BIT = 13;
                    Lk = 8192;
                    break;
            case 13:
                    BIT = 14;
                    Lk = 16384;
                    break;
            case 14:
                    BIT = 15;
                    Lk = 32768;
                    break;
        }

    }
}

void spread()
{
    buffer_left = (short *)malloc(num_item * sizeof(short) / 2);
    buffer_right = (short *)malloc(num_item * sizeof(short) / 2);
     
    for(int i = 0; i < size / 2; i++)
        buffer_left[i] = buffer[i*2];

    for(int i = 0; i < size / 2; i++)
        buffer_right[i] = buffer[i*2 + 1];
}

int classify(int data)
{
    if(data >= 0 && data <= 7)
        return 1;
    else if(data >= 8 && data <= 15)
        return 2;
    else if(data >= 16 && data <= 31)
        return 3;
    else if(data >= 32 && data <= 63)
        return 4;
    else if(data >= 64 && data <= 127)
        return 5;
    else if(data >= 128 && data <= 255)
        return 6;
    else if(data >= 256 && data <= 511)
        return 7;
    else if(data >= 512 && data <= 1023)
        return 8;
    else if(data >= 1024 && data <= 2047)
        return 9;
    else if(data >= 2048 && data <= 4095)
        return 10;
    else if(data >= 4096 && data <= 8191)
        return 11;
    else if(data >= 8192 && data <= 16383)
        return 12;
    else if(data >= 16384 && data <= 32767)
        return 13;
    else if(data >= 32768 && data <= 65535)
        return 14;
}
