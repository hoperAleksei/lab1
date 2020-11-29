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

#define BASE 10
#define BLOCK_LENGTH 4
#define BLOCK_COUNT 25
#define LINE_COUNT 100

#define INPUT_FILE_NAME "inp"
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
	
	const string validDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return validDigits.find(CDigit);
}

char getDigitRepr(int IDigit)
{
	/*
	 * Функция получает для каждой цифры типа int ее представление в char
	*/
	
	const string validDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return validDigits[IDigit];
}


#pragma endregion general_functions

#pragma region block_functions

/*
 * Блок описания функций работы с блоками
 *
*/

bool compareBlocks(block_t a, block_t b)
{
	/*
	 * Сравнивает блоки a и b, если a > b возвращает true
	*/
	
	if (strlen(a) > strlen(b))
	{
		return true;
	}
	else
	{
		for (int i = 0; i < BLOCK_LENGTH; ++i)
		{
			if (a[i] == '\0')
			{
				break;
			}
			if (a[i] > b[i])
			{
				return true;
			}
			else if (b[i] > a[i])
			{
				return false;
			}
		}
	}
	return false;
}

void blockAdd(block_t term1, block_t term2, bool &transfer, block_t &res)
{
	/*
	 * Функция складывает блоки term1 и term2 с переносом transfer
	 * если transfer = true, то к результату сложения блоков прибавляется еденица
	 * если происходит переполнение блока, то transfer = true
	*/
	
	int sum = 0;
	for (int i = BLOCK_LENGTH-1; i>=0; --i)
	{
		sum = getDigitWeight(term1[i]) + getDigitWeight(term2[i]) + (transfer ? 1 : 0);
		res[i] = getDigitRepr(sum % BASE);
		transfer = (bool) (sum / BASE);
	}
}

void blockSub(block_t min, block_t sub, bool &transfer, block_t &res)
{
	/*
	 * Функция вычитает из блока min блок sub с заемом transfer
	 * если transfer = true, то из результата сложения блоков вычитается еденица
	 * если происходит недостаток блока, то transfer = true
	*/
	
	int diff = 0;
	for (int i = BLOCK_LENGTH-1; i>=0; --i)
	{
		diff = getDigitWeight(min[i]) - getDigitWeight(sub[i]) - (transfer ? 1 : 0);
		if (diff < 0)
		{
			transfer = true;
			diff += BASE;
		}
		else
		{
			transfer = false;
		}
		res[i] = getDigitRepr(diff);
	}
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

bool compareNumbers(number a, number b)
{
	/*
	 * Сравнивает модули чисел a и b, если a > b возвращает true
	*/
	
	if (a.inter.count > b.inter.count)
	{
		return true;
	}
	else if (a.inter.count < b.inter.count)
	{
		return false;
	}
	else
	{
		for (int i = a.inter.count-1; i >= 0; --i)
		{
			if (compareBlocks(a.inter.blocks[i], b.inter.blocks[i]))
			{
				return true;
			}
			else if (compareBlocks(b.inter.blocks[i], a.inter.blocks[i]))
			{
				return false;
			}
		}
		int i, j;
		for (i = 0, j = 0; (i <= a.fact.count-1) && (j <= b.fact.count-1); ++i, ++j)
		{
			if (compareBlocks(a.fact.blocks[i], b.fact.blocks[j]))
			{
				return true;
			}
			else if (compareBlocks(b.fact.blocks[j], a.fact.blocks[i]))
			{
				return false;
			}
		}
		cout << i << ' ' << j << endl;
		if ((i <= a.fact.count-1) && (j > b.fact.count-1))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

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

bool equal(number a, number b)
{
	/*
	 * Возвращает true, если a = b
	*/

	return (!(compareNumbers(a, b) || compareNumbers(b, a)) && (a.sign == b.sign));
}

bool less(number a, number b)
{
	/*
	 * Возвращает true, если a < b
	*/

	return (((a.sign == b.sign) && (!a.sign) && compareNumbers(b, a)) || ((a.sign == b.sign) && (a.sign) && compareNumbers(a, b)) || (a.sign && !b.sign)) && (!equal(a, b));
}




#pragma region functions_for_readNum


void errorThrow(bool &error, int len, int dot)
{
	error = true;
	cout << "Error!\tLen: " << len << ", Dot pos: " << dot << endl;
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
	
	
	
	if ((((len > 1) && (SInter[0] == '0')) || (count > BLOCK_COUNT)))
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
	
	if ((((len > 1) && (SFact[len-1] == '0')) || (count > BLOCK_COUNT)))
	{
		error = true;
	}
	else
	{
	//	cout << "------===" << count << endl;
		for(int i = 0; i < count-1; ++i)
		{
			strcpy(res.blocks[i], SFact.substr((i)*BLOCK_LENGTH, BLOCK_LENGTH).c_str());
			checkBlock(res.blocks[i], error);
		}
		strcpy(res.blocks[count-1], SFact.substr(len-lastBlockLength).c_str());
		checkBlock(res.blocks[count-1], error);
		res.count = count;
	}
	/*for (int i = res.count-1; i >= 0 ; --i)
	{
		cout << i <<'(' << res.blocks[i] << ')';
	}
	cout << endl;*/
	return res;

	// todo
}


#pragma endregion functions_for_readNum

number readNum(string numb, bool &error)
{
	/*
	 * Функция считывания числа
	*/
	
	number res;

	// TODO Поменять порядок дробной части
	
	
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
				SInter = numb.substr(1, dot-1);
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
	for (int i = 0 ; i <= numb.fact.count-1 ; ++i)
	{
		cout << i << '(' << numb.fact.blocks[i] << ')';
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
	number nn;
	cout << "Ваша версия страндарта языка: " << __cplusplus << endl;
	
	//while (! inpFile.eof())
	//{
		//error = false;
		//getline(inpFile, line, '\n');
		//n = readNum(line, error);
		//getline(inpFile, line, '\n');
		//nn = readNum(line, error);
		
		//cout << equal(n, nn) << endl;

		//printNum(n);
		

		//getline(inpFile, line, '\n');
		//nn = readNum(line, error);
		
		// cout << compareNumbers(n, nn) << endl;
		
		// if (!error)
		// {
		// 	
		// }
		// else
		// {
		// 	//cout << "ERROR!!!" << line << endl;
		// }
	//}
	
	
	
	//number n = {true, {2, {"5678", "1234", "1234"}}, {2, {"4567", "0123"}}};
	
/*
	n.inter.count = 1;
	strcpy(n.inter.blocks[0], "1234");
*/
	
	//printNum(n);
	
	//cout << compareBlocks("01", "10");
	
	// block_t b;
	// block_t x = "1111";
	// block_t y = "9899";
	
	// blockAdd(x, y, error, b);
	// cout << '=' << b << '+' << error << endl;
	// error = false;
	// blockSub(x, y, error, b);
	// cout << '=' << b << '-' << error << endl;
	


	block_t b1 = "0100";
	block_t b2 = "0099";

	block_t res;

	blockSub(b1, b2, error, res);

	cout << res << endl;
	
	inpFile.close();
 	return 0;
}