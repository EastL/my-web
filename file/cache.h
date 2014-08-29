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

//�]�w�򥻦r���ഫ��K�{�����g
#define total_size "cache_size:"			
#define block_size "cache_block_size:"
#define ways "#_cache_ways:"
#define set "#_cache_sets:"
#define lines "#_cache_lines:"
#define tag_bit "#_tag_bits:"

//function prototype
void InputToValue(string fn);		//�Ninput file���ȥ��۹����ѼơAinput�ɦW���Ĥ@�ӰѼ�
void MapToSet();					//�p��Xset���h��
void MissHit();						//�P�_miss�٬Ohit
void OutputToFile(string on);
bool check_command(int num);		//�]�����{���ݭn�Ψ�command line����A�ȨϥΪ̫��O���~�ӳ]�p
int SwitchString(string strname);	//�w�q�r�ꪺ�N�X�A��Kswitch��
int Tobit(int n);					//�N�Ʀr�ରbit��
string HexTobin(char hex);			//�N�Q���i�쪺�r���ഫ��4 bit binary�r��
void RemovePoper(int remove);		//�N�ǰe�i�Ӫ����Ӧ�m�qpoper������

struct memory;

//�N�򥻰ѼƳ]��global
string CacheSize, CacheBlockSize;		//��ܥ�
int cache_size;							//�p���	
int cache_block_size;
int cache_sets;
int cache_lines;
int cache_ways;
int offset_bit;
int index_bit;
int tag_bits;
bool ways_check;		//�P�_�쥻��cache_ways�쩳�O���O0
vector<memory> cache_memory, poper;	//�x�s�C��address���A

struct memory		//�C��memory�]�taddress, miss or hit, set�T��member
{
	string address;		//address �W��
	string misshit;		//0��miss 1��hit
	int sets;		//���ݩ����set
};