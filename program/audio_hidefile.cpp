#include <iostream>
#include <string>
#include <cstdlib>
#include <sndfile.h>
#include <math.h>
#include <fstream>

#define header_size 10 

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

int size;
SF_INFO Info;
short *buffer;
int num_item;
short *buffer_left;
short *buffer_right;

void snd_read(char input[]);
void snd_write(char output[]);
string Tobinary(string str);
void pvd(string str);
int classify(int data);
string set_header(string str);

int main (int argc, char **argv)
{
    snd_read(argv[2]);

    //Hide message
    if(argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == 'm')
    {
        string message;
        cout << "please input the message:\n";
        getline(cin, message);
        pvd(message);
        snd_write(argv[3]);
    }

    //Hide file
    else if(argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == 'f')
    {
        string temp, str;
        ifstream file(argv[3], ios::in);
        
        while(getline(file, temp))
            str += temp;
        pvd(str);
        file.close();
        snd_write(argv[4]);
    }

    //retrieve message
    else if(argv[1][0] == '-' && argv[1][1] == 'x' && argv[1][2] == 'm')
    {
        
    }
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

string set_header(string str)
{
    int s_size = str.size();
    string t_set;

    while(s_size > 0)
    {
        t_set += s_size % 2;
        s_size /= 2;
    }
    
    int zero_set = header_size - t_set.size();
    string set;

    for(int i = 0; i < zero_set; i++)
        set += '0';
    for(int i = t_set.size() - 1; i >= 0; i--)
        set += t_set[i] + 48;
    set += str;

    return set;
}

void pvd(string str)
{
    string t_message = Tobinary(str);
    string message = set_header(t_message);

    int message_count = 0;

    for(int i = 0; i < message.size(); i++)
        cout << message[i];
    cout << endl;
    for(int index = 0; index < size; index += 2)
    {
        int diff = buffer[index+1] - buffer[index], classify_group;
        bool end = 0;
        if(diff < 0)
            classify_group = -diff;
        else
            classify_group = diff;

        int K = classify(classify_group);
        int BIT, Lk;
        //classfy into 14 interval
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
        
        //calculate message value
        int dec = 0, Bcount;
     
        if(message.size() - message_count <= BIT)
        {    
            Bcount = message.size() - message_count;
            end = 1;
        }
        else
            Bcount = BIT;
        //cout << Bcount << ' ';
        for(; Bcount > 0 ; Bcount--)
        {
            dec += pow(2, Bcount - 1) * (message[message_count] - 48);
            message_count ++;
        }

        cout << "original:" << buffer[index] << ' ' << buffer[index+1] << endl;

        dec += Lk;    //add low bound
        if(diff < 0) dec = -dec;

        cout << "o:" << diff << endl << "b:" << dec << endl;
        int NewOldDiff = dec - diff, forward = buffer[index], back = buffer[index+1];
        //if(buffer[index] < 0) NewOldDiff = -NewOldDiff;
        
        cout << "different:" << NewOldDiff << endl;
        if(NewOldDiff % 2 == 0)
        {
            forward -= NewOldDiff / 2;
            back += NewOldDiff / 2;
            
            /*if(forward < -32768)
            {
                back -= -32768 - forward;
                forward = -32768;
            }
    
            if(forward > 65535)
            {
                back -= forward - 65535;
                forward = 65535;
            }

            if(back < 0)
            {
                forward -= back;
                back = 0;
            }

            if(back > 65535)
            {
                forward -= back - 65535;
                back = 65535;
            }*/
        }

        else
	{
	    if(NewOldDiff >= 0)
	    {
	        forward -= NewOldDiff / 2 + 1;
		back += NewOldDiff / 2;

		/*if(forward < 0)
		{
		    back -= forward;
		    forward = 0;
		}
	
		if(forward > 65535)
		{
		    back -= forward - 65535;
		    forward = 65535;
		}

		if(back < 0)
		{
		    forward -= back;
		    back = 0;
		}

		if(back > 65535)
		{
		    forward -= back - 65535;
		    back = 65535;
		}*/		
	    }
	    
	    else
	    {
	        forward -= NewOldDiff / 2 - 1;
		back += NewOldDiff / 2;

		/*if(forward < 0)
		{
		    back -= forward;
		    forward = 0;
		}
	
		if(forward > 65535)
		{
		    back -= forward - 65535;
		    forward = 65535;
		}

		if(back < 0)
		{
		    forward -= back;
		    back = 0;
		}

		if(back > 65535)
		{
		    forward -= back - 65535;
		    back = 65535;
		}*/
	    }   
	}   

        buffer[index] = forward;
        buffer[index+1] = back;
        cout << "before:" << buffer[index] << ' ' << buffer[index+1] << endl;
        cout << endl;
        if(end) break;
    }
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
