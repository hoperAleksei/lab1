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
#define BLOCK_COUNT 10
#define LINE_COUNT 100

#define INPUT_FILE_NAME "/home/aleksei/Projects/lab1/inp"
#define OUTPUT_FILE_NAME "/home/aleksei/Projects/lab1/oup"


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
	res[BLOCK_LENGTH] = '\0';
	for (int i = BLOCK_LENGTH-1; i>=0; --i)
	{
		sum = getDigitWeight(term1[i]) + getDigitWeight(term2[i]) + (transfer ? 1 : 0);
		res[i] = getDigitRepr(sum % BASE);
		transfer = (bool) (sum / BASE);
	}
	
}

void blockZerosL(block_t &blockIn)
{
	int len = strlen(blockIn);
	
	block_t buf;
	
	strcpy(buf, blockIn);
	
	for (int i = 0; i < BLOCK_LENGTH-len; ++i) {
		blockIn[i] = '0';
	}
	for (int i = BLOCK_LENGTH-len, j = 0; i < BLOCK_LENGTH; ++i, ++j) {
		blockIn[i] = buf[j];
	}
}

void blockZerosR(block_t &blockIn)
{
	int len = strlen(blockIn);
	
	for (int i = len; i < BLOCK_LENGTH; ++i) {
		blockIn[i] = '0';
	}
	blockIn[BLOCK_LENGTH] = '\0';
}

void blockNormalizeL(block_t &blockIn)
{
	block_t buf;
	int i = 0;
	int len = strlen(blockIn);
	
	for (;i < len; ++i)
	{
		if (blockIn[i] != '0')
		{
			break;
		}
	}
	int j = 0;
	for (; i < len, j < len; ++j, ++i)
	{
		buf[j] = blockIn[i];
	}
	buf[j] = '\0';
	
	strcpy(blockIn, buf);
}

