#pragma once

#include "vector3.h"
#include "ray.h"
#include <corecrt_math_defines.h>

namespace rt {

	class Camera
	{
	public:

		Camera(const Vector3f& aLookFrom, 
			const Vector3f& aLookAt, 
			const Vector3f& aUp, 
			float aVerticleFoVInDegrees, 
			float aAspectRatio) 
		{
			Vector3f u, v, w;

			float thetaInRadians = aVerticleFoVInDegrees * (float)M_PI / 180.0f;
			float halfHeight = tan(thetaInRadians / 2.0f);
			float halfWidth = aAspectRatio * halfHeight;

			mOrigin = aLookFrom;
			w = unitVector(aLookFrom - aLookAt);
			u = unitVector(Vector3f::cross(aUp, w));
			v = Vector3f::cross(w, u);

			mLowerLeftCorner = mOrigin - halfWidth * u - halfHeight * v - w;

			mHorizontal = 2.0f * halfWidth * u;
			mVerticle = 2.0f * halfHeight * v;
		}

		Ray ray(float aU, float aV) {
			return Ray(mOrigin, (mLowerLeftCorner + aU * mHorizontal + aV * mVerticle) - mOrigin);
		}

	private:
		Vector3f mLowerLeftCorner;
		Vector3f mHorizontal;
		Vector3f mVerticle;
		Vector3f mOrigin;
	};

}