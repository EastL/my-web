#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> //socket
#include <sys/socket.h> //socket
#include <arpa/inet.h> //htons htonl
#include <netinet/in.h> //inet_aton
#include <unistd.h> //close
#include <pthread.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	struct sockaddr_in si_receiver, si_sender;
	si_receiver.sin_family = AF_INET;
	si_receiver.sin_port = htons(atoi(argv[1]));
	si_receiver.sin_addr.s_addr = htonl(INADDR_ANY);

	int sfd_receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP), si_sender_len = sizeof(si_sender);

	bind(sfd_receiver, (struct sockaddr*)&si_receiver, sizeof(si_receiver));

	char recv_buffer[MAX_BUFFER_SIZE];
	char bit_str[MAX_BUFFER_SIZE];
	int mask = 0x8000;
	int bit_count = 0;
	int i,j;
	
	while(recvfrom(sfd_receiver, recv_buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&si_sender, (socklen_t*)&si_sender_len))
	{
		short secret = ntohs(si_sender.sin_port);
		char temp_bit[16];
		int bpd;

		for(i = 0; i < 16; i++)
			temp_bit[i] = (secret & (mask >> i)) >> (15 - i);
		if(temp_bit[0] == 0 && temp_bit[1] == 1) bpd = 4;
		else if(temp_bit[0] == 1 && temp_bit[1] == 0) bpd = 8;
		else if(temp_bit[0] == 1 && temp_bit[1] == 1) bpd = 12;

		for(i = 16 - bpd; i < 16; i++)
		{
			bit_str[bit_count] = temp_bit[i];
			bit_count++;
		}

		if(temp_bit[0] == 0 && temp_bit[1] == 0)
		{
			char *byte_str = (char*)malloc(bit_count / 8 * sizeof(char));

			for(i = 0; i < bit_count / 8 - 1; i++)
			{
				char d = 0;
				for(j = 0; j < 8; j++)
					d = (d << 1) | bit_str[i * 8 + j];
				byte_str[i] = d;
			}

			printf("message: %s\n", byte_str);
		}
	}

	return 0;
}
