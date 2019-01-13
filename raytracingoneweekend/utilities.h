#pragma once

#include "Vector3.h"

namespace rt
{
	inline float randFloat()
	{
		// make sure srand is called somewhere before using this method
		return (float)rand() / (float)RAND_MAX;
	}

	Vector3f randomPointInUnitSphere() {
		Vector3f p;

		do {
			p = 2.0f * Vector3f(randFloat(), randFloat(), randFloat()) - Vector3f(1.0f, 1.0f, 1.0f);
		} while (p.squaredLength() >= 1.0f);

		return p;
	}

	Vector3f reflect(const Vector3f& aIn, const Vector3f& aNormal)
	{
		return aIn - 2.0f * Vector3f::dot(aIn, aNormal) * aNormal;
	}

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
}