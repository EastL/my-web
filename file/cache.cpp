#include <iostream>
#include "cache.h"

int main(int argc, char **argv)
{
	bool excute = check_command(argc);	//�T�{�O�_��cmd����
	if (!excute)
		exit(0);		//�p�G�ѼƤ��ŦX�W�w�h����{��

	InputToValue(argv[1]);	//�Ninput file���ȥ��۹����ѼơAinput�ɦW���Ĥ@�ӰѼ�
	
	cache_lines = cache_size / cache_block_size;	//�p��cache_lines�Acache_sets�Atag_bits
	cache_sets = cache_lines / cache_ways;
	offset_bit = Tobit(cache_block_size);
	index_bit = Tobit(cache_sets);
	tag_bits = 32 - offset_bit - index_bit;

	MapToSet();		//�p��Xset���h��
	MissHit();		//�P�_miss�٬Ohit

	OutputToFile(argv[2]);		//�N���G��ܦb�ĤG�ӰѼƪ��ɮ׸�(�o���ɦW���s�b�S���Y�A���|�۰ʳХX�ɮ�)

	return 0;
}

void InputToValue(string fn)
{
	ifstream pname(fn);	//�}���ɮ�
	string str;		//�N��Ū�쪺�C�@�泣�x�s��str

	while(getline(pname,str))
	{
		int t_count = 0;
		string name, temp_value;	//�C�@�������Ӱ϶��G�W�r���

		for (int i = 0; i < str.size(); i++)	//�h���ťյM��N�e�����������W�r��
		{
			if (str[i] != ' ')
				name += str[i];
			if (str[i] == ' ' && name.size() != 0)
			{
				t_count = i;
				break;
			}
		}
		
		for (int i = t_count; i < str.size(); i++)	//�ѤU�����N�Ovalue
			if (str[i] != ' ')
				temp_value += str[i];
		//���N���㪺��F�s�n�A��K��X
		if (SwitchString(name) == 1) CacheSize = temp_value;
		if (SwitchString(name) == 2) CacheBlockSize = temp_value;

		//��cache_size��cache_block_size�h�����
		string temp;
		int diff = 1;//�p�G�u��B�N��B�h��
		if (name == total_size || name == block_size)
		{
			if (temp_value[temp_value.size() - 2] == 'K' || temp_value[temp_value.size() - 2] == 'k')
				diff = 2;//�p�G�OKB�N�n�h�����		
			for (int i = 0; i < temp_value.size() - diff; i++)
				temp += temp_value[i];
		}
		memory t_memory;
		switch (SwitchString(name))//�N�W�r�Ωw�q�n���N�X�������Ʊ�
		{
			case 1://catche_size�A�P�_�OKB�٬OByte�A�M��N�e�����r���ର�Ʀr
					if (diff == 1)	//string��int
						cache_size = atoi(temp.c_str());
					if (diff == 2)
						cache_size = 1024 * atoi(temp.c_str());	//1024�O����ഫ

					break;
			case 2:
					//block_size���w�]�u��Byte
					cache_block_size = atoi(temp.c_str());break;
			case 3:	//cache_ways�¼Ʀr
				cache_ways = atoi(temp_value.c_str());break;
			case 4://cache memory
				t_memory.address = name;
				cache_memory.push_back(t_memory);
		}
	}

	if (cache_ways == 0)		// #_cache_ways: �� 0 �ɥN��direct mapped
	{
		cache_ways = 1;
		ways_check = 1;
	}
	else ways_check = 0;
	pname.close();
}

void MapToSet()
{
	for (int i = 0; i < cache_memory.size(); i++)
	{
		string binary;		//address�ഫ��binary string
		for (int j = 2; j < cache_memory[i].address.size(); j++)
			binary += HexTobin(cache_memory[i].address[j]);

		int dec_set = 0;		//���Xcatch index�ô��⦨�Q�i��
		for (int j = tag_bits + index_bit - 1, k = 1; j >= tag_bits ; j--, k *= 2)
			 dec_set += (binary[j] - 48) * k;		//�q�̫�@��}�l���e�A��K�q2�i�촫��10�i��

		cache_memory[i].sets = dec_set;		//�ᵹmemory struct
	}
}

