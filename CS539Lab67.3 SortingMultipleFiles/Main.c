/*Jee, Michael
CS 539 Lab 6 and 7
11/26/18
This program will: take as input: last name, first name; street address; city and state; and zip code and
output a new file with the data in order with respect to zip code*/

#include "header.h"

int main()
{
	int size;
	Data *pdata[MAXSIZE]; /*original array*/
	Data *sortData[MAXSIZE]; /*sorted array*/
	size = inputAlloc(pdata, sortData); /*data allocation function*/
	sort(size, sortData); /*sorting*/
	output(size, sortData); /*outputting*/
	dealloc(size, pdata, sortData); /*deallocating function*/
	return 0;
}

/*
cmd code: E:\>
PierceCollege\CS539\CS539Lab67.3\Debug\CS539Lab67.3.exe<PierceCollege\CS539\CS539Lab67.3\Debug\address.txt>PierceCollege\CS539\CS539Lab67.3\Debug\addressNew.txt
*/
PierceCollege\(0)_current_term\CS546\MDJLab1.1\Debug\MDJLab1.1.exe<
/*
K1, K2
720 Eucalyptus Ave 105
Inglewood, CA
89030
O1, O2
7659 Mckinley Ave
Los Angeles, CA
90001
G1, G2
20253 Lorenzana Dr
Los Angeles, CA
90005
N1, N2
20044 Wells Dr
Beverly Hills, CA
90210
H1, H2
5241 Del Moreno Dr
Los Angeles, CA
91110
F1, F2
20225 Lorenzana Dr
Los Angeles, CA
91111
C1, C2
5142 Dumont Pl
Azusa, CA
91112
J1, J2
5135 Quakertown Ave
Thousand Oaks, CA
91362
M1, M2
4819 Quedo Pl
Westlake Village, CA
91362
A1, A2
20294 Lorenzana Dr
Woodland Hills, CA
91364
L1, L2
5021 Dumont Pl
Woodland Hills, CA
91364
D1, D2
20636 De Forest St
Woodland Hills, CA
91364
A1, A2
20294 Lorenzana Dr
Woodland Hills, CA
91364
E1, E2
4851 Poe Ave
Woodland Hills, CA
91364
B1, B2
19831 Henshaw St
Culver City, CA
94023
I1, I2
5332 Felice Pl
Stevenson Ranch, CA
94135
I1, I2
5332 Felice Pl
Stevenson Ranch, CA
94135
I1, I2
5332 Felice Pl
Stevenson Ranch, CA
94135

*/