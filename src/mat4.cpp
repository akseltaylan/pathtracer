#include "mat4.h"

mat4::mat4() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                vals[i][j] = 1.0;
            }
            else {
                vals[i][j] = 0.0;
            }
        }
    }
}

void mat4::translate(double transX, double transY, double transZ) {

}

void mat4::scale(double scaleX, double scaleY, double scaleZ) {

}

void mat4::rotX(double t) {

}

void mat4::rotY(double t) {
    
}

void mat4::rotZ(double t) {
    
}