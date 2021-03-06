// Michael Jee
// 10/4/18
// CS 540
// Lab 3

#include "stdafx.h"
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

const int FILE_SIZE = 20;
const string dataIn = "dataIn.txt";

struct students
{
	string firstName = " ";
	string lastName = " ";
	double GPA = 0.0f;
	string idNum = "0";
	string email = " ";
};

void readData(students school[], int & size,  students *pschool[]);
void menu(students school[], int & select, int size, students *pschool[]);
void sort(int select, int size, students *pschool[]);
void printOrig(students school[], int size);
void printNew(int size, students *pschool[]);

int main()
{
	int select;
	int size = 0;
	cout << setprecision(2) << showpoint << fixed;
	students school[FILE_SIZE];
	students *pschool[FILE_SIZE]; //array of pointers to sort
	char contin = 'y';
	readData(school, size, pschool);
	do
	{
		menu(school, select, size, pschool);
		cout << "Continue? (Y/N)" << endl;
		cin >> contin;
	} while (contin == 'y' || contin == 'Y');
	cout << "File processing complete. Output in dataOut.txt" << endl;
	return 0;
}

void readData(students school[], int & size, students *pschool[])
{
	ifstream infile;
	infile.open(dataIn);
	if (!infile)
	{
		cout << "Error opening file. Program terminating." << endl;
		infile.close();
		exit(1);
	}
	while (!infile.eof() && size < FILE_SIZE)
	{
		infile >> school[size].firstName >> school[size].lastName >> school[size].GPA >> school[size].idNum >> school[size].email;
		pschool[size] = &school[size];
		size++; //counts size up to FILE_SIZE (20)
	}
	if (!infile.eof())
	{
		cout << "Warning. File size too large. Data output is truncated.\n" << endl;
	}
	infile.close();
}

void menu(students school[], int & select, int size, /*ofstream & outfile,*/ students *pschool[])
{
	do
	{
		cout << "Hello. This program will read data from the file \"dataIn.txt\" and output it sorted or unsorted into \"dataOut.txt\"." << endl;
		cout << "0: output data unsorted" << endl;
		cout << "1: sort data in ascending order by first name" << endl;
		cout << "2: sort data in ascending order by last name" << endl;
		cout << "3: sort data in ascending order by GPA" << endl;
		cout << "4: sort data in ascending order by ID number" << endl;
		cout << "5: sort data in ascending order by email" << endl;
		cout << "9: exit" << endl;
		cin >> select;
	} while (select != 9 && (select < 0 || select > 5)); //repeats menu if invalid entry
	if (select >=1 && select <=5) //sents to sort function if 1-5 chosen
	{
		sort(select, size, pschool);
		printNew(size, pschool);
	}
	else if (!select)
		printOrig(school, size);
}

void sort(int select, int size, students *pschool[])
{
	int index;
	int count;
	int count2;
	students * temp;
	bool less = false; //flag to see if element to the right of the current element is smaller
	for (index = 0; index < size; index++)
	{
		for (count2 = index + 1; count2 < size; count2++)
		{
			count = index;
			switch (select)
			{
			case 1:
				less = (pschool[count2]->firstName < pschool[count]->firstName); //trigger flag
				break;
			case 2:
				less = (pschool[count2]->lastName < pschool[count]->lastName);
				break;
			case 3:
				less = (pschool[count2]->GPA < pschool[count]->GPA);
				break;
			case 4:
				less = (pschool[count2]->idNum < pschool[count]->idNum);
				break;
			case 5:
				less = (pschool[count2]->email < pschool[count]->email);
				break;
			}
			if (less)
			{
				count = count2; //actual sorting
				temp = pschool[count];
				pschool[count2] = pschool[index];
				pschool[index] = temp;
			}
		}
	}
}

