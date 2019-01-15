#pragma once

#include "vector3.h"
#include "ray.h"
#include <corecrt_math_defines.h>

namespace rt {

	class Camera
	{
	public:

		Camera(float aVerticleFoVInDegrees, float aAspectRatio) {
			float thetaInRadians = aVerticleFoVInDegrees * (float)M_PI / 180.0f;
			float halfHeight = tan(thetaInRadians / 2.0f);
			float halfWidth = aAspectRatio * halfHeight;

			mLowerLeftCorner = Vector3f{ -halfWidth, -halfHeight, -1.0 };
			mHorizontal = Vector3f{ 2.0f * halfWidth, 0.0, 0.0 };
			mVerticle = Vector3f{ 0.0, 2.0f * halfHeight, 0.0 };
			mOrigin = Vector3f{ 0.0, 0.0, 0.0 };
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