void blockNormalizeR(block_t &blockIn)
{
	int len = strlen(blockIn);
	int i = len - 1;
	
	for (;i>=0; --i)
	{
		//cout << i << ' ' << blockIn[i] << endl;
		if (blockIn[i] != '0')
		{
			break;
		}
		else
		{
			blockIn[i] = '\0';
		}
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
	res[BLOCK_LENGTH] = '\0';
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

partOfNum addInter(partOfNum term1, partOfNum term2, bool &transfer)
{
	/*
	 * Функция для сложения целых частей чисел
	*/
	
	if (term2.count > term1.count)
	{
		partOfNum buf;
		buf = term1;
		term1 = term2;
		term2 = buf;
	} // term2 <= term1
	
	block_t buf;
	partOfNum res;
	
	int i = 0;
	for (; i < term2.count-1; ++i) // сложение полных блоков
	{
		blockAdd(term1.blocks[i], term2.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
	}
	blockZerosL(term2.blocks[i]);
	if (term2.count == term1.count) // сложение первого блока у равных чисел
	{
		blockZerosL(term1.blocks[i]);
		blockAdd(term1.blocks[i], term2.blocks[i], transfer, buf);
		// возможны неожиданные ошибки
		if (!transfer)
		{
			blockNormalizeL(buf);
		}
		strcpy(res.blocks[i], buf);

	}
	else // сложение блоков отсутствующих у одного числа
	{
		blockAdd(term1.blocks[i], term2.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
		i += 1;
		block_t zero = "";
		blockZerosL(zero);
		for (; i < term1.count-1; ++i){
			blockAdd(term1.blocks[i], zero, transfer, buf);
			strcpy(res.blocks[i], buf);
		}
		blockZerosL(term1.blocks[i]);
		blockAdd(term1.blocks[i], zero, transfer, buf);
		if (!transfer)
		{
			blockNormalizeL(buf);
		}
		strcpy(res.blocks[i], buf);
	}
	if (transfer) // учет переноса в новый блок
	{
		if (i >= BLOCK_COUNT-1) // учет переолнения блоков
		{
			/* можно переделать */
			cout << "ERROR: переполнение" << endl;
			i = 0;
			strcpy(res.blocks[0], "0");
		}
		else
		{
			i += 1;
			strcpy(res.blocks[i], "1");
		}
	}
	
	res.count = i+1;
	
	if ((res.count == 1) && (strlen(res.blocks[0]) == 0))
	{
		strcpy(res.blocks[0], "0");
	}
	return res;
}

partOfNum subInter(partOfNum min, partOfNum sub, bool &transfer)
{
	/*
	 * Функция для вычитания целых частей чисел
	*/
	
	partOfNum res;
	block_t  buf;
	
	int i = 0;
	
	for (;i < sub.count-1; ++i) // вычитание полных блоков
	{
		blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
	}
	blockZerosL(sub.blocks[i]);
	if (sub.count == min.count) // вычитание первого блока у равных чисел
	{
		blockZerosL(min.blocks[i]);
		blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
		++i;
	}
	else
	{
		blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
		++i;
		block_t zero = "";
		blockZerosL(zero);
		for (;i < min.count-1; ++i) // вычитание блоков пустых у sub
		{
			blockSub(min.blocks[i], zero, transfer, buf);
			strcpy(res.blocks[i], buf);
		}
		blockZerosL(min.blocks[i]);
		blockSub(min.blocks[i], zero, transfer, buf);
		strcpy(res.blocks[i], buf);
		++i;
	}

	res.count = i;
	
	if (transfer)
	{
		cout << "ERROR!!!!!!!!!!!!!! В ПРОГРАММЕ СБОЙ" << endl;
	}
	
	--i;
	for (; i >= 0; --i) // приведение числа к нормальному виду
	{
		blockNormalizeL(res.blocks[i]);
		if (strlen(res.blocks[i]) != 0)
		{
			break;
		}
		else
		{
			if (i == 0)
			{
				strcpy(res.blocks[i], "0");
			}
			else
			{
				--res.count;
			}
		}
	}
	
	
	return res;
}

partOfNum addFact(partOfNum term1, partOfNum term2, bool &transfer)
{
	/*
	 * Функция для сложения дробных частей чисел
	*/
	
	if (term2.count > term1.count)
	{
		partOfNum buf;
		buf = term1;
		term1 = term2;
		term2 = buf;
	} // term2 <= term1
	
	block_t buf;
	partOfNum res;
	
	int i = term1.count-1;
	
	for (; i > term2.count-1; --i) // сложение блоков отсутствующих у одного числа
	{
		strcpy(res.blocks[i], term1.blocks[i]);
	}
	if (i >= 0) //сложение первого блока у равных чисел
	{
		blockZerosR(term1.blocks[i]);
		blockZerosR(term2.blocks[i]);
		blockAdd(term1.blocks[i], term2.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
		--i;
		for (;i >= 0; --i) // сложение полных блоков
		{
			blockAdd(term1.blocks[i], term2.blocks[i], transfer, buf);
			strcpy(res.blocks[i], buf);
		}
	}
	
	res.count = term1.count;
	
	i = res.count-1;
	for (; i >= 0; --i) // приведение числа к нормальному виду
	{
		blockNormalizeR(res.blocks[i]);
		if (strlen(res.blocks[i]) != 0)
		{
			break;
		}
		else
		{
			if (i == 0)
			{
				strcpy(res.blocks[i], "0");
			}
			else
			{
				--res.count;
			}
		}
	}
	
	return res;
}

partOfNum subFact(partOfNum min, partOfNum sub, bool &transfer)
{
	/*
	 * Функция для вычитания дробных частей чисел. Из min вычитается sub
	*/
	
	partOfNum res;
	block_t buf;
	
	block_t zero = "";
	blockZerosR(zero);
	
	int i;
	
	if (min.count >= sub.count) // вычитание блоков отсутствующих у sub
	{
		i = min.count-1;
		
		blockZerosR(min.blocks[i]);
		if (min.count != sub.count)
		{
			for (; i > sub.count-1; --i)
			{
				blockSub(min.blocks[i], zero, transfer, buf);
				strcpy(res.blocks[i], buf);
			}
			blockZerosR(sub.blocks[i]);
			blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
			strcpy(res.blocks[i], buf);
			--i;
		}
		else
		{
			blockZerosR(sub.blocks[i]);
			blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
			strcpy(res.blocks[i], buf);
		}
		res.count = min.count;
	}
	else // вычитание блоков отсутствующих у min
	{
		i = sub.count-1;
		
		blockZerosR(sub.blocks[i]);
		for (; i > min.count-1; --i) // вычитание блоков отсутствующих у sub
		{
			blockSub(zero, sub.blocks[i], transfer, buf);
			strcpy(res.blocks[i], buf);
		}
		blockZerosR(min.blocks[i]);
		blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
		res.count = sub.count;
	}
	--i;
	for (; i >= 0; --i) // вычитание полных блоков
	{
		blockSub(min.blocks[i], sub.blocks[i], transfer, buf);
		strcpy(res.blocks[i], buf);
	}
	
	i = res.count-1;
	for (; i >= 0; --i) // приведение числа к нормальному виду
	{
		blockNormalizeR(res.blocks[i]);
		if (strlen(res.blocks[i]) != 0)
		{
			break;
		}
		else
		{
			if (i == 0)
			{
				strcpy(res.blocks[i], "0");
			}
			else
			{
				--res.count;
			}
		}
	}
	
	return res;
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
	
	number res;
	bool transfer = false;
	
	res.fact = addFact(term1.fact, term2.fact, transfer);
	res.inter = addInter(term1.inter, term2.inter, transfer);
	
	return  res;
	
}

number subAbs(number min, number sub)
{
	/*
	 * Функция вычитания модулей чисел
	*/
	number res;
	bool transfer = false;
	
	res.fact = subFact(min.fact, sub.fact, transfer);
	res.inter = subInter(min.inter, sub.inter, transfer);
	
	return  res;
	
}


#pragma endregion abs_number_functions

#pragma region number_functions

/*
 * Блок описания функций для работы с числами
 *
*/

number _subNum(number min, number sub);

number addNum(number term1, number term2)
{
	/*
	 * Функция сложения чисел
	*/
	
	number res;
	
	if (term1.sign == term2.sign) // числа имеют одинаковые знаки
	{
		res = addAbs(term1, term2);
		res.sign = term1.sign;
	}
	else if (!(!term1.sign && term2.sign)) // из term1 вычитаем term2
	{
		res = _subNum(term2, term1);
	}
	else if (!(term1.sign && !term2.sign)) // из term2 вычитаем term1
	{
		res = _subNum(term1, term2);
	}
	
	return res;
}

number _subNum(number min, number sub)
{
	/*
	 * Функция вычитания положительных чисел (min - sub)
	*/
	
	bool ind = compareNumbers(sub, min);
	number res;
	bool transfer;
	
	if (ind)
	{
		res.sign = true;
		res.fact = subFact(sub.fact, min.fact, transfer);
		res.inter = subInter(sub.inter, min.inter, transfer);
	}
	else
	{
		res.sign = false;
		res.fact = subFact(min.fact, sub.fact, transfer);
		res.inter = subInter(min.inter, sub.inter, transfer);
	}
	
	return res;
}

number subNum(number min, number sub)
{
	/*
	 * Функция вычитания чисел (min - sub)
	*/
	
	number res;
	
	if (min.sign == sub.sign)
	{
		if (min.sign)
		{
			res = _subNum(sub, min);
		}
		else
		{
			res = _subNum(min, sub);
		}
	}
	else
	{
		res = addAbs(min, sub);
		if (min.sign)
		{
			res.sign = true;
		}
		else
		{
			res.sign = false;
		}
	}
	
	
	// TODO
	
	return res;
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
		res.sign = false;
		res.fact.count = 0;
		res.inter.count = 0;
		return res;
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
		cout << i << '(' << numb.inter.blocks[i] << ')';
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
	
	number r;
	cout << "Ваша версия страндарта языка: " << __cplusplus << endl;
	
	n = readNum("0.0", error);
	nn = readNum("0.0", error);
	error = false;
	/*
	 * max 4 * 10 | 16
	 * FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	 * FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF.FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	 *
	 * 1..0 4 * 10 | 16
	 * 1000000000000000000000000000000000000000.0
	 * */
	
	r = addNum(n, nn);
	
	printNum(n);
	printNum(nn);
	
	
	printNum(r);
	
	
	
	
	inpFile.close();
	return 0;
}