#include "pch.h"
#include "ppm.h"
#include <fstream>
#include <random>

#include"vector3.h"
#include "ray.h"

void rt::writeRandomPPM(const std::string& aFilepath, const int aWidth, const int aHeight) 
{
	// TODO get a simple logger from github
	
	Vector3f origin{ 2.123f, 3.0f, 4.0f };
	Vector3f direction{ 1.0, 0.0f, 0.0f };
	Vector3<int> veci{};

	std::cout << origin;
	
	//Vector3f.cross(origin, direction);
	Vector3f tempMul = origin * 5.0f;
	Vector3f temp = origin / 2.0f;
	Ray ray{origin, direction};


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

