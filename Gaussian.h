//
// Created by jajal on 1/18/2022.
//

#ifndef TRUESKILL_PORTCPP_GAUSSIAN_H
#define TRUESKILL_PORTCPP_GAUSSIAN_H


class Gaussian {

public:
    static double pdf(double x);
    double pdf(double x, double mu, double sigma);
    static double cdf(double z);
    double cdf(double z, double mu, double sigma);
    double inverseCDF(double y);
    double inverseCDF(double y, double delta, double lo, double hi);
    double phi(double x);
    double phi(double x, double mu, double sigma);
    double Phi(double z);
    double Phi(double z, double mu, double sigma);
    double PhiInverse(double y);
};


#endif //TRUESKILL_PORTCPP_GAUSSIAN_H
