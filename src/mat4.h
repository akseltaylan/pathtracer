#ifndef MAT4_H
#define MAT4_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <algorithm>

/*
    Matrix class
*/

class mat4 {

    public:

        float vals[4][4];

        mat4();

        void translate(float transX, float transY, float transZ);
        void scale(float scaleX, float scaleY, float scaleZ);
        void rotX (float t);
        void rotY (float t);
        void rotZ (float t);

        float & operator()(const int i, const int j);
        float operator()(const int i, const int j) const;

        mat4 & operator*=(const mat4& m);
        mat4 & operator*=(const float c);

        friend mat4 operator*(const mat4& m1, mat4& m2);
        friend mat4 operator*(const mat4&m, const float c);

};

#endif