#include <cmath>
#include "Vector3.h"
#include "Vector2.h"
#include "Nare/Mathf/Mathf.h"
#include "Nare/Core/Core.h"


float Vector3::operator[](const unsigned int index) const
{
	switch(index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
	NR_CORE_ASSERT(false, "This vector: ", ToString(), "was attempted to be accessed in the wrong index using the index operator!");
}
Vector3::Vector3(const float& scalar)
	: x(scalar), y(scalar), z(scalar)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

Vector3::Vector3(const Vector2& rhs)
	: x(rhs.x), y(rhs.y), z(0)
{

}

Vector3::Vector3(const Vector2& rhs, float z)
	: x(rhs.x), y(rhs.y), z(z)
{
}

Vector3::~Vector3()
{
}

void Vector3::Set(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector3 Vector3::operator/(float scalar) const
{
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(scalar), "Dividing by zero.");
	return { x / scalar, y / scalar, z / scalar };
}

Vector3& Vector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

void Vector3::SetZero()
{
	Set(0.0f, 0.0f, 0.0f);
}

bool Vector3::IsZero() const
{
	return Mathf::ApproximatelyZero(x) && Mathf::ApproximatelyZero(y) && Mathf::ApproximatelyZero(z);
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(scalar * x,scalar * y,scalar * z);
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return Mathf::Approximately(x, rhs.x) &&
			Mathf::Approximately(y, rhs.y) &&
			Mathf::Approximately(z, rhs.z);
}

bool Vector3::operator!=(const Vector3& rhs) const
{
	return !Mathf::Approximately(x, rhs.x) ||
			!Mathf::Approximately(y, rhs.y) ||
			!Mathf::Approximately(z, rhs.z);
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

float Vector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::LengthSquared() const
{
	return (x * x + y * y + z * z);
}

float Vector3::Distance(const Vector3& rhs) const
{
	return (*this - rhs).Length();
}

float Vector3::DistanceSquared(const Vector3& rhs) const
{
	return (*this - rhs).LengthSquared();
}

float Vector3::Distance(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs - rhs).Length();
}

float Vector3::DistanceSquared(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs - rhs).LengthSquared();
}

float Vector3::Dot(const Vector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::Cross(const Vector3& rhs) const
{
	return Vector3(y * rhs.z - z * rhs.y,
					z * rhs.x - x * rhs.z,
					x * rhs.y - y * rhs.x);
}

Vector3 Vector3::Normalized(void) const 
{
	float l = Length();
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(l), "Division by zero")
	return Vector3(*this) /= l;
}

Vector3& Vector3::Normalize(void)
{
	float l = Length();
	NR_CORE_ASSERT(Mathf::ApproximatelyZero(l), "Division by zero")
	return *this /= l;
}

Vector3 Vector3::Reflect(const Vector3& rhs) const
{
	return *this - 2 * this->Dot(rhs) * rhs;
}

std::ostream& operator<< (std::ostream& os, Vector3& rhs)
{
	os << "[x: " << rhs.x << " , y: " << rhs.y << " , z: " << rhs.z << " ]";
	return os;
}

Vector3 operator*( float scalar, const Vector3& rhs )
{
	return rhs * scalar;
}

std::string Vector3::ToString() const
{
	std::stringstream ss;
	ss << this;
	return ss.str();
}