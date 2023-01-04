#include <cmath>
#include "Vector4.h"
#include "Vector3.h"
#include "Nare/Mathf/Mathf.h"
#include "Nare/Core.h"


float Vector4::operator[](const unsigned int index) const
{
	switch(index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}

	NR_CORE_ASSERT(false, "This vector: ", ToString(), "was attempted to be accessed in the wrong index using the index operator!");
}

Vector4 Vector4::operator/(float scalar) const
{
	assert(Mathf::Approximately(scalar, 0));
	return { x / scalar, y / scalar, z / scalar, w / scalar };
}

Vector4& Vector4::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4::Vector4(const float& scalar)
	: x(scalar), y(scalar), z(scalar), w(scalar)
{
}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}

Vector4::Vector4(const Vector3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(0)
{

}

Vector4::~Vector4()
{

}

bool Vector4::IsZero() const
{
	return Mathf::ApproximatelyZero(x) && Mathf::ApproximatelyZero(y) && Mathf::ApproximatelyZero(z) && Mathf::ApproximatelyZero(w);
}

Vector4 Vector4::operator+(const Vector4& rhs) const
{
	return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
}

Vector4& Vector4::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

Vector4 Vector4::operator-(const Vector4& rhs) const
{
	return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

Vector4 Vector4::operator-() const
{
	return { -x, -y, -z, -w };
}

Vector4 Vector4::operator*(float scalar) const
{
	return { scalar * x,scalar * y,scalar * z, scalar * w };
}

Vector4& Vector4::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

bool Vector4::operator==(const Vector4& rhs) const
{
	return Mathf::Approximately(x, rhs.x) &&
			Mathf::Approximately(y, rhs.y) &&
			Mathf::Approximately(z, rhs.z) &&
			Mathf::Approximately(w, rhs.w);
}

bool Vector4::operator!=(const Vector4& rhs) const
{
	return !Mathf::Approximately(x, rhs.x) ||
			!Mathf::Approximately(y, rhs.y) ||
			!Mathf::Approximately(z, rhs.z) ||
			!Mathf::Approximately(w, rhs.w);
}

Vector4& Vector4::operator=(const Vector4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

float Vector4::Length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSquared() const
{
	return (x * x + y * y + z * z + w * w);
}

float Vector4::Distance(const Vector4& rhs) const
{
	return (*this - rhs).Length();
}

float Vector4::DistanceSquared(const Vector4& rhs) const
{
	return (*this - rhs).LengthSquared();
}

float Vector4::Distance(const Vector4& lhs, const Vector4& rhs)
{
	return (lhs - rhs).Length();
}

float Vector4::DistanceSquared(const Vector4& lhs, const Vector4& rhs)
{
	return (lhs - rhs).LengthSquared();
}

float Vector4::Dot(const Vector4& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

Vector4 Vector4::Normalized(void) const 
{
	float l = Length();
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(l), "Division by zero")
	return Vector4(*this) /= l;
}

Vector4& Vector4::Normalize(void)
{
	float l = Length();
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(l), "Division by zero")
	return *this /= l;
}


std::ostream& operator<< (std::ostream& os, Vector4& rhs)
{
	os << "[x: " << rhs.x << " , y: " << rhs.y << " , z: " << rhs.z << " , w: " << rhs.w <<  " ]";
	return os;
}

Vector4 operator*( float scalar, const Vector4& rhs )
{
	return rhs * scalar;
}

std::string Vector4::ToString() const
{
	std::stringstream ss;
	ss << this;
	return ss.str();
}