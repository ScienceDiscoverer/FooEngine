#ifndef MATRIX_H
#define MATRIX_H

class matrix2_2 // 2x2 matrix
{
	float data[2][2];
	
	public:
		
		matrix2_2(); // default constructor will initialise all elements to 0
		
		//somehow func to set elements elegantly?
		matrix2_2 operator+(matrix2_2 other); // matrix addition
		matrix2_2 operator-(matrix2_2 other); // matrix subtruction
		matrix2_2 operator-() const; // matrix negation (get opposite matrix)
		
		matrix2_2 operator*(matrix2_2 other); // matrix multiplication
		matrix2_2 operator*(vector2 vec); // multiply matrix by vector
		matrix2_2 operator*(float scalar); // multiply matrix by scalar (scale matrix)
			
};

class matrix3_3 // 3x3 matrix
{
	float data[3][3];
	
	public:
		
		matrix3_3(); // default constructor will initialise all elements to 0
		
		//somehow func to set elements elegantly?
		matrix3_3 operator+(matrix3_3 other); // matrix addition
		matrix3_3 operator-(matrix3_3 other); // matrix subtruction
		matrix3_3 operator-() const; // matrix negation (get opposite matrix)
		
		matrix3_3 operator*(matrix3_3 other); // matrix multiplication
		matrix3_3 operator*(vector2 vec); // multiply matrix by vector
		matrix3_3 operator*(float scalar); // multiply matrix by scalar (scale matrix)
			
};

#endif  /* MATRIX_H */
