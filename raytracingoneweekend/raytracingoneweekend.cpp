// raytracingoneweekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "ppm.h"
#include "Vector3.h"
#include "ray.h"
#include "hitable.h"

using namespace rt;


float hitSphere(const Vector3f& aCenter, float aRadius, const Ray& aRay)
{
	Vector3f oc = aRay.origin() - aCenter;
	float a = Vector3f::dot(aRay.direction(), aRay.direction());
	float b = 2.0f * Vector3f::dot(aRay.direction(), oc);
	float c = Vector3f::dot(oc, oc) - aRadius * aRadius;

	float discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0.f) {
		return -1.0f;
	}
	else {
		return (-b - sqrtf(discriminant)) / (2.0f * a);
	}
}

Vector3f color(const Ray& aRay)
{
	Vector3f sphereCenter = Vector3f(0.0f, 0.0f, -1.0f);
	float t = hitSphere(Vector3f(0.0f, 0.0f, -1.0f), 0.5, aRay);
	if (t > 0.0f) {
		Vector3f normal = unitVector(aRay.pointAtParameter(t) - sphereCenter);
		return 0.5f * Vector3f(normal.x() + 1.0f, normal.y() + 1.0f, normal.z() + 1.0f);
	}

	Vector3f unit_direction = unitVector(aRay.direction());
	// mapping [-1,1] -> [0-1]
	t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t)*Vector3f(1.0f, 1.0f, 1.0f) + t * Vector3f(0.5f, 0.7f, 1.0f);
}

Vector3f color(const Ray& aRay, const Hitable& aHitable)
{
	Vector3f sphereCenter = Vector3f(0.0f, 0.0f, -1.0f);
	
	HitRecord hitRecord;

	float t = aHitable.hit(aRay, 0.0f, FLT_MAX, hitRecord);
	if (t > 0.0f) {
		Vector3f normal = hitRecord.normal;
		return 0.5f * Vector3f(normal.x() + 1.0f, normal.y() + 1.0f, normal.z() + 1.0f);
	}

	Vector3f unit_direction = unitVector(aRay.direction());
	// mapping [-1,1] -> [0-1]
	t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t)*Vector3f(1.0f, 1.0f, 1.0f) + t * Vector3f(0.5f, 0.7f, 1.0f);
}

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


		Vector3f lowerLeftCorner{ -2.0, -1.0, -1.0 };
		Vector3f horizontal { 4.0, 0.0, 0.0 };
		Vector3f verticle { 0.0, 2.0, 0.0 };
		Vector3f origin { 0.0, 0.0, 0.0 };


		for (int row = aHeight - 1; row >= 0; --row) {
			for (int col = 0; col < aWidth; ++col) {

				float u = static_cast<float>(col) / static_cast<float>(aWidth);
				float v = static_cast<float>(row) / static_cast<float>(aHeight);

				Ray r(origin, lowerLeftCorner + u * horizontal + v * verticle);
				Vector3f pickedColor = color(r);

				red = static_cast<int>(255.99 * pickedColor[0]);
				green = static_cast<int>(255.99 * pickedColor[1]);
				blue = static_cast<int>(255.99 * pickedColor[2]);

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
