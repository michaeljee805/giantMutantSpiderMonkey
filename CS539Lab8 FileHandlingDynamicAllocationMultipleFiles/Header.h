/*Jee, Michael
CS 539 Lab 8
12/3/18
This program will: take as input: last name, first name; street address; city and state; and zip code and
output a new file with the data in order with respect to zip code using file input output*/#pragma once

#ifndef FUNCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAXSTR 26 /*max size of strings*/
#define MAXZIP 7 /*max size of zip code*/
#define MAXSIZE 50 /*max number of entries*/

typedef struct data
{
	char name[MAXSTR];
	char address[MAXSTR];
	char cityState[MAXSTR];
	char zip[MAXZIP];
} Data;

int inputAlloc(Data *pdata[], Data *sortData[], FILE *input);
void sort(int size, Data *sortData[]);
void output(int size, Data *sortData[], FILE *output);
void dealloc(int size, Data *pdata[], Data *sortData[]);

#endif