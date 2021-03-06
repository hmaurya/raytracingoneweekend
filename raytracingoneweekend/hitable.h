#pragma once

#include "ray.h"
#include "vector3.h"

namespace rt
{

	class Material;

	struct HitRecord {
		float t;
		Vector3f p;
		Vector3f normal;
		Material *material;
	};

	class Hitable
	{
	public: 
		virtual bool hit(const Ray& aRay, float t_min, float t_max, HitRecord& hitRecord) const = 0;
	};

}