#include "nrpch.h"
#include "Vector2.h"


#include "Mathf.h"
#include "Nare/Core/Core.h"

Vector2::Vector2(double x, double y)
	: x(static_cast<float>(x))
	, y(static_cast<float>(y))
{
}


Vector2::Vector2(unsigned x, unsigned y)
	: x(static_cast<float>(x))
	, y(static_cast<float>(y))
{
}

// TODO: Might make this a less expensive function.
/**
 * \brief Convert the Vector2 into a string.
 * \return String representation of the vector
 */
std::string Vector2::ToString() const
{
	std::stringstream ss;
	ss << "[x: " << x << " , y: " << y << " ]";
	return ss.str();
}

const float* Vector2::data() const
{
	return &x;
}

float Vector2::operator[](const unsigned& index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		// TODO: This should be a log error.
		throw std::invalid_argument("Vector2 cannot be accessed with this index.");
	}
}

bool Vector2::IsZero() const
{
	return Mathf::ApproximatelyZero(x) && Mathf::ApproximatelyZero(y);
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return Mathf::Approximately(x, rhs.x) && Mathf::Approximately(y, rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	return !Mathf::Approximately(x, rhs.x) || !Mathf::Approximately(y, rhs.y);
}

Vector2 Vector2::operator-() const
{
	return { -x, -y };
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return {x + rhs.x, y + rhs.y};
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return { x - rhs.x, y - rhs.y };
}

Vector2 Vector2::operator*(const float scalar) const
{
	return { scalar * x, scalar * y };
}

Vector2& Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
	NR_CORE_ASSERT(!Mathf::ApproximatelyZero(scalar), "Dividing by zero.")
	return { x / scalar, y / scalar };
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2& Vector2::Normalize()
{
	const float l = Length();
	NR_CORE_ASSERT(!Mathf::ApproximatelyZero(l), "Division by zero")
	return *this /= l;
}

Vector2 Vector2::Normalized() const
{
	const float l = Length();
	NR_CORE_ASSERT(!Mathf::ApproximatelyZero(l), "Division by zero")
	return Vector2(*this) / l;
}

float Vector2::Dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::DistanceSquared(const Vector2& rhs) const
{
	return (*this - rhs).LengthSquared();
}

float Vector2::Distance(const Vector2& rhs) const
{
	return (*this - rhs).Length();
}

Vector2 Vector2::PerpendicularClockwise() const
{
	return Vector2(y, -x).Normalize();
}

Vector2 Vector2::PerpendicularAntiClockwise() const
{
	return Vector2(-y, x).Normalize();
}

Vector2 Vector2::Normalize(const Vector2& vec)
{
	return vec.Normalized();
}

float Vector2::Dot(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.Dot(vec2);
}

Vector2 Vector2::Reflect(const Vector2& incident, const Vector2& normal)
{
	return incident - 2 * incident.Dot(normal) * normal;
}

float Vector2::Length(const Vector2& vec)
{
	return vec.Length();
}

float Vector2::LengthSquared(const Vector2& vec)
{
	return vec.LengthSquared();
}


float Vector2::Distance(const Vector2& lhs, const Vector2& rhs)
{
	return (lhs - rhs).Length();
}

float Vector2::DistanceSquared(const Vector2& lhs, const Vector2& rhs)
{
	return (lhs - rhs).Length();
}

Vector2 operator*(float scalar, const Vector2& rhs)
{
	return rhs * scalar;
}

std::ostream& operator<<(std::ostream& os, const Vector2& rhs)
{
	os << "[x: " << rhs.x << " , y: " << rhs.y << " ]";
	return os;
}
