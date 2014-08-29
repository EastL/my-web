#include <fstream>
#include <string>
#include <vector>

using std::cin; 
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::vector;

//設定基本字串轉換方便程式撰寫
#define total_size "cache_size:"			
#define block_size "cache_block_size:"
#define ways "#_cache_ways:"
#define set "#_cache_sets:"
#define lines "#_cache_lines:"
#define tag_bit "#_tag_bits:"

//function prototype
void InputToValue(string fn);		//將input file的值丟到相對應參數，input檔名為第一個參數
void MapToSet();					//計算出set為多少
void MissHit();						//判斷miss還是hit
void OutputToFile(string on);
bool check_command(int num);		//因為此程式需要用到command line執行，怕使用者指令錯誤而設計
int SwitchString(string strname);	//定義字串的代碼，方便switch用
int Tobit(int n);					//將數字轉為bit數
string HexTobin(char hex);			//將十六進位的字元轉換成4 bit binary字串
void RemovePoper(int remove);		//將傳送進來的那個位置從poper中移除

struct memory;

//將基本參數設為global
string CacheSize, CacheBlockSize;		//顯示用
int cache_size;							//計算用	
int cache_block_size;
int cache_sets;
int cache_lines;
int cache_ways;
int offset_bit;
int index_bit;
int tag_bits;
bool ways_check;		//判斷原本的cache_ways到底是不是0
vector<memory> cache_memory, poper;	//儲存每個address狀態

struct memory		//每個memory包含address, miss or hit, set三個member
{
	string address;		//address 名稱
	string misshit;		//0為miss 1為hit
	int sets;		//隸屬於哪個set
};