void printOrig(students school[], int size)
{
	cout << "File output in newData.txt\n" << endl;
	cout << "First" << "\t" << "Last" << "\t" << "GPA" << "\t" << "ID" << "\t" << "email" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << school[i].firstName << "\t" << school[i].lastName << "\t" << school[i].GPA << "\t" << school[i].idNum << "\t" << school[i].email << endl;
	}
	cout << "\t" << endl;
}

void printNew(int size, students *pschool[])
{
	cout << "File output in newData.txt\n" << endl;
	cout << "First" << "\t" << "Last" << "\t" << "GPA" << "\t" << "ID" << "\t" << "email" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << pschool[i]->firstName << "\t" << pschool[i]->lastName << "\t" << pschool[i]->GPA << "\t" << pschool[i]->idNum << "\t" << pschool[i]->email << endl;
	}
	cout << "\t" << endl;
}
/*
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
0
File output in newData.txt

Michael Jee     3.5     999999  m_jee@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com

Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
1
File output in newData.txt

Angus   Hagan   1.5     523725  a_hagan@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Michael Jee     3.5     999999  m_jee@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com

Continue? (Y/N)
Y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
2
File output in newData.txt

Kye     Baker   3.4     457921  k_baker@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com
Michael Jee     3.5     999999  m_jee@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com

Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
3
File output in newData.txt

Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Michael Jee     3.5     999999  m_jee@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com

Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
4
File output in newData.txt

Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Michael Jee     3.5     999999  m_jee@gmail.com

Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
5
File output in newData.txt

Angus   Hagan   1.5     523725  a_hagan@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Michael Jee     3.5     999999  m_jee@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com

Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
0
File output in newData.txt

Michael Jee     3.5     999999  m_jee@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com

Continue? (Y/N)
n
File processing complete. Output in dataOut.txt
Press any key to continue . . .

Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
9
Continue? (Y/N)
N
File processing complete. Output in dataOut.txt
Press any key to continue . . .

***testing how continue works with exiting
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
9
Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit

***when data file is too large
Warning. File size too large. Data output is truncated.

Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
0
File output in newData.txt

First   Last    GPA     ID      email
Trinity Heath   3.8     423168  t_heath@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com

Continue? (Y/N)
y
Hello. This program will read data from the file "dataIn.txt" and output it sorted or unsorted into "dataOut.txt".
0: output data unsorted
1: sort data in ascending order by first name
2: sort data in ascending order by last name
3: sort data in ascending order by GPA
4: sort data in ascending order by ID number
5: sort data in ascending order by email
9: exit
1
File output in newData.txt

First   Last    GPA     ID      email
Angus   Hagan   1.5     523725  a_hagan@gmail.com
Annabel Willis  2.1     432816  a_willis@gmail.com
Ashton  Simmons 2.2     986235  a_simmons@gmail.com
Billie  Bernal  4.0     653453  b_bernal@gmail.com
Farah   Granger 2.5     468513  f_graing@gmail.com
Harvey  Brown   2.3     351826  h_fernan@gmail.com
Jemima  Lovell  1.5     567831  j_lovell@gmail.com
Julia   Crouch  2.4     468315  j_crouch@gmail.com
Kaci    Ridley  4.0     624872  k_ridley@gmail.com
Katerin Dunlap  0.0     645314  c_dunlap@gmail.com
Keiran  Lowe    2.4     457358  k_lowe@gmail.com
Kye     Baker   3.4     457921  k_baker@gmail.com
Melissa Barajas 3.8     657325  m_barajas@gmail.com
Noel    O'Ryan  3.4     526458  n_oryan@gmail.com
Rachel  Todd    3.3     597325  r_todd@gmail.com
Rowan   Odonnel 2.9     653482  r_odonn@gmail.com
Sulaman Mcdonal 3.4     165724  s_mcdon@gmail.com
Tiffany Burrows 2.8     435792  t_burrows@gmail.com
Trinity Heath   3.8     423168  t_heath@gmail.com

Continue? (Y/N)
n
File processing complete. Output in dataOut.txt
Press any key to continue . . .
*/