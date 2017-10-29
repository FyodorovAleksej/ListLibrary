#define CRC_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

/**
	Переопределение слов TRUE и FALSE как 1 и 0 соответсвенно (так как в языке C нету типа bool)
*/
#define TRUE 1
#define FALSE 0

/***
	Определение одного блока (ячейки) списка
*/
struct block
{
	// Значение самого блока
	double value;
	// Указатель на следующий блок
	struct block* next;
};

/**
	@brief getBlock - Получение блока под выбранным номером
	@param start - начало очереди (указатель на 1-ый блок)
	@param position - позиция блока для выбора
	@return - указатель на блок с выбранным номером
*/
struct block* getBlock(struct block* start, int position)
{
	int current = 0;			// номер текущего блока
	while (start != NULL)		// проход до конца списка
	{
		if (current == position)// если совпали номера
		{
			return start;		// возвращаем текущий блок
		}
		start = start->next;	// переходим к следующему блоку
		current++;				// увеличиваем текущую позицию
	}
	return NULL;				// если вышли за конец списка - возвращаем NULL
}

/**
	@brief getLength - Получение длины списка
	@param start - начало списка
	@return - длина списка
*/
int getLength(struct block* start)
{
	int length = 0;				// текущая длина
	while (start != NULL)		// проход по всему списку
	{
		length++;				// увеличение длины
		start = start->next;	// переход к следующему блоку
	}
	return length;				// возврат длины
}

/**
	@brief insert - вставка нового блока после выбранного блока
	@param previous - указатель на блок перед вставкой
	@param newBlock - указатель на блок для вставки
*/
void insert(struct block* previous, struct block* newBlock)
{
	if (previous != NULL)		// проверка на нулевой указатель
	{
		newBlock->next = previous->next;	// перестановка указателей
		previous->next = newBlock;			
	}
}

/**
	@brief insertAfterPos - вставка нового блока после переданной позиции в списке
	@param start - начало списка
	@param newBlock - блок для вставки
	@param position - позиция в списке, после которой нужно вставить блок
	@return - получилось ли вставить?
*/
char insertAfterPos(struct block* start, struct block* newBlock, int position)
{
	struct block* blockOnPosition = getBlock(start, position);	// получение блока с указанной позицией
	if (blockOnPosition != NULL)								// проверка на нулевой указатель
	{
		insert(blockOnPosition, newBlock);						// вставка после найденного блока
		return TRUE;											// успешная вставка
	}
	return FALSE;												// указатель был NULL
}

/**
	@brief delAfter - удаление блока из списка после переданного блока
	@param previous - блок, после которого нужно удалить
*/
void delAfter(struct block* previous)
{
	if (previous != NULL)						// проверка указателя на NULL
	{
		struct block* temp = previous->next;	// сохранение указателя на следующий блок
		if (temp != NULL)						// проверка если мы передали конец списка
		{
			previous->next = temp->next;		// перестановка указателей
			free(temp);							// удаление старого блока
		}
	}
}

/**
	@brief deleteAfterPosition - удаление блока после переданной позиции в списке
	@param start - начало списка
	@param position - позиция, после которой нужно удалить блок
*/
void deleteAfterPosition(struct block* start, int position)
{
	delAfter(getBlock(start, position));		// удаление после блока с переданной позицией
}

/**
	@brief edit - изменение блока, следующего за указанным блоком в списке
	@param previous - блок, после которого нужно изменить блок
	@param newBlock - блок, на который нужно изменить старый блок
*/
void edit(struct block* previous, struct block* newBlock)
{
	delAfter(previous);				// удаление после переданного блока
	insert(previous, newBlock);		// вставка нового значения
}

/**
	@brief editAfterPosition - изменение блока, следующего за переданной позицией а списке
	@param start - начало списка
	@param newBlock - блок, на который нужно заменить старый блок
	@param position - позиция, после которой нужно изменить блок
*/
void editAfterPosition(struct block* start, struct block* newBlock, int position)
{
	struct block* blockOnPosition = getBlock(start, position);	// получение блока на указанной позиции
	if (blockOnPosition != NULL)								// проверка на нулевой указатель
	{
		edit(blockOnPosition, newBlock);						// изменение следующего за ним блока
	}
}

/**
	@brief clear - очистка всего списка
	@param start - начало списка
*/
void clear(struct block* start)
{
	struct block* temp = start;		// сохранение указателя на текущий блок
	while (start != NULL)			// прохождение по всему списку
	{
		temp = start;				// текущий блок
		start = start->next;		// переход на следующий блок
		free(temp);					// удаление предыдущего блока
	}
}

/**
	@brief appendToEnd - добавление блока в конец списка
	@param start - начало списка
	@param newBlock - блок для добавления
*/
void appendToEnd(struct block* start, struct block* newBlock)
{
	while(start->next != NULL)	// проход до конца списка
	{
		start = start->next;	// переход к следующему блоку
	}
	start->next = newBlock;		// добавление блока в конец
	newBlock->next = NULL;		// зануление конца списка
}

/**
	@brief create - создание блока (ячейки) с переданным значением
	@param value - значение новой ячейки
	@return - указатель на созданный блок (ячейку)
*/
struct block* create(double value)
{
	struct block* newBlock = (struct block*)malloc(sizeof(struct block));	// выделение памяти для блока
	newBlock->value = value;												// установка заданного значения
	newBlock->next = NULL;													// зануление указателя
	return newBlock;														// возвращение созданного блока
}

/**
	@brief out - вывод списка 
	@param start - начало списка
*/
void out(struct block* start)
{
	for (; start != NULL; start = start->next)	// прохождение по всем блокам списка
	{
		printf("%f ", start->value);			// вывод значения каждого блока
	}
	printf("\n");								// переход на новую строчку
}

/**
	@brief test - проверка совпадения значения блока в списке с переданным значением
	@param current - блок в списке
	@param value - значение, с которым оно сравнивается
	@return - совпадает ли значение?
*/
char test(struct block* current, double value)
{
	static int number;								// статический номер текущего теста (рассмотрим на занятии)
	if (current->value == value)					// если совпадает значение блока и переданное значение
	{
		printf("----------------------------\n");	// вывод сообщения о прохождении теста
		printf("test number %d\n", number);
		printf("Succesfully passed\n");
		printf("----------------------------\n");
		number++;
		return TRUE;
	}
	else
	{
		printf("----------------------------\n");	// вывод сообщение о непрохождении теста
		printf("test number %d\n", number);
		printf("FAILED: \n");
		printf("Expected: %f ; Valid: %f\n", current->value, value);
		printf("----------------------------\n");
		number++;
		return FALSE;
	}
}

void main()
{
	struct block *start;
	start = create(2.5);

	appendToEnd(start, create(3.6));
	appendToEnd(start, create(4.7));
	out(start);

	test(start, 2.5);
	test(getBlock(start, 1), 3.6);

	insertAfterPos(start, create(4.0), 2);
	test(getBlock(start, 3), 4.0);

	deleteAfterPosition(start, 1);
	test(getBlock(start, 2), 4.0);

	editAfterPosition(start, create(1.8), 1);
	test(getBlock(start, 2), 1.8);

	clear(start);
	system("pause");
}