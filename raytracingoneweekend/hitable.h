#pragma once

#include "ray.h"
#include "Vector3.h"

namespace rt
{

	struct HitRecord {
		float t;
		Vector3f p;
		Vector3f normal;
	};

	class Hitable
	{
	public: 
		virtual bool hit(const Ray& aRay, float t_min, float t_max, HitRecord& hitRecord) const = 0;
	};

}