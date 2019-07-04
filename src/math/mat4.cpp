#include "mat4.h"

mat4::mat4() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                vals[i][j] = 1.0f;
            }
            else {
                vals[i][j] = 0.0f;
            }
        }
    }
}

void mat4::translate(float transX, float transY, float transZ) {
    mat4 transMat;
    transMat.vals[0][3] = transX;
    transMat.vals[1][3] = transY;
    transMat.vals[2][3] = transZ;
    (*this) *= transMat;
}

void mat4::scale(float scaleX, float scaleY, float scaleZ) {
    mat4 scaleMat;
    scaleMat.vals[0][0] = scaleX;
    scaleMat.vals[1][1] = scaleY;
    scaleMat.vals[2][2] = scaleZ;
    (*this) *= scaleMat;
}

void mat4::rotX(float t) {
    float rad = t * M_PI / 180.0f;
    mat4 rotX;
	rotX.vals[1][1] = cos(rad);
	rotX.vals[1][2] = -sin(rad);
	rotX.vals[2][1] = sin(rad);
	rotX.vals[2][2] = cos(rad);
	(*this) *= rotX;
}

void mat4::rotY(float t) {
    float rad = t * M_PI / 180.0f;
    mat4 rotY;
    rotY.vals[0][0] = cos(rad);
	rotY.vals[0][2] = sin(rad);
	rotY.vals[2][0] = -sin(rad);
	rotY.vals[2][2] = cos(rad);
    (*this) *= rotY;
}

void mat4::rotZ(float t) {
    float rad = t * M_PI / 180.0;
    mat4 rotZ;
    rotZ.vals[0][0] = cos(rad);
	rotZ.vals[0][1] = -sin(rad);
	rotZ.vals[1][0] = sin(rad);
	rotZ.vals[1][1] = cos(rad);
    (*this) *= rotZ;
}

float & mat4::operator()(const int i, const int j)
{
	return vals[i][j];
}

float mat4::operator()(const int i, const int j) const
{
	return vals[i][j];
}

mat4 & mat4::operator*=(const mat4& m)
{
    float newvals[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += vals[i][k]*m.vals[k][j];
            }
            newvals[i][j] = sum;
        }
    }
    std::copy(&newvals[0][0], (&newvals[0][0] + (4*4)), &vals[0][0]);
    return *this;
}

mat4 & mat4::operator*=(const float c)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			vals[i][j] *= c;
		}
	}
	return *this;
}

mat4 operator*(const mat4& m1, mat4& m2)
{
	mat4 newmat;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			float sum = 0.0f;
			for(int k = 0; k < 4; ++k)
			{
				sum += m1.vals[i][k] * m2.vals[k][j];
			}
			newmat.vals[i][j] = sum;
		}
	}
	return newmat;
}

mat4 operator*(const mat4&m, const float c)
{
	mat4 newmat;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			newmat.vals[i][j] = newmat.vals[i][j] * c;
		}
	}
	return newmat;
}