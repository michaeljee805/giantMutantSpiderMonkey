// Jee, Michael			CS546 Section 13495	 4/1/19
// Second Laboratory Assignment - Map NYC Taxi Destinations

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "windows.h"
using namespace std;
// The following defines the size of the square image in pixels.

#define IMAGE_SIZE 256*4
#define GRADIENT 256*4
#define SBOUND 40.700455 //40.700455 North latitude
#define NBOUND 40.830509 //40.830509 North latitude
#define LAT_RANGE 40.830509-40.700455
#define WBOUND -74.045033 //74.045033 West longitude
#define EBOUND -73.914979 //73.914979 West longitude
#define LON_RANGE 74.045033-73.914979

void input(ifstream & infile, float&, int bitLoc[]);
int convLatBit(double lat);
int convLonBit(double lon); 

int main(int argc, char* argv[])
{
	BITMAPFILEHEADER bmfh;

	BITMAPINFOHEADER bmih;

	char colorTable[GRADIENT];

	char bits[IMAGE_SIZE][IMAGE_SIZE] = { -1 };

	ifstream infile;
	infile.open("L2Data10K.dat",ios::binary); //L2Data10K.dat
	if (!infile)
	{
		cout << "Error opening file.";
		exit(1);
	}

	float location[IMAGE_SIZE * 2 * 4] = { 0 };
	int bitLoc[IMAGE_SIZE * 2 * 4] = { 0 };

	int i, j;

	// Define and open the output file. 
	ofstream bmpOut("foo.bmp", ios::out + ios::binary);
	if (!bmpOut) {
		cout << "...could not open file, ending.";
		return -1;
	}

	// Initialize the bit map file header with static values.
	bmfh.bfType = 0x4d42;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(bmfh) + sizeof(bmih) + sizeof(colorTable);
	bmfh.bfSize = bmfh.bfOffBits + sizeof(bits);

	// Initialize the bit map information header with static values.
	bmih.biSize = 40;
	bmih.biWidth = IMAGE_SIZE;
	bmih.biHeight = IMAGE_SIZE;
	bmih.biPlanes = 1;
	bmih.biBitCount = 8; //colors, 2^biBitCount=num of colors
	bmih.biCompression = 0;
	bmih.biSizeImage = IMAGE_SIZE * IMAGE_SIZE;
	bmih.biXPelsPerMeter = 2835;  // magic number, see Wikipedia entry
	bmih.biYPelsPerMeter = 2835;
	bmih.biClrUsed = GRADIENT;
	bmih.biClrImportant = 0;

	// Build color table.
	for (i = 0; i < 256; ++i) {
		j = i * 4;
		colorTable[j] = colorTable[j + 1] = colorTable[j + 2] = colorTable[j + 3] = i;
		//^blue			^green				^red				^black
		// for your edification, try setting one of the first three values to 255 instead of i
		// and see what it does to the generated bit map.
	}

	for (int i = 0; i < IMAGE_SIZE * 2 * 4; ++i)
	{
		infile.read((char*)&location[i], sizeof(float));
		//cout << location[i] << " ";
		if (i % 2)
		{
			bitLoc[i] = convLonBit(location[i]);
		}
		else
		{
			bitLoc[i] = convLatBit(location[i]);
		}
		/*cout << bitLoc[i] << " ";
		if (i % 2)
			cout << endl;*/
	}

	for (int i = 0; i < IMAGE_SIZE * 2 * 4; i += 2)
	{
		if (bits[bitLoc[i + 1]][bitLoc[i]] < 255) //plot via longitude, latitude
			bits[bitLoc[i + 1]][bitLoc[i]] = 255; //+=4 if more data read in
		//if (bits[bitLoc[i]][bitLoc[i + 1]] < 255) //plot via latitude, longitude
		//bits[bitLoc[i]][bitLoc[i + 1]] += 4;
	}

	// Write out the bit map.
	char* workPtr;
	workPtr = (char*)&bmfh;
	bmpOut.write(workPtr, 14);
	workPtr = (char*)&bmih;
	bmpOut.write(workPtr, 40);
	workPtr = &colorTable[0];
	bmpOut.write(workPtr, sizeof(colorTable));
	workPtr = &bits[0][0];
	bmpOut.write(workPtr, IMAGE_SIZE*IMAGE_SIZE);
	bmpOut.close();

	// Now let's look at our creation.
	system("mspaint foo.bmp");

	// Done.
	return 0;
}

/*void input(ifstream & infile, float &location, int bitLoc[])
{
	for (int i = 0; i < IMAGE_SIZE * 2 * 4; ++i)
	{
		infile.read((char*)&location[i],sizeof(float));
		//read in as latitude, longitude
		if (i % 2)
			bitLoc[i] = convLonBit(location[i]);
		//bitLoc[i] = convLatBit(location[i]);
		else
			bitLoc[i] = convLatBit(location[i]);
		//bitLoc[i] = convLonBit(location[i]);
	}
}*/

int convLatBit(double lat)
{
	if (lat > NBOUND || lat < SBOUND)
		return -1; //ignore coordinates if out of bounds
	else
	{
		lat -= SBOUND;
		lat /= LAT_RANGE;
		lat *= IMAGE_SIZE;
		return lat;
	}
}

int convLonBit(double lon)
{
	if (lon < WBOUND || lon > EBOUND)
		return -1; //ignore coordinates if out of bounds
	else
	{
		lon -= WBOUND;
		lon /= LON_RANGE;
		lon *= IMAGE_SIZE;
		return lon;
	}
}

//debug
/*input(infile, location, bitLoc);
for (int j = 0; j < IMAGE_SIZE * 2; j += 2)
{
cout << "j lat: " << j / 2 << "        " <<  location[j] << "      " << bitLoc[j] << endl;
cout << "j lon: " << j / 2 << "        " << location[j + 1] << "      " << bitLoc[j + 1] << endl;
}*/

/*debug
cout << convLatBit(40) << endl;
cout << convLatBit(41) << endl;
cout << convLatBit(40.75) << endl;
cout << convLonBit(73) << endl;
cout << convLonBit(75) << endl;
cout << convLonBit(74) << endl;*/
