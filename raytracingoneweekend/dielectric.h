#pragma once

#include "material.h"
#include "utilities.h"

namespace rt
{
	class Dielectric : public Material
	{
	public:
		Dielectric(float aRefIndex) : mRefIndex(aRefIndex) {}

		virtual bool scatter(const Ray& aRayIn, const HitRecord& aHitRecord, Vector3f& aAttenuation, Ray& aScattered) const override
		{
			Vector3f outwardNormal;
			Vector3f reflected = reflect(aRayIn.direction(), aHitRecord.normal);
			float ni_over_nt;
			aAttenuation = Vector3f(1.0f, 1.0f, 1.0f);
			Vector3f refracted;
			float reflect_prob;
			float cosine;
			if (Vector3f::dot(aRayIn.direction(), aHitRecord.normal) > 0.0f) {
				outwardNormal = -aHitRecord.normal;
				ni_over_nt = mRefIndex;
				cosine = mRefIndex * Vector3f::dot(aRayIn.direction(), aHitRecord.normal) / aRayIn.direction().length();
			}
			else {
				outwardNormal = aHitRecord.normal;
				ni_over_nt = 1.0f / mRefIndex;
				cosine = -Vector3f::dot(aRayIn.direction(), aHitRecord.normal) / aRayIn.direction().length();
			}

			if (refract(aRayIn.direction(), outwardNormal, ni_over_nt, refracted)) {
				reflect_prob = schlick(cosine, mRefIndex);
			}
			else {
				reflect_prob = 1.0f;
			}

			if (randFloat() < reflect_prob) {
				aScattered = Ray(aHitRecord.p, reflected);
			}
			else {
				aScattered = Ray(aHitRecord.p, refracted);
			}
			return true;
		}

	private:
		float mRefIndex;
	};
}