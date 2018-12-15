#pragma once

#include <iostream>

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
	
    // https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class
	template<typename T>
	std::ostream& operator<<(std::ostream & oStream, const Vector3<T>& input)
	{
		oStream << input.x() << " " << input.y() << " " << input.z();
		return oStream;
	}

	typedef Vector3<float> Vector3f;
}