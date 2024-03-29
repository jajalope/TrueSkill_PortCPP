//
// Created by jajal on 1/18/2022.
//

#include <cmath>
#include "Gaussian.h"

// return pdf(x) = standard Gaussian pdf
double Gaussian::pdf(double x) {
    return exp(-x*x / 2) / sqrt(2 * M_PI);
}

// return pdf(x, mu, sigma) = Gaussian pdf with mean mu and stddev sigma
double Gaussian::pdf(double x, double mu, double sigma) {
    return pdf((x - mu) / sigma) / sigma;
}

// return cdf(z) = standard Gaussian cdf using Taylor approximation
double Gaussian::cdf(double z) {
    if (z < -8.0) return 0.0;
    if (z >  8.0) return 1.0;
    double sum = 0.0, term = z;
    for (int i = 3; sum + term != sum; i += 2) {
        sum  = sum + term;
        term = term * z * z / i;
    }
    return 0.5 + sum * pdf(z);
}

// return cdf(z, mu, sigma) = Gaussian cdf with mean mu and stddev sigma
double Gaussian::cdf(double z, double mu, double sigma) {
    return cdf((z - mu) / sigma);
}

// Compute z such that cdf(z) = y via bisection search
double Gaussian::inverseCDF(double y) {
    return inverseCDF(y, 0.00000001, -8, 8);
}

// bisection search
double Gaussian::inverseCDF(double y, double delta, double lo, double hi) {
    double mid = lo + (hi - lo) / 2;
    if (hi - lo < delta) return mid;
    if (cdf(mid) > y) return inverseCDF(y, delta, lo, mid);
    else              return inverseCDF(y, delta, mid, hi);
}

// return phi(x) = standard Gaussian pdf
double Gaussian::phi(double x) {
    return pdf(x);
}

// return phi(x, mu, sigma) = Gaussian pdf with mean mu and stddev sigma
double Gaussian::phi(double x, double mu, double sigma) {
    return pdf(x, mu, sigma);
}

// return Phi(z) = standard Gaussian cdf using Taylor approximation
double Gaussian::Phi(double z) {
    return cdf(z);
}

// return Phi(z, mu, sigma) = Gaussian cdf with mean mu and stddev sigma
double Gaussian::Phi(double z, double mu, double sigma) {
    return cdf(z, mu, sigma);
}

double Gaussian::PhiInverse(double y) {
    return inverseCDF(y);
}
