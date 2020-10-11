#include <iostream>
#include <fstream>

using namespace std;

/*
* Блок описания констант
*/

#define BASE 16
#define BLOCK_LENGTH 4
#define LINE_COUNT 100
#define BLOCK_COUNT 25

/*
* Блок описания типов
*/

using block = char[BLOCK_LENGTH];

struct partOfNum
{
	unsigned char count;
	
};

struct number
{
	bool sign;
	partOfNum inter;
	partOfNum fact;
};









int main() {
	ifstream fout;
	fout.open("inp");

	//cout << __cplusplus << endl;

	fout.close();
	return 0;
}