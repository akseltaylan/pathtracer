#include "wavelength.h"

wavelength::wavelength() {

}

wavelength::wavelength(int s, vec4 col, double nWLx) {
    samples = s;
    totColor = col;
    if (s < 1) {
        low = nWLx;
        high = nWLx;
    }
    else {
        low = 0.0;
        high = 1.0;
    }
    nWL = nWLx;
}

int wavelength::getNumSamples() {
    return samples;
}

vec4 wavelength::getTotColor() {
    return totColor;
}

double wavelength::getLow() {
    return low;
}

double wavelength::getHigh() {
    return high;
}

double wavelength::getWL() {
    return nWL;
}

vec4 wavelength::getColSample(int num, double r, double& nwl) {
    if (num < samples) {
        if (samples < 1) {
            nwl = nWL;
            return totColor;
        }
        else {
            double sam = (double)samples;
            double range = (high - low) / sam;
            nwl = range * (samples + r);
            return getColMultiplier(nwl); 
        }
    }
    return vec4(0,0,0);
}

vec4 wavelength::getColMultiplier(double m) {
    double r; double g; double b;
    if (m < 0.5) {
        r = -6.0 * m + 1.0;
        g = 6.0 * m -  1.0;
        b = -6.0 * m + 3.0;
    }
    else {
        r = 6.0 * m - 3.0;
        g = 6.0 * m + 5.0;
        b = 6.0 * m - 5.0;
    }
    vec4 col (r, g, b);
    col.clamp(0.0, 1.0);
    return col;
}