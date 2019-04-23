/*Jee, Michael
CS 539 Lab 8
12/3/18
This program will: take as input: last name, first name; street address; city and state; and zip code and
output a new file with the data in order with respect to zip code using file input output*/

#include "header.h"

int inputAlloc(Data *pdata[], Data *sortData[], FILE *infile)
{
	int size = 0;
	for (size = 0; size < MAXSIZE && !feof(infile); size++) /*loop until max number of entries or until end of file*/
	{
		pdata[size] = (Data*)malloc(sizeof(Data)); /*allocating*/
		if (pdata[size] == NULL)
		{
			printf("Error allocating pData.\n");
			exit(1);
		}
		sortData[size] = (Data*)malloc(sizeof(Data));
		if (sortData[size] == NULL)
		{
			printf("Error allocating sortData.\n");
			exit(1);
		}
		fgets(pdata[size]->name, MAXSTR, infile); /*assigning*/
		if (pdata[size]->name == NULL)
			printf("Error reading name.");
		fgets(pdata[size]->address, MAXSTR, infile);
		if (pdata[size]->address == NULL)
			printf("Error reading address.");
		fgets(pdata[size]->cityState, MAXSTR, infile);
		if (pdata[size]->cityState == NULL)
			printf("Error reading cityState.");
		fgets(pdata[size]->zip, MAXZIP, infile);
		if (pdata[size]->zip == NULL)
			printf("Error reading zip.");
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

void output(int size, Data *sortData[], FILE *outfile)
{
	for (int i = 0; i < size; i++) /*output loop*/
	{
		fputs(sortData[i]->name, outfile);
		fputs(sortData[i]->address, outfile);
		fputs(sortData[i]->cityState, outfile);
		fputs(sortData[i]->zip, outfile);
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