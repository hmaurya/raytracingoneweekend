#pragma once

#include "ray.h"
#include "Vector3.h"
#include "hitable.h"

namespace rt
{
	class Material
	{
	public:
		virtual bool scatter(const Ray& aRayIn, const HitRecord& aHitRecord, Vector3f& aAttenuation, Ray& aScattered) const = 0;
	};

}