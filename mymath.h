#ifndef MYMATH_H
#define MYMATH_H

namespace math
{

	float sqrt(float n); // square root of a number
	
	namespace newton // hide recurcive function from main namespace
	{
		float newtonSqrt(float value, float estimate, float margin); // recurcive Newton's (Babylonian) algorithm
	}
	
	float abs(float n); // absolute value of a number
	
	float cos_d(float angle); // cosine of agnle expressed in degrees
	float sin_d(float angle); // sine of agnle expressed in degrees
	float acos_d(float ratio); // arccosine - return value: degrees
	float asin_d(float ratio); // arcsine - return value: degrees
	float atan_d(float y, float x); // arctangen (correct quadrant) - return value: degrees

}

#endif  /* MYMATH_H */
