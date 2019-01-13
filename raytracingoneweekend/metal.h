#pragma once

#include "material.h"
#include "utilities.h"

namespace rt
{
	class Metal : public Material
	{
	public:
		Metal(const Vector3f& aAlbedo) : mAlbedo{ aAlbedo } {}

		bool scatter(const Ray& aRayIn, const HitRecord& aHitRecord, Vector3f& aAttenuation, Ray& aScattered) const override
		{
			Vector3f reflected = reflect(aRayIn.direction(), aHitRecord.normal);
			aScattered = Ray(aHitRecord.p, reflected);
			aAttenuation = mAlbedo;
			return (Vector3f::dot(aScattered.direction(), aHitRecord.normal) > 0.0f);
		}

	private:
		Vector3f mAlbedo;

	};
}