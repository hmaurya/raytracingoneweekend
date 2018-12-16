#pragma once

#include <iostream>
#include <math.h>

namespace rt
{

	template <typename T> class Vector3;
	template <typename T> std::ostream& operator<<(std::ostream&, const Vector3<T>&);

	template<typename T>
	class Vector3 
	{
	public:

		Vector3() = default;
		// c++ 11 construtor list initialization
		Vector3(T aX, T aY, T aZ)
			: m_e{ aX, aY, aZ } {}
		
		friend std::ostream& operator<< <T>(std::ostream&, const Vector3<T>&);
		
		template <typename U>
		friend inline Vector3<U> operator*(float value, const Vector3<U>& aVector);
		template <typename U>
		friend inline Vector3<U> operator*(const Vector3<U>& aVector, float aValue);
		template <typename U>
		friend inline Vector3<U> operator/(const Vector3<U>& aVector, float aValue);


		static Vector3 forward() { return Vector3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }
		static Vector3 right() { return Vector3(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
		static Vector3 up() { return Vector3(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

		inline T x() const { return m_e[0]; }
		inline T y() const { return m_e[1]; }
		inline T z() const { return m_e[2]; }
		// TODO we can do a fucntion alias https://www.fluentcpp.com/2017/10/27/function-aliases-cpp/ here
		inline T r() const { return m_e[0]; }
		inline T g() const { return m_e[1]; }
		inline T b() const { return m_e[2]; }

		static T dot(Vector3<T> aVectorA, Vector3<T> aVectorB)
		{
			return 
				(aVectorA.x() * aVectorB.x()) +
				(aVectorA.y() * aVectorB.y()) +
				(aVectorA.z() * aVectorB.z());
		}

		static Vector3<T> cross(Vector3<T> aVectorA, Vector3<T> aVectorB)
		{
			return Vector3<T>
			{
				(aVectorA.y() * aVectorB.z() - aVectorB.y() * aVectorA.z()),
					-(aVectorA.x() * aVectorB.z() - aVectorB.x() * aVectorA.z()),
					(aVectorA.x() * aVectorB.y() - aVectorB.x() * aVectorA.y())
			};
		}

		inline float length() const {
			return sqrtf((m_e[0] * m_e[0]) + (m_e[1] * m_e[1]) + (m_e[2] * m_e[2]));
		}

		inline Vector3 operator+(const Vector3& aRHS) const { 
			return Vector3(this->m_e[0] + aRHS.x(), this->m_e[1] + aRHS.y(), this->m_e[2] + aRHS.z());
		}
		
		inline Vector3 operator-(const Vector3& aRHS) const {
			return Vector3(this->m_e[0] - aRHS.x(), this->m_e[1] - aRHS.y(), this->m_e[2] - aRHS.z());
		}

		inline const Vector3& operator+() const { return *this; }
		inline Vector3 operator-() { return Vector3(-this->m_e[0], -this->m_e[1], -this->m_e[2]); }

		inline const T& operator[](int aIndex) const { return m_e[aIndex]; }
		inline T& operator[](int aIndex) { return m_e[aIndex]; }

		inline Vector3& operator+=(const Vector3& aRHS) {
			this->m_e[0] += aRHS.m_e[0];
			this->m_e[1] += aRHS.m_e[1];
			this->m_e[2] += aRHS.m_e[2];

			return *this;
		}

		inline Vector3& operator-=(const Vector3& aRHS) {
			this->m_e[0] -= aRHS.m_e[0];
			this->m_e[1] -= aRHS.m_e[1];
			this->m_e[2] -= aRHS.m_e[2];

			return *this;
		}
		
		// TODO listed in the book as the header. But does not make sense as Vector multiplication is defined as scaler multiplication
		/*inline Vector3& operator*=(const Vector3& aRHS) {
			this->m_e[0] *= aRHS.m_e[0];
			this->m_e[1] *= aRHS.m_e[1];
			this->m_e[2] *= aRHS.m_e[2];

			return *this;
		}*/

		inline Vector3& operator*=(const T& aRHS) {
			this->m_e[0] = this->m_e[0] * aRHS;
			this->m_e[1] = this->m_e[1] * aRHS;
			this->m_e[2] = this->m_e[2] * aRHS;

			return *this;
		}

		inline Vector3& operator/=(const T& aRHS) {
			this->m_e[0] = this->m_e[0] / aRHS;
			this->m_e[1] = this->m_e[1] / aRHS;
			this->m_e[2] = this->m_e[2] / aRHS;

			return *this;
		}

		

	private:
		T m_e[3];

	};
	
	template<typename T>
	inline Vector3<T> operator*(float value, const Vector3<T>& aVector) {

		return Vector3<T>(aVector.m_e[0] * value,
			aVector.m_e[1] * value,
			aVector.m_e[2] * value);
	}

	template<typename T>
	inline Vector3<T> operator*(const Vector3<T>& aVector, float value) {

		return Vector3<T>(aVector.m_e[0] * value,
			aVector.m_e[1] * value,
			aVector.m_e[2] * value);
	}

	template<typename T>
	inline Vector3<T> operator/(const Vector3<T>& aVector, float value) {

		return Vector3<T>(aVector.m_e[0] / value,
			aVector.m_e[1] / value,
			aVector.m_e[2] / value);
	}

    // https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class
	template<typename T>
	std::ostream& operator<<(std::ostream & oStream, const Vector3<T>& input)
	{
		oStream << input.x() << " " << input.y() << " " << input.z();
		return oStream;
	}


	// free functions
	template <typename T>
	inline Vector3<T> unitVector(const Vector3<T>& aVector)
	{
		return aVector / aVector.length();
	}

	typedef Vector3<float> Vector3f;
}