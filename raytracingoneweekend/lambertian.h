#pragma once

#include "material.h"
#include "utilities.h"

namespace rt
{
	class Lambertian : public Material
	{
	public:
		Lambertian(const Vector3f& aAlbedo) : mAlbedo {aAlbedo} {}

		bool scatter(const Ray& /*aRayIn*/, const HitRecord& aHitRecord, Vector3f& aAttenuation, Ray& aScattered) const override
		{
			Vector3f target = aHitRecord.p + aHitRecord.normal + randomPointInUnitSphere();
			aScattered = Ray(aHitRecord.p, target - aHitRecord.p);
			aAttenuation = mAlbedo;
			return true;
		}

		void setAlbedo(const Vector3f& aAlbedo)
		{
			mAlbedo = aAlbedo;
		}

	private:
		Vector3f mAlbedo;
	};
}