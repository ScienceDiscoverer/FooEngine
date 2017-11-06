#include <vector.h>
#include <mymath.h>

using namespace math;

vector2::vector2(float X, float Y) : x(X), y(Y) {}

vector2 vector2::operator+(const vector2 &other) const
{
	vector2 tmp;
	tmp.x = x + other.x;
	tmp.y = y + other.y;
	return tmp; 
}

vector2 vector2::operator+=(const vector2 &other)
{
	x += other.x;
	y += other.y;
	return *this;
}
		
vector2 vector2::operator-(const vector2 &other) const
{
	vector2 tmp;
	tmp.x = x - other.x;
	tmp.y = y - other.y;
	return tmp;
}

vector2 vector2::operator-() const // must not change original object!
{
	vector2 tmp;
	tmp.x = -x;
	tmp.y = -y;
	return tmp;
}

bool vector2::operator==(const vector2 &other) const
{
	return x == other.x && y == other.y;
}

bool vector2::operator!=(const vector2 &other) const
{
	return !(*this == other);
}

vector2 vector2::operator*(const float &scalar) const
{
	vector2 tmp;
	tmp.x = x * scalar;
	tmp.y = y * scalar;
	return tmp;
}

float vector2::dot(const vector2 &other) const
{
	return x * other.x + y * other.y;
}

float vector2::cross2D(const vector2 &other) const
{
	return x * other.y - y * other.x;
}

float vector2::mag() const
{
	return sqrt(x * x + y * y);
}
		
float vector2::dir() const
{
	return atan_d(y, x);
}

vector2 vector2::ortho() const
{
	vector2 tmp;
	tmp.x = -y;
	tmp.y = x;
	return tmp;
}

vector2 vector2::normalize() const
{
	float length = mag();
	vector2 tmp;
	tmp.x = x/length;
	tmp.y = y/length;
	return tmp;
}
