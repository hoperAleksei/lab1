#include <iostream>
#include <fstream>

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



/*
 * Блок описания типов
 *
*/

using block_t = char[BLOCK_LENGTH];

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
};

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


/*
 * Блок описания функций работы с блоками
 *
*/


block_t* blockAdd(block_t term1, block_t term2, bool *transfer)
{
	/*
	 * Функция складывает блоки term1 и term2 с переносом transfer
	 * если transfer = true, то к результату сложения блоков прибавляется еденица
	 * если происходит переполнение блока, то transfer = true
	*/
	
	// TODO
	
}

block_t* blockSub(block_t min, block_t sub, bool *transfer)
{
	/*
	 * Функция вычитает из блока min блок sub с заемом transfer
	 * если transfer = true, то из результата сложения блоков вычитается еденица
	 * если происходит недостаток блока, то transfer = true
	*/
	
	// TODO
	
}

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

partOfNum addfact(partOfNum term1, partOfNum term2, bool transfer)
{
	/*
	 * Функция для сложения дробных частей чисел
	*/
	
	// TODO
	
}

partOfNum subfact(partOfNum min, partOfNum sub, bool transfer)
{
	/*
	 * Функция для вычитания дробных частей чисел
	*/
	
	// TODO
	
}


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

number readNum(/* char numb string numb,  */)
{
	/*
	 * Функция считывания числа
	*/
	
	// TODO
	
}

number printNum(/* char numb string numb,  */)
{
	/*
	 * Функция вывода числа
	*/
	
	// TODO
	
}



int main() {
	ifstream fout;
	fout.open("inp");

	cout << __cplusplus << endl;

	fout.close();
	return 0;
}