void MissHit()
{
	for (int i = 0; i < cache_memory.size(); i++)
	{
		bool sameornot = false;	//�w�]��miss���A
		for (int j = 0; j < poper.size(); j++)		//�}�l��poper�̭����S���@�˪�address
			if (cache_memory[i].address == poper[j].address)	
			{
				sameornot = true;		//�����ܴN�Ohit
				break;
			}

		if (sameornot)		//��nstruct�̭��Ѽƪ��A
			cache_memory[i].misshit = "hit";
		else
			cache_memory[i].misshit = "miss";

		int set_num = 0, Remove;		//�Naddress��i��
		for (int j = 0; j < poper.size(); j++)
		{
			if (cache_memory[i].sets == poper[j].sets)
			{	
				set_num ++;
				if (set_num == 1) Remove = j;		//�O���Ĥ@��set����m
				if (set_num == 2)					//�p�G����Ӫ��ܭn�N�o�Ӧ�m������
				{
					RemovePoper(Remove);
					break;
				}
			}
		}

		poper.push_back(cache_memory[i]);		//�Naddress��i��
	}
}

void OutputToFile(string on)
{
	if (ways_check)		//�쥻input��cache_ways�O0���ܳo��]�n�O0
		cache_ways = 0;

	ofstream fout(on);
	//�}�l��X���G
	fout << total_size << ' ' << CacheSize << endl
		 << block_size << ' ' << CacheBlockSize << endl
		 << set << ' ' << cache_sets << endl
		 << lines << ' ' << cache_lines << endl
		 << ways << ' ' << cache_ways << endl
		 << tag_bit << ' ' << tag_bits << endl;

	fout << endl;

	fout << "memory trace results:" << endl;

	for (int i = 0; i < cache_memory.size(); i++)
		fout << cache_memory[i].address << " map to set " 
		<< cache_memory[i].sets << ' ' << cache_memory[i].misshit << endl;

	fout.close();
}

bool check_command(int num)
{
	if (num == 1)		//�u���@�ӰѼƥN��user�������榹�ɮ�
	{
		cout << "�Х�command line���� :" << endl			//�����ϥΪ̥�cmd�Ӱ��榹�{��
		<< "\t�Ĥ@�ӰѼƬ���������" << endl 
		<< "\t�ĤG�ӰѼƬ�input��" << endl 
		<< "\t�ĤT�ӰѼƬ�output��" << endl;

		return 0;
	}
	if (num != 3 && num != 1)		//�ϥΪ̤U���Ѽƪ��p
	{
		cout << "command line�е��q�T�ӰѼ�" << endl;
		return 0;
	}
	if (num == 3)		//���T�Ѽ����i����
		return 1;
}

int SwitchString(string strname)			//�w�q�r�ꪺ�N�X�A��Kswitch��
{
	if(strname.size() > 0)
	{
		if (strname == total_size)
			return 1;
		else if (strname == block_size)
			return 2;
		else if (strname == ways)
			return 3;
		else if (strname[0] == '0' && strname[1] == 'x')
			return 4;
		else return 0;
	}
	else
		return 0;
}

int Tobit(int n)		//�N�Ʀr�ରbit��
{
	int num = 0;
	while (n != 1)
	{
		n /= 2;
		num++;
	}

	return num;
}

string HexTobin(char hex)		//�N�@�Ӧr���ഫ��4bit string
{
	int dec;	//���r�����Ʀr���A
	if (hex <= 'F' && hex >= 'A')	//A~F�ҥ~�B�z
	{
		if (hex == 'A')	dec = 10;
		if (hex == 'B')	dec = 11;
		if (hex == 'C')	dec = 12;
		if (hex == 'D')	dec = 13;
		if (hex == 'E')	dec = 14;
		if (hex == 'F')	dec = 15;
	}

	else		//�Ʀr���ܥ�ascii
		dec = hex - 48;

	string bitstring;		//�x�s2�i��string
	bool temp[4] = {0, 0, 0, 0};
	int index = 4;
	while (dec != 0)
	{
		index--;
		temp[index] = dec % 2;
		dec /= 2;
	}
	
	for (int i = 0; i < 4; i++)		//4 bit string
		bitstring.push_back(temp[i] + 48);

	return bitstring;
}

void RemovePoper(int remove)
{
	vector<memory> temp;
	//�e�b�q��itemp
	for(int i = 0; i < remove - 1; i++)
		temp.push_back(poper[i]);
	//��b�q��itemp
	for(int i = remove + 1; i < poper.size(); i++)
		temp.push_back(poper[i]);
	//���N���쥻��poper
	poper = temp;
}