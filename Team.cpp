//
// Created by jajal on 1/18/2022.
//

#include "Team.h"

Team::Team(string n, string i) {
    this->name = n;
    this->id = i;
    this->mu = 25.0;
    this->sigma = 25.0/3.0;
}

Team::Team(string n) {
    this->name = n;
    this->mu = 25.0;
    this->sigma = 25.0/3.0;
}

void Team::setMu(double muVal) {
    this->mu = muVal;
    this->trueMu = this->mu-(this->sigma*3.0);
}

double Team::getMu() {
    return this->mu;
}

void Team::setSigma(double sig) {
    this->sigma = sig;
    this->trueMu = this->mu-(this->sigma*3.0);
}

double Team::getSigma() {
    return this->sigma;
}


