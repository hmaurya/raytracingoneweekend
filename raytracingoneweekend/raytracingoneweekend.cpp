// raytracingoneweekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>

#include "ppm.h"

void writePPM(const std::string& aFilepath, const int aWidth, const int aHeight)
{
	// TODO get a simple logger from github
	std::cout << "Input filepath is " << aFilepath << std::endl;
	std::ofstream writeStream(aFilepath.c_str());

	const unsigned int MAXVALUE = UCHAR_MAX;

	if (writeStream.is_open()) {
		writeStream << "P3" << "\n";
		writeStream << aWidth << " " << aHeight << "\n";

		writeStream << MAXVALUE << "\n";

		unsigned int red = MAXVALUE;
		unsigned int green = MAXVALUE;
		unsigned int blue = MAXVALUE;

		for (int row = aHeight - 1; row >= 0; --row) {
			for (int col = 0; col < aWidth; ++col) {

				float r = static_cast<float>(col) / static_cast<float>(aWidth);
				float g = static_cast<float>(row) / static_cast<float>(aHeight);
				float b = 0.2f;

				red = static_cast<int>(255.99 * r);
				green = static_cast<int>(255.99 * g);
				blue = static_cast<int>(255.99 * b);

				writeStream << red << " " << green << " " << blue << " ";
			}
			writeStream << "\n";
		}

		writeStream.close();
	}
	else {
		std::cout << "unable to open the file!" << std::endl;
	}
}


int main()
{
    std::cout << "Hello World!\n"; 

	std::string file("sample.ppm");
	writePPM(file, 200, 100);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
