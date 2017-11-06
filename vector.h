#ifndef VECTOR_H
#define VECTOR_H

struct vector2 // 2D Vector
{
	float x;
	float y;
	
	vector2(float X = 0, float Y = 0); // initialization + default constructors
	/* copy and assignment constructors will be provided by the compiler */
		
	vector2 operator+(const vector2 &other) const; // add 2 vectors
	vector2 operator+=(const vector2 &other); // assign-addition
	vector2 operator-(const vector2 &other) const; // subtruct 2 vectors (points)
	vector2 operator-() const; // vector negation (get opposite vector)
	bool operator==(const vector2 &other) const; // check if 2 vectors are equal
	bool operator!=(const vector2 &other) const; // check if 2 vectors are not equal
	
	vector2 operator*(const float &scalar) const; // multiply vector by scalar
	float dot(const vector2 &other) const; // dot product of vectors
	float cross2D(const vector2 &other) const; // 2D cross product for line intersection calculation
	float mag() const; // magnitude (length) of the vector
	float dir() const; // direction of the vector (degrees)
	vector2 ortho() const; // get vector orthogonal (perpendicular) to this vector (counterclock 90 deg)
	vector2 normalize() const; // normalize vector
	// note for future: possibly add function to compute x,y from angle and magnitude
	
};

#endif  /* VECTOR_H */
