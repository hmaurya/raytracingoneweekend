// raytracingoneweekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <time.h>

#include "ppm.h"
#include "vector3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "camera.h"
#include "utilities.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"


using namespace rt;

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

Vector3f color(const Ray& aRay, const std::vector<Hitable*>& aHitables, int aDepth)
{
	HitRecord record;

	if (Sphere::hit(aRay, 0.001f, std::numeric_limits<float>::max(), aHitables, record)) {

		Ray scattered;
		Vector3f attenuation;
		if (aDepth < 50 && record.material->scatter(aRay, record, attenuation, scattered)) {
			return attenuation * color(scattered, aHitables, aDepth + 1);
		}
		else {
			return Vector3f(0.0f, 0.0f, 0.0f);
		}
	}
	else {

		Vector3f unit_direction = unitVector(aRay.direction());
		// mapping [-1,1] -> [0-1]
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t)*Vector3f(1.0f, 1.0f, 1.0f) + t * Vector3f(0.5f, 0.7f, 1.0f);
	}
}

void writePPM(const std::string& aFilepath, const int aWidth, const int aHeight, const int aNumSamplesPerRay)
{
	// TODO get a simple logger from github
	std::cout << "Input filepath is " << aFilepath << std::endl;
	std::ofstream writeStream(aFilepath.c_str());
	
	srand((unsigned int)time(0));

	const unsigned int MAXVALUE = UCHAR_MAX;

	if (writeStream.is_open()) {
		writeStream << "P3" << "\n";
		writeStream << aWidth << " " << aHeight << "\n";

		writeStream << MAXVALUE << "\n";

		unsigned int red = MAXVALUE;
		unsigned int green = MAXVALUE;
		unsigned int blue = MAXVALUE;

		std::vector<Hitable*> spheres;

		spheres.push_back(new Sphere(Vector3f(0., 0., -1.), 0.5, new Lambertian(Vector3f(0.1f, 0.2f, 0.5f))));
		spheres.push_back(new Sphere(Vector3f(0., -100.5, -1), 100.0f, new Lambertian(Vector3f(0.8f, 0.8f, 0.0f))));
		spheres.push_back(new Sphere(Vector3f(1., 0., -1.), 0.5f, new Metal(Vector3f(0.8f, 0.6f, 0.2f), 0.3f)));
		//spheres.push_back(new Sphere(Vector3f(-1., 0., -1.), 0.5f, new Dielectric(1.5f)));
		spheres.push_back(new Sphere(Vector3f(-1., 0., -1.), -0.45f, new Dielectric(1.5f)));

		/*float R = cos((float)M_PI / 4);
		spheres.push_back(new Sphere(Vector3f(-R, 0., -1.), R, new Lambertian(Vector3f(0.f, 0.f, 1.f))));
		spheres.push_back(new Sphere(Vector3f(R, 0., -1.), R, new Lambertian(Vector3f(1.f, 0.f, 0.f))));*/

		Camera cam(Vector3f(-2, 2, 1), Vector3f(0, 0, -1), Vector3f(0, 1, 0), 
			90.0f, static_cast<float>(aWidth) / static_cast<float>(aHeight));

		for (int row = aHeight - 1; row >= 0; --row) {
			for (int col = 0; col < aWidth; ++col) {

				Vector3f pickedColor(0., 0.,0.);
				for (int ns = 0; ns < aNumSamplesPerRay; ++ns) {

					float rc = (float)rand() / (float)RAND_MAX;
					float rr = (float)rand() / (float)RAND_MAX;

					float u = static_cast<float>(col + rc) / static_cast<float>(aWidth);
					float v = static_cast<float>(row + rr) / static_cast<float>(aHeight);
					Ray r = cam.ray(u, v);
					pickedColor += color(r, spheres, 0);
				}
				pickedColor = pickedColor / (float)aNumSamplesPerRay;

				red = static_cast<int>(255.99 * sqrtf(pickedColor[0]));
				green = static_cast<int>(255.99 * sqrtf(pickedColor[1]));
				blue = static_cast<int>(255.99 * sqrtf(pickedColor[2]));

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
	int width = 200;
	int height = 100;
	int numSamplesPerRay = 100;
	writePPM(file, width, height, numSamplesPerRay);
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
