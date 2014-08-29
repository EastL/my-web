#include <iostream>
#include <string>

using namespace std;

int main()
{

	string input, code;

	cout << "message:";
	cin >> input;
	cout << "key:";
	cin >> code;

	string table, rtable;
	for(int i = 0; i < 26; i++)
		table.push_back(65+i);
	
	for(int i = 0; i < code.size(); i++)
	{
		bool tag = 0;
		for(int j = 0; j < rtable.size(); j++)
			if(rtable[j] == code[i])
				tag = 1;
		if(!tag)
			rtable.push_back(code[i]);
	}

	char the_char = 'A';
	for(int i = rtable.size(); i < 26;)
	{
		bool tag = 0;
		for(int j = 0; j < code.size(); j++)
			if(code[j] == the_char)
				tag = 1;

		if(tag)
			the_char++;
		else
		{
			rtable.push_back(the_char);
			the_char++;
			i++;
		}
	}
	cout << "the table:\t" << table << endl;

	cout << "the key table:\t" << rtable << endl;
	int usr_com = 0;
	cout << "What do you want to do ?[1(for Ecryption)/2(for Decryption)]" << endl;
	cin >> usr_com;
	string answer;
	switch(usr_com)
	{
	case 1:
		for(int i = 0; i < input.size(); i++)
		{
			int p = input[i] - 65;
			answer.push_back(rtable[p]);
		}

		cout << "Ecryption:";
		break;
	case 2:
		for(int i = 0; i < input.size(); i++)
		{
			int p;
			for(int j = 0; j < 26; j++)
				if(rtable[j] == input[i])
				{
					p = j;
					break;
				}
			answer.push_back(table[p]);
		}
		cout << "Decryption:";
	}
	cout << endl << answer << endl;
	return 0;
}
