#include <iostream>
#include "cache.h"

int main(int argc, char **argv)
{
	bool excute = check_command(argc);	//確認是否用cmd執行
	if (!excute)
		exit(0);		//如果參數不符合規定則停止程式

	InputToValue(argv[1]);	//將input file的值丟到相對應參數，input檔名為第一個參數
	
	cache_lines = cache_size / cache_block_size;	//計算cache_lines，cache_sets，tag_bits
	cache_sets = cache_lines / cache_ways;
	offset_bit = Tobit(cache_block_size);
	index_bit = Tobit(cache_sets);
	tag_bits = 32 - offset_bit - index_bit;

	MapToSet();		//計算出set為多少
	MissHit();		//判斷miss還是hit

	OutputToFile(argv[2]);		//將結果顯示在第二個參數的檔案裡(這邊檔名不存在沒關係，它會自動創出檔案)

	return 0;
}

void InputToValue(string fn)
{
	ifstream pname(fn);	//開啟檔案
	string str;		//將來讀到的每一行都儲存為str

	while(getline(pname,str))
	{
		int t_count = 0;
		string name, temp_value;	//每一行分成兩個區塊：名字跟值

		for (int i = 0; i < str.size(); i++)	//去掉空白然後將前面的部分塞到名字裡
		{
			if (str[i] != ' ')
				name += str[i];
			if (str[i] == ' ' && name.size() != 0)
			{
				t_count = i;
				break;
			}
		}
		
		for (int i = t_count; i < str.size(); i++)	//剩下部分就是value
			if (str[i] != ' ')
				temp_value += str[i];
		//先將完整的表達存好，方便輸出
		if (SwitchString(name) == 1) CacheSize = temp_value;
		if (SwitchString(name) == 2) CacheBlockSize = temp_value;

		//做cache_size跟cache_block_size去掉單位
		string temp;
		int diff = 1;//如果只有B就把B去掉
		if (name == total_size || name == block_size)
		{
			if (temp_value[temp_value.size() - 2] == 'K' || temp_value[temp_value.size() - 2] == 'k')
				diff = 2;//如果是KB就要去掉兩個		
			for (int i = 0; i < temp_value.size() - diff; i++)
				temp += temp_value[i];
		}
		memory t_memory;
		switch (SwitchString(name))//將名字用定義好的代碼分類做事情
		{
			case 1://catche_size，判斷是KB還是Byte，然後將前面的字串轉為數字
					if (diff == 1)	//string轉int
						cache_size = atoi(temp.c_str());
					if (diff == 2)
						cache_size = 1024 * atoi(temp.c_str());	//1024是單位轉換

					break;
			case 2:
					//block_size單位預設只有Byte
					cache_block_size = atoi(temp.c_str());break;
			case 3:	//cache_ways純數字
				cache_ways = atoi(temp_value.c_str());break;
			case 4://cache memory
				t_memory.address = name;
				cache_memory.push_back(t_memory);
		}
	}

	if (cache_ways == 0)		// #_cache_ways: 為 0 時代表direct mapped
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
		string binary;		//address轉換成binary string
		for (int j = 2; j < cache_memory[i].address.size(); j++)
			binary += HexTobin(cache_memory[i].address[j]);

		int dec_set = 0;		//取出catch index並換算成十進位
		for (int j = tag_bits + index_bit - 1, k = 1; j >= tag_bits ; j--, k *= 2)
			 dec_set += (binary[j] - 48) * k;		//從最後一位開始往前，方便從2進位換算10進位

		cache_memory[i].sets = dec_set;		//丟給memory struct
	}
}

void MissHit()
{
	for (int i = 0; i < cache_memory.size(); i++)
	{
		bool sameornot = false;	//預設為miss狀態
		for (int j = 0; j < poper.size(); j++)		//開始找poper裡面有沒有一樣的address
			if (cache_memory[i].address == poper[j].address)	
			{
				sameornot = true;		//有的話就是hit
				break;
			}

		if (sameornot)		//填好struct裡面參數狀態
			cache_memory[i].misshit = "hit";
		else
			cache_memory[i].misshit = "miss";

		int set_num = 0, Remove;		//將address丟進來
		for (int j = 0; j < poper.size(); j++)
		{
			if (cache_memory[i].sets == poper[j].sets)
			{	
				set_num ++;
				if (set_num == 1) Remove = j;		//記錄第一個set的位置
				if (set_num == 2)					//如果有兩個的話要將這個位置給移除
				{
					RemovePoper(Remove);
					break;
				}
			}
		}

		poper.push_back(cache_memory[i]);		//將address丟進來
	}
}

void OutputToFile(string on)
{
	if (ways_check)		//原本input檔cache_ways是0的話這邊也要是0
		cache_ways = 0;

	ofstream fout(on);
	//開始輸出結果
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
	if (num == 1)		//只有一個參數代表user直接執行此檔案
	{
		cout << "請用command line執行 :" << endl			//提醒使用者用cmd來執行此程式
		<< "\t第一個參數為此執行檔" << endl 
		<< "\t第二個參數為input檔" << endl 
		<< "\t第三個參數為output檔" << endl;

		return 0;
	}
	if (num != 3 && num != 1)		//使用者下錯參數狀況
	{
		cout << "command line請給訂三個參數" << endl;
		return 0;
	}
	if (num == 3)		//正確參數應可執行
		return 1;
}

int SwitchString(string strname)			//定義字串的代碼，方便switch用
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

int Tobit(int n)		//將數字轉為bit數
{
	int num = 0;
	while (n != 1)
	{
		n /= 2;
		num++;
	}

	return num;
}

string HexTobin(char hex)		//將一個字元轉換成4bit string
{
	int dec;	//此字元的數字型態
	if (hex <= 'F' && hex >= 'A')	//A~F例外處理
	{
		if (hex == 'A')	dec = 10;
		if (hex == 'B')	dec = 11;
		if (hex == 'C')	dec = 12;
		if (hex == 'D')	dec = 13;
		if (hex == 'E')	dec = 14;
		if (hex == 'F')	dec = 15;
	}

	else		//數字的話用ascii
		dec = hex - 48;

	string bitstring;		//儲存2進位string
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
	//前半段丟進temp
	for(int i = 0; i < remove - 1; i++)
		temp.push_back(poper[i]);
	//後半段丟進temp
	for(int i = remove + 1; i < poper.size(); i++)
		temp.push_back(poper[i]);
	//取代掉原本的poper
	poper = temp;
}