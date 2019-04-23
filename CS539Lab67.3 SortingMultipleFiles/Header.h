/*Jee, Michael
CS 539 Lab 6 and 7
11/26/18
This program will: take as input: last name, first name; street address; city and state; and zip code and
output a new file with the data in order with respect to zip code*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAXSTR 26 /*max size of strings*/
#define MAXZIP 6 /*max size of zip code*/
#define MAXSIZE 50 /*max number of entries*/

typedef struct data
{
	char name[MAXSTR];
	char address[MAXSTR];
	char cityState[MAXSTR];
	char zip[MAXZIP];
} Data;

int inputAlloc(Data *pdata[], Data *sortData[]);
void sort(int size, Data *sortData[]);
void output(int size, Data *sortData[]);
void dealloc(int size, Data *pdata[], Data *sortData[]); 

#pragma once