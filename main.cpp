#include <iostream>
#include <fstream>
#include <valarray>
#include <cstring>

using namespace std;

/*
 * Блок описания констант
 *
 * BASE - основание СС
 * BLOCK_LENGTH - длинна блока
 * BLOCK_COUNT - количиство блоков в числе
 * LINE_COUNT - количество обрабатываемых строк
 *
*/

#define BASE 16
#define BLOCK_LENGTH 4
#define BLOCK_COUNT 25
#define LINE_COUNT 100

#define INPUT_FILE_NAME "/home/aleksei/Projects/lab1/inp"
#define OUTPUT_FILE_NAME "oup"


#pragma region types

/*
 * Блок описания типов
 *
*/

using block_t = char[BLOCK_LENGTH+1];

struct partOfNum
{
	int count;
	block_t blocks[BLOCK_COUNT];
};

struct number
{
	bool sign;
	partOfNum inter;
	partOfNum fact;
};

#pragma endregion types

#pragma region general_functions

/*
 * Блок описания внутренних функций
 *
*/


int getDigitWeight(char CDigit)
{
	/*
	 * Функция получает для каждой цифры типа char ее вес в int
	*/
	
	// TODO
	
}

char getDigitRepr(int IDigit)
{
	/*
	 *
	*/
	
	// TODO
	
}

#pragma endregion general_functions


#pragma region block_functions

/*
 * Блок описания функций работы с блоками
 *
*/


block_t* blockAdd(block_t term1, block_t term2, bool &transfer)
{
	/*
	 * Функция складывает блоки term1 и term2 с переносом transfer
	 * если transfer = true, то к результату сложения блоков прибавляется еденица
	 * если происходит переполнение блока, то transfer = true
	*/
	
	// TODO
	
}

block_t* blockSub(block_t min, block_t sub, bool &transfer)
{
	/*
	 * Функция вычитает из блока min блок sub с заемом transfer
	 * если transfer = true, то из результата сложения блоков вычитается еденица
	 * если происходит недостаток блока, то transfer = true
	*/
	
	// TODO
	
}

#pragma endregion block_functions


#pragma region part_number_functions

/*
 * Блок описания функций для работы с частяли чисел
 *
*/

partOfNum addInter(partOfNum term1, partOfNum term2, bool transfer)
{
	/*
	 * Функция для сложения целых частей чисел
	*/
	
	// TODO
	
}

partOfNum subInter(partOfNum min, partOfNum sub, bool transfer)
{
	/*
	 * Функция для вычитания целых частей чисел
	*/
	
	// TODO
	
}

partOfNum addFact(partOfNum term1, partOfNum term2, bool transfer)
{
	/*
	 * Функция для сложения дробных частей чисел
	*/
	
	// TODO
	
}

partOfNum subFact(partOfNum min, partOfNum sub, bool transfer)
{
	/*
	 * Функция для вычитания дробных частей чисел
	*/
	
	// TODO
	
}


#pragma endregion part_number_functions


#pragma region abs_number_functions

/*
 * Блок описания функций для работы с модулями чисел
 *
*/

number addAbs(number term1, number term2)
{
	/*
	 * Функция сложения модулей чисел
	*/
	
	// TODO
	
}

number subAbs(number min, number sub)
{
	/*
	 * Функция вычитания модулей чисел
	*/
	
	// TODO
	
}

void normalize(number &numb)
{
	/*
	 * Функция реформатирования числа (пересчет количества блоков)
	*/
	
	// TODO
	
}


#pragma endregion abs_number_functions


#pragma region number_functions

/*
 * Блок описания функций для работы с числами
 *
*/

number addNum(number term1, number term2)
{
	/*
	 * Функция сложения чисел
	*/
	
	// TODO
	
}

number subNum(number min, number sub)
{
	/*
	 * Функция вычитания чисел
	*/
	
	// TODO
	
}

number readNum(string numb, bool &Error)
{
	/*
	 * Функция считывания числа
	*/
	//if ()
	
	
	
	
	// TODO
}

number printNum(number numb)
{
	/*
	 * Функция вывода числа
	*/
	
	cout << (numb.sign ? '-' : '+');
	// cout << numb.inter.count << '/';
	for (int i = numb.inter.count; i >= 0 ; --i)
	{
		cout << numb.inter.blocks[i];
	}
	cout << '.';
	// cout << numb.fact.count << '/';
	for (int i = numb.fact.count; i >= 0 ; --i)
	{
		cout << numb.fact.blocks[i];
	}
	cout  << endl;
	
	//TODO не зависит от count
}

#pragma endregion number_functions


int main() {
	ifstream inpFile;
	inpFile.open(INPUT_FILE_NAME);
	
	string line;
	
	
	cout << "Ваша версия страндарта языка: " << __cplusplus << endl;
	

	getline(inpFile, line, '\n');
	
	
	
	
	/*using block_t = char[BLOCK_LENGTH];

struct partOfNum
{
	unsigned char count;
	block_t blocks[BLOCK_COUNT];
};

struct number
{
	bool sign;
	partOfNum inter;
	partOfNum fact;
};*/
	
	number n = {true, {2, {"5678", "1234", "1234"}}, {2, {"4567", "0123"}}};
	
/*
	n.inter.count = 1;
	strcpy(n.inter.blocks[0], "1234");
*/
	
	printNum(n);
	
	inpFile.close();
	return 0;
}