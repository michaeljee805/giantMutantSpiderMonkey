// Jee, Michael		CS546 Section 13495 Date completed
// First Laboratory Assignment - Compute Pythagorean Triples

#include "stdafx.h"
#include <iostream>
using namespace std;

void input(int & m, int & n);
void sideA(int m, int n, int & side1, int & eflags);
void sideB(int m, int n, int & side2, int & eflags);
void sideC(int m, int n, int & side3, int & eflags);

int main()
{
	int m, n, side1, side2, side3, eflags = 0;
	cout << "Pythagorean Triples Calculation - CS546 - Michael Jee" << endl
		<< "Enter values for m and n:" << endl;
	input(m, n);
	sideA(m, n, side1, eflags);
	if (!eflags)
	{
		if (m > n)
			sideB(m, n, side2, eflags);
		else
			sideB(n, m, side2, eflags);
	}
	if (!eflags)
		sideC(m, n, side3, eflags);
	if (!eflags)
	{
		cout << "Side a = " << side1 << endl;
		cout << "Side b = " << side2 << endl;
		cout << "Side c = " << side3 << endl;
		cout << "Calculation ended." << endl;
	}
	system("pause");
	if (!eflags)
		return 0;
	else
		return -1;
}

void input(int & m, int & n)
{
	cin >> m >> n;
	while (m <= 0)
	{
		cout << "Value " << m << " is out of range - only positive integers are allowed" << endl
			<< "Enter value for m:" << endl;
		cin >> m;
	}
	while (n <= 0)
	{
		cout << "Value " << n << " is out of range - only positive integers are allowed" << endl
			<< "Enter value for n:" << endl;
		cin >> n;
	}
}

void sideA(int m, int n, int & side1, int & eflags)
{
	int a = -1, temp = 0;
	__asm //side a=2*m*n
	{
		mov eax, m; //eax=m
		mov ebx, n; //ebx=n
		mul ebx; //eax*=ebx
		jo ReturnFl;//if overflow flag flagged, go to Return
		jc ReturnFl;//if carry flag flagged, go to Return
		mov ebx, 2;//ebx=2
		mul ebx; //eax*=2
		jo ReturnFl;
		jc ReturnFl;
		mov a, eax; //a=eax
		jmp Return0;
	ReturnFl:
		pushfd;
		pop eax;
		mov temp, eax;
		jmp Return0;
	Return0:
	}
	if (temp)
	{
		eflags = temp;
		cout << "Error completing calculation - Flags:" << eflags << endl;
	}
	else
		side1 = a;
}

void sideB(int m, int n, int & side2, int & eflags)
{
	int b = -1, temp = 0;
	__asm //side b=m^2-n^2
	{
		mov eax, n; //eax=n
		mul eax;//eax*=eax
		jo ReturnFl;
		jc ReturnFl;
		mov ebx, eax;//ebx=eax
		mov eax, m; //eax=m
		mul eax; //eax*=eax
		jo ReturnFl;
		jc ReturnFl;
		sub eax, ebx;//eax=ebx-eax
		mov b, eax; //b=eax
		jmp Return0;
	ReturnFl:
		pushfd;
		pop eax;
		mov temp, eax;
		jmp Return0;
	Return0:
	}
	if (temp)
	{
		eflags = temp;
		cout << "Error completing calculation - Flags:" << eflags << endl;
	}
	else
		side2 = b;
}

void sideC(int m, int n, int & side3, int & eflags)
{
	int c = -1, temp = 0;
	__asm //side b=m^2+n^2
	{
		mov eax, n; //eax=n
		mul eax;//eax*=eax
		jo ReturnFl;
		jc ReturnFl;
		mov ebx, eax;//ebx=eax
		mov eax, m; //eax=m
		mul eax; //eax*=eax
		jo ReturnFl;
		jc ReturnFl;
		add ebx, eax;//ebx=eax-ebx
		jo ReturnFl;
		jc ReturnFl;
		mov c, ebx; //c=ebx
		jmp Return0;
	ReturnFl:
		pushfd;
		pop eax;
		mov temp, eax;
		jmp Return0;
	Return0:
	}
	if (temp)
	{
		eflags = temp;
		cout << "Error completing calculation - Flags:" << eflags << endl;
	}
	else
		side3 = c;
}