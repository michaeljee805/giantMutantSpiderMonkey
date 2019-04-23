/*Jee, Michael
CS 539 Lab 6 and 7
11/26/18
This program will: take as input: last name, first name; street address; city and state; and zip code and
output a new file with the data in order with respect to zip code*/

#include "header.h"

int inputAlloc(Data *pdata[], Data *sortData[])
{
	int size = 0;
	int iochar;
	int end = 0;
	for (size = 0; size < MAXSIZE && !feof(stdin); size++) /*loop until max number of entries or until end of file*/
	{
		pdata[size] = (Data*)malloc(sizeof(Data)); /*allocating*/
		if (pdata[size] == NULL)
			printf("Error allocating.\n");
		sortData[size] = (Data*)malloc(sizeof(Data));
		if (sortData[size] == NULL)
			printf("Error allocating.\n");
		gets(pdata[size]->name); /*assigning*/
		gets(pdata[size]->address);
		gets(pdata[size]->cityState);
		gets(pdata[size]->zip);
		*sortData[size] = *pdata[size]; /*copying to sorting array*/
	}
	return size;
}

void sort(int size, Data *sortData[])
{
	int index, count, count2;
	Data *temp = { '\0' };
	for (index = 0; index < size; index++) /*sorting*/
	{
		for (count2 = index + 1; count2 < size; count2++)
		{
			count = index;
			/*printf("%s %s %d\n", sortData[index]->zip, sortData[count2]->zip, strcmp(sortData[count]->zip, sortData[count2]->zip));*/
			if (strcmp(sortData[count]->zip, sortData[count2]->zip) == 1) /*if count2<count, swap*/
			{
				count = count2;
				temp = sortData[count]; /*3 variable swap*/
				sortData[count2] = sortData[index];
				sortData[index] = temp;
			}
		}
	}
}

void output(int size, Data *sortData[])
{
	for (int i = 0; i < size; i++) /*output loop*/
	{
		puts(sortData[i]->name);
		puts(sortData[i]->address);
		puts(sortData[i]->cityState);
		puts(sortData[i]->zip);
	}
}

void dealloc(int size, Data *pdata[], Data *sortData[])
{
	for (int i = 0; i < size; i++) /*deallocating loop*/
	{
		free((void*)pdata[i]);
		free((void*)sortData[i]);
	}
}