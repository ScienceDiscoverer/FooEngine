#include <mymath.h>
#include <cmath>

#define PI 3.141592

namespace math {

float abs(float n)
{
	return n < 0 ? -n : n;
}

float newtonSqrt(float value, float estimate, float margin)
{
	float error = estimate * estimate - value;

	if(abs(error) < margin)
		return estimate;
	else
	{
		float new_estimate = (estimate + value/estimate)/2;
		return newtonSqrt(value, new_estimate, margin);
	}
}

float sqrt(float n)
{
	if(n < 0)
		return -1; // no root for negative number
	else
	{
		float mrg = 0.000001;
	
		for(int i = 10; i < n; i *= 10) // adjust accuracy depending on how big is the number
			mrg *= 10;
		
		return newtonSqrt(n, 1, mrg);
	}
}

float cos_d(float angle)
{
	float radian = angle * PI/180;
	return cos(radian);
}

float sin_d(float angle)
{
	float radian = angle * PI/180;
	return sin(radian);
}

float acos_d(float ratio)
{
	float radian = acos(ratio);
	return radian * 180/PI;
}

float asin_d(float ratio)
{
	float radian = asin(ratio);
	return radian * 180/PI;
}

float atan_d(float y, float x)
{
	float radian = atan2(y, x);
	return radian * 180/PI;
}

}
