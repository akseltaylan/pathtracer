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

        double vals[4][4];

        mat4();

        void translate(double transX, double transY, double transZ);
        void scale(double scaleX, double scaleY, double scaleZ);
        void rotX (double t);
        void rotY (double t);
        void rotZ (double t);

        double & operator()(const int i, const int j);
        double operator()(const int i, const int j) const;

        mat4 & operator*=(const mat4& m);
        mat4 & operator*=(const double c);

        friend mat4 operator*(const mat4& m1, mat4& m2);
        friend mat4 operator*(const mat4&m, const double c);

};

#endif