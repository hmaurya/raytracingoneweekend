#include "pch.h"
#include "ppm.h"
#include <fstream>
#include <random>

#include"Vector3.h"

void rt::writeRandomPPM(const std::string& aFilepath, const int aWidth, const int aHeight) 
{
	// TODO get a simple logger from github
	
	Vector3f vec{ 2.123f, 3.0f, 4.0f };

	std::cout << vec;
	
	std::cout << "Input filepath is " << aFilepath << std::endl;
	std::ofstream writeStream(aFilepath.c_str());

	const unsigned int MAXVALUE = UCHAR_MAX;
	// intialize a uniform real dist
	std::random_device rd;
	std::mt19937 gen(rd());

	//std::uniform_real_distribution<> distribution(0.0f, 1.0f);
	std::poisson_distribution<> distribution(0.5);
	if (writeStream.is_open()) {
		writeStream << "P3" << "\n";
		writeStream << aWidth << " " << aHeight << "\n";

		writeStream << MAXVALUE << "\n";
		
		unsigned int red = MAXVALUE;
		unsigned int green = MAXVALUE;
		unsigned int blue = MAXVALUE;

		for (int row = 0; row < aHeight; ++row) {
			for (int col = 0; col < aWidth; ++col) {

				red = MAXVALUE * distribution(gen);
				green = MAXVALUE * distribution(gen);
				blue = MAXVALUE * distribution(gen);

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