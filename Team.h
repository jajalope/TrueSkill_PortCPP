//
// Created by jajal on 1/18/2022.
//

#ifndef TRUESKILL_PORTCPP_TEAM_H
#define TRUESKILL_PORTCPP_TEAM_H
using namespace std;

#include <string>

class Team {

public:
    Team(string n, string i);
    Team(string basicString);

    double mu, sigma, trueMu = mu - (sigma * 3);
    string name, id;
    void setMu(double muVal);
    double getMu();
    void setSigma(double sigma);
    double getSigma();
};


#endif //TRUESKILL_PORTCPP_TEAM_H
