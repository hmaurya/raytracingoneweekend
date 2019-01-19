#pragma once

#include "vector3.h"
#include "ray.h"
#include <corecrt_math_defines.h>
#include "utilities.h"

namespace rt {

	class Camera
	{
	public:

		Camera(const Vector3f& aLookFrom, 
			const Vector3f& aLookAt, 
			const Vector3f& aUp, 
			float aVerticleFoVInDegrees, 
			float aAspectRatio,
			float aAperture,
			float aFocusDist) 
		{
			mLensRadius = aAperture / 2.0f;

			float thetaInRadians = aVerticleFoVInDegrees * (float)M_PI / 180.0f;
			float halfHeight = tan(thetaInRadians / 2.0f);
			float halfWidth = aAspectRatio * halfHeight;

			mOrigin = aLookFrom;
			mW = unitVector(aLookFrom - aLookAt);
			mU = unitVector(Vector3f::cross(aUp, mW));
			mV = Vector3f::cross(mW, mU);

			mLowerLeftCorner = mOrigin - halfWidth * aFocusDist * mU - halfHeight * aFocusDist * mV - mW * aFocusDist;

			mHorizontal = 2.0f * halfWidth * aFocusDist *  mU;
			mVerticle = 2.0f * halfHeight * aFocusDist * mV;
		}

		Ray ray(float aU, float aV) {
			Vector3f randomPoint = mLensRadius * randomInUnitDisk();
			Vector3f offset = mU * randomPoint.x() + mV * randomPoint.y();
			return Ray(mOrigin + offset, (mLowerLeftCorner + aU * mHorizontal + aV * mVerticle) - mOrigin - offset);
		}

	private:
		Vector3f mLowerLeftCorner;
		Vector3f mHorizontal;
		Vector3f mVerticle;
		Vector3f mOrigin;
		Vector3f mU, mV, mW;
		float mLensRadius;
	};

}