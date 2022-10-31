#include "vec3.h"
#include <sstream>
#include <Util/HAssert.h>

namespace Height
{
	vec3::vec3() : x(0.0f), y(0.0f), z(0.0f)
	{
	}

	vec3::vec3(const float xx, const float yy, const float zz) : x(xx), y(yy), z(zz)
	{
	}

	vec3::vec3(float scalar) : x(scalar), y(scalar), z(scalar)
	{
	}


	vec3::vec3(const vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	std::string vec3::ToString() const
	{
		std::stringstream ss;
		ss << "vec3: (" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}


	float vec3::Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	float vec3::Length2()
	{
		return (x * x + y * y + z * z);
	}

	float vec3::Length(const vec3& vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
	float vec3::Length2(const vec3& vec)
	{
		return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	vec3 vec3::Normalize(const vec3& vec)
	{
		float lenght = vec3::Length(vec);
	
		if (lenght <= 0.0f)
			return vec;

		return vec3(vec.x / lenght, vec.y / lenght, vec.z / lenght);
	}

	vec3  vec3::Normalized()
	{
		float length = this->Length();

		HT_ASSERT(length > 0.0f, "Cannot divide by zero");

		return vec3(x / length, y / length, z / length);
	}

	Height::vec3 vec3::lerp(const vec3& start, const vec3& end, float alpha)
	{
		vec3 aux;
		
		aux.x = (start.x * (1.0f - alpha)) + (end.x * alpha);
		aux.y = (start.y * (1.0f - alpha)) + (end.y * alpha);
		aux.z = (start.z * (1.0f - alpha)) + (end.z * alpha);

		return aux;
	}

	vec3  vec3::Cross(const vec3& other)
	{
		return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	vec3  vec3::Cross(const vec3& first, const vec3& second)
	{
		return vec3(first.y * second.z - first.z * second.y,
					first.z * second.x - first.x * second.z,
					first.x * second.y - first.y * second.x);
	}

	float vec3::Dot(const vec3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	float vec3::Dot(const vec3& first, const vec3& second)
	{
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}

	vec3 vec3::Max(const vec3& other) const
	{
		vec3 result;

		for (uint8_t x = 0; x < 3; x++)
			result[x] = elements[x] > other[x] ? elements[x] : other[x];

		return result;
	}

	float vec3::Max() const
	{
		float maxVal = elements[0];

		for (uint8_t x = 0; x < 3; x++)
			if (elements[x] > maxVal) maxVal = elements[x];

		return maxVal;
			
	}

	vec3& vec3::add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3& vec3::subtract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3& vec3::multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Height::vec3& vec3::multiply(const float& other)
	{
		x *= other;
		y *= other;
		z *= other;

		return *this;
	}

	vec3& vec3::divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}



	vec3& vec3::operator+=(const vec3& other)
	{
		return add(other);
	}

	Height::vec3& vec3::operator*=(const float& other)
	{
		return multiply(other);
	}

	vec3& vec3::operator-=(const vec3& other)
	{
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other)
	{
		return multiply(other);
	}


	vec3& vec3::operator/=(const vec3& other)
	{
		return divide(other);
	}



	bool vec3::operator==(const vec3& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool vec3::operator!=(const vec3& other)
	{
		return (!(*this == other));
	}


	std::ostream& operator<<(std::ostream& os, const Height::vec3& vec)
	{
		return os << vec.ToString();
	}

	vec3 operator+(vec3 left, const vec3& right)
	{
		return left.add(right);
	}
	vec3 operator-(vec3 left, const vec3& right)
	{
		return left.subtract(right);
	}
	vec3 operator*(vec3 left, const vec3& right)
	{
		return left.multiply(right);
	}
	vec3 operator/(vec3 left, const vec3& right)
	{
		return left.divide(right);
	}

	vec3 operator*(vec3 left, const float& other)
	{
		return left.multiply(other);
	}

}