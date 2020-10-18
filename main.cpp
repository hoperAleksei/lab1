#include <iostream>
#include <fstream>
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
	 * Функция получает для каждой цифры типа char ее вес (значение) в int
	*/
	
	string validDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return validDigits.find(CDigit);
}

char getDigitRepr(int IDigit)
{
	/*
	 * Функция получает для каждой цифры типа int ее представление в char
	*/
	
	string validDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return validDigits[IDigit];
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

#pragma region functions_for_readNum


void errorThrow(bool &error, int len, int dot)
{
	error = true;
	cout << "Error!!!\tLen: " << len << " dot pos: " << dot << endl;
}

void checkBlock(block_t block, bool &error)
{
	int digit;
	for (int i = 0; i < BLOCK_LENGTH; ++i)
	{
		if (block[i] == '\0')
		{
			break;
		}
		digit = getDigitWeight(block[i]);
		if ((digit == -1) || (digit >= BASE))
		{
			cout << digit << '=' << block[i] << endl;
			error = true;
		}
	}
}

partOfNum readInter(string SInter, bool &error)
{
	partOfNum res;
	
	int len = SInter.length();
	int lastBlockLength = len % BLOCK_LENGTH;
	lastBlockLength = lastBlockLength == 0 ? BLOCK_LENGTH : lastBlockLength;
	int count = len / BLOCK_LENGTH + (lastBlockLength == BLOCK_LENGTH ? 0 : 1);
	
	
	
	if (((len > 1) && (SInter[0] == '0') || (count > BLOCK_COUNT)))
	{
		error = true;
	}
	else
	{
		strcpy(res.blocks[count-1], SInter.substr(0, lastBlockLength).c_str());
		checkBlock(res.blocks[count-1], error);
	//	cout << SInter.substr(0, lastBlockLength).c_str() << ' ' << count << endl;
		for(int i = count-2; i >=0; --i)
		{
			//cout << i;
			strcpy(res.blocks[i], SInter.substr(lastBlockLength+(count-2-i)*BLOCK_LENGTH, BLOCK_LENGTH).c_str());
			checkBlock(res.blocks[i], error);
		}
		res.count = count;
	}
/*	for (int i = res.count-1; i >= 0 ; --i)
	{
		cout << i <<'(' << res.blocks[i] << ')';
	}
	cout << endl;*/
	
	return res;
}

partOfNum readFact(string SFact, bool &error)
{
	partOfNum res;
	
	int len = SFact.length();
	int lastBlockLength = len % BLOCK_LENGTH;
	lastBlockLength = lastBlockLength == 0 ? BLOCK_LENGTH : lastBlockLength;
	int count = len / BLOCK_LENGTH + (lastBlockLength == BLOCK_LENGTH ? 0 : 1);
	
	if (((len > 1) && (SFact[len-1] == '0') || (count > BLOCK_COUNT)))
	{
		error = true;
	}
	else
	{
	//	cout << "------===" << count << endl;
		for(int i = count-1; i > 0; --i)
		{
			strcpy(res.blocks[i], SFact.substr((count-1-i)*BLOCK_LENGTH, BLOCK_LENGTH).c_str());
			checkBlock(res.blocks[i], error);
		}
		strcpy(res.blocks[0], SFact.substr(len-lastBlockLength).c_str());
		checkBlock(res.blocks[0], error);
		res.count = count;
	}
	/*for (int i = res.count-1; i >= 0 ; --i)
	{
		cout << i <<'(' << res.blocks[i] << ')';
	}
	cout << endl;*/
	return res;
}


#pragma endregion functions_for_readNum

number readNum(string numb, bool &error)
{
	/*
	 * Функция считывания числа
	*/
	
	number res;
	
	
	string SInter;
	string SFact;
	
	int len = numb.length();
	
	int dot = numb.find('.');
	
	
	if ((len == 0) || (dot == -1) || (dot == 0) || (dot+1 == len))
	{
		errorThrow(error, len, dot);
	}
	else
	{
		if (numb[0] == '-')
		{
			if (numb[1] == '.')
			{
				errorThrow(error, len, dot);
			}
			else
			{
				SInter = numb.substr(1, dot);
				res.sign = true;
			}
		}
		else
		{
			res.sign = false;
			SInter = numb.substr(0, dot);
		}
		if (!error)
		{
			SFact = numb.substr(dot + 1);
			//cout << SInter << '|' << SFact << endl;
			
			res.inter = readInter(SInter, error);
			if (!error)
			{
				res.fact = readFact(SFact, error);
				if (error)
				{
					errorThrow(error, len, dot);
				}
			}
			else
			{
				errorThrow(error, len, dot);
			}
			
			return res;
		}
	}
	// TODO
}

void printNum(number numb)
{
	/*
	 * Функция вывода числа
	*/
	
	cout << (numb.sign ? '-' : '+');
	// cout << numb.inter.count << '/';
	for (int i = numb.inter.count-1; i >= 0 ; --i)
	{
		cout << '(' << numb.inter.blocks[i] << ')';
	}
	cout << '.';
	// cout << numb.fact.count << '/';
	for (int i = numb.fact.count-1; i >= 0 ; --i)
	{
		cout << '(' << numb.fact.blocks[i] << ')';
	}
	cout  << endl;
	
	//TODO убрать дебаг
}


#pragma endregion number_functions


int main() {
	ifstream inpFile;
	inpFile.open(INPUT_FILE_NAME);
	
	string line;
	
	bool error = false;
	
	number n;
	
	cout << "Ваша версия страндарта языка: " << __cplusplus << endl;
	
	while (! inpFile.eof())
	{
		error = false;
		getline(inpFile, line, '\n');
		n = readNum(line, error);
		if (!error)
		{
			printNum(n);
		}
		else
		{
			cout << "ERROR!!!" << line << endl;
		}
	}
	
	//number n = {true, {2, {"5678", "1234", "1234"}}, {2, {"4567", "0123"}}};
	
/*
	n.inter.count = 1;
	strcpy(n.inter.blocks[0], "1234");
*/
	
	//printNum(n);
	
	
	
	inpFile.close();
	return 0;
}