#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include "Team.h"
#include "Gaussian.h"

using namespace std;
//Team *teams[1000];
string temp[10];
vector<string> tem;
vector<Team> teams;

void teamBuilderStandard(string filePath);
void teamBuilderSportsReference(string filePath);
void gamePicker(string team1Name, string team2Name);
Team teamFinder(string teamName);
Team teamFinderID(string id);
void TgamePicker(string team1Name, string team2Name);
double gnd(double x, double mu, double sigma);
double snd(double x);
double v(double t);
double w(double t);
bool iequals(const string& a, const string& b);
int activeTeams();
void splitter(string line);
vector<string> split (string s, string delimiter);

int main() {
    //teamBuilderStandard("resources/NFL/NFL2021.csv");
    teamBuilderSportsReference("C:\\Users\\jajal\\CLionProjects\\TrueSkill-PortCPP\\resources\\College Football (FBS)\\20.csv");
    //teamBuilderMM2017(tRec.nextLine());
    while (true) {
        string in, t1, t2;
        cin >> t1;
        cin >> t2;
        cout << teamFinder(t1).mu << teamFinder(t2).mu;
        gamePicker(t1, t2);
        TgamePicker(t1, t2);
    }
    return 0;
}

void teamBuilderStandard(string filePath) {
    double beta = 10.1;
    //play around with beta value
    ifstream file;
    file.open(filePath);
    string line;
    while(getline(file, line)) {
        string temp[10] {"0","0","0","0","0","0","0","0","0","0"};
        stringstream ssin(line);
        int i = 0;
        while (ssin.good() && i<10) {
            ssin >> temp[i];
            ++i;
        }

        if (iequals(temp[0],"Team1") || iequals(temp[0],"") || temp[0].find("week") || temp[0].find("//")) continue;
        if (iequals(temp[2],(""))) { continue;}

        int count = activeTeams();
        int placeholder = count;
        for (Team t: teams) {
            if (iequals(t.name,temp[0])) break;
            count--;
        }
        if (count == 0) {
            //Team* x = new Team(temp[0]);
            //teams[placeholder] = (x);
        }
        count = activeTeams();
        placeholder = count;
        for (Team t: teams) {
            if (iequals(t.name,temp[1])) break;
            count--;
        }
        if (count == 0) {
                //Team* x = new Team(temp[1]);
                //teams[placeholder] = x;

        }


        if (!iequals(temp[2],"0")) {
            if (iequals(temp[2],"1")) {
                Team winner = teamFinder(temp[0]);
                Team loser = teamFinder(temp[1]);

                double oldWinnerMu = winner.mu;
                double oldLoserMu = loser.mu;
                double oldWinnerSigma = winner.sigma;
                double oldLoserSigma = loser.sigma;

                double c = sqrt(2*pow(beta, 2) + pow(oldWinnerSigma, 2) + pow(oldLoserSigma, 2));
                double t = (oldWinnerMu-oldLoserMu)/c;

                winner.setMu(oldWinnerMu + ((pow(oldWinnerSigma, 2))/c) * v(t));
                loser.setMu(oldLoserMu - ((pow(oldLoserSigma, 2))/c) * v(t));
                winner.setSigma(sqrt((pow(oldWinnerSigma, 2)) * (1 - ((pow(oldWinnerSigma, 2)) / pow(c, 2)) * w(t))));
                loser.setSigma(sqrt((pow(oldLoserSigma, 2)) * (1 - ((pow(oldLoserSigma, 2)) / pow(c, 2)) * w(t))));
            }
            else {
                Team winner = teamFinder(temp[1]);
                Team loser = teamFinder(temp[0]);

                double oldWinnerMu = winner.mu;
                double oldLoserMu = loser.mu;
                double oldWinnerSigma = winner.sigma;
                double oldLoserSigma = loser.sigma;

                double c = sqrt(2*pow(beta, 2) + pow(oldWinnerSigma, 2) + pow(oldLoserSigma, 2));
                double t = (oldWinnerMu-oldLoserMu)/c;

                winner.setMu(oldWinnerMu + ((pow(oldWinnerSigma, 2))/c) * v(t));
                loser.setMu(oldLoserMu - ((pow(oldLoserSigma, 2))/c) * v(t));
                winner.setSigma(sqrt((pow(oldWinnerSigma, 2)) * (1 - ((pow(oldWinnerSigma, 2)) / pow(c, 2)) * w(t))));
                loser.setSigma(sqrt((pow(oldLoserSigma, 2)) * (1 - ((pow(oldLoserSigma, 2)) / pow(c, 2)) * w(t))));
            }
        }
    }
}

void teamBuilderSportsReference(string filePath) {
    double beta = 10.1;
    //play around with beta value
    ifstream file;
    file.open(filePath);
    string line;
    while(getline(file, line)) {
        //splitter(line);
        tem = split(line, ",");

        if (iequals(tem[0],"Date") || tem[0].find("//") != string::npos) {
            continue;
        }
        int tester = 0;
        for (Team t: teams) {
            if (iequals(t.name,tem[1])) {
                tester = 1;
                break;
            }
        }
        if (tester == 0) {
            Team x(tem[1]);
            teams.push_back(x);
        }
        tester = 0;
        for (Team t: teams) {
            if (iequals(t.name,tem[3])) {
                tester = 1;
                break;
            }
        }
        if (tester == 0) {
            Team x(tem[3]);
            teams.push_back(x);
        }

        if (stoi(tem[2]) > stoi(tem[4])) {
            Team winner = teamFinder(tem[1]);
            Team loser = teamFinder(tem[3]);

            double oldWinnerMu = winner.mu;
            double oldLoserMu = loser.mu;
            double oldWinnerSigma = winner.sigma;
            double oldLoserSigma = loser.sigma;

            double c = sqrt((2.0 * pow(beta, 2.0) + pow(oldWinnerSigma, 2.0) + pow(oldLoserSigma, 2.0)));
            double t = (oldWinnerMu - oldLoserMu) / c;

            winner.setMu(oldWinnerMu + ((pow(oldWinnerSigma, 2)) / c) * v(t));
            loser.setMu(oldLoserMu - ((pow(oldLoserSigma, 2)) / c) * v(t));
            winner.setSigma(sqrt((pow(oldWinnerSigma, 2.0)) * (1.0 - ((pow(oldWinnerSigma, 2.0)) / pow(c, 2.0)) * w(t))));
            loser.setSigma(sqrt((pow(oldLoserSigma, 2.0)) * (1.0 - ((pow(oldLoserSigma, 2.0)) / pow(c, 2)) * w(t))));
        } else {
            Team winner = teamFinder(tem[3]);
            Team loser = teamFinder(tem[1]);

            double oldWinnerMu = winner.mu;
            double oldLoserMu = loser.mu;
            double oldWinnerSigma = winner.sigma;
            double oldLoserSigma = loser.sigma;

            double c = sqrt((2.0 * pow(beta, 2.0) + pow(oldWinnerSigma, 2.0) + pow(oldLoserSigma, 2.0)));
            double t = (oldWinnerMu - oldLoserMu) / c;

            winner.setMu(oldWinnerMu + ((pow(oldWinnerSigma, 2.0)) / c) * v(t));
            loser.setMu(oldLoserMu - ((pow(oldLoserSigma, 2.0)) / c) * v(t));
            winner.setSigma(sqrt(
                    (pow(oldWinnerSigma, 2.0)) * (1.0 - ((pow(oldWinnerSigma, 2.0)) / pow(c, 2.0)) * w(t))));
            loser.setSigma(sqrt(
                    (pow(oldLoserSigma, 2.0)) * (1.0 - ((pow(oldLoserSigma, 2.0)) / pow(c, 2.0)) * w(t))));
        }
    }
    file.close();
}

void gamePicker(string team1Name, string team2Name) {
    if ((teamFinder(team1Name).mu/(teamFinder(team1Name).mu + teamFinder(team2Name).mu) * 100) >=50.0 ) {
        cout << team1Name << " has a " << (teamFinder(team1Name).mu/(teamFinder(team1Name).mu + teamFinder(team2Name).mu) * 100) << " percent chance of winning" << endl;
    }
    else if ((teamFinder(team2Name).mu/(teamFinder(team1Name).mu + teamFinder(team2Name).mu) * 100) >=50.0 ) {
        cout << team2Name << " has a " << (teamFinder(team2Name).mu/(teamFinder(team1Name).mu + teamFinder(team2Name).mu) * 100) << " percent chance of winning" << endl;
    }
    else {
        cout << "The game will likely be a tie" << endl;
    }
}

Team teamFinder(string teamName) {
    for (Team t:teams) {
        //if (t!=NULL) {}
            if (iequals(t.name,teamName)) {
                return (t);
            }
    }
    return static_cast<Team>(NULL);
}

Team teamFinderID(string id) {
    for (Team t:teams) {
        if (iequals(t.id,id)) {
            return (t);
        }
    }
    return static_cast<Team>(NULL);
}

void TgamePicker(string team1Name, string team2Name) {
    if ((teamFinder(team1Name).trueMu/(teamFinder(team1Name).trueMu + teamFinder(team2Name).trueMu) * 100) >=50.0 ) {
        cout << team1Name << " has a " << (teamFinder(team1Name).trueMu/(teamFinder(team1Name).trueMu + teamFinder(team2Name).trueMu) * 100) << " percent chance of winning" << endl;
    }
    else if ((teamFinder(team2Name).trueMu/(teamFinder(team1Name).trueMu + teamFinder(team2Name).trueMu) * 100) >=50.0 ) {
        cout << team2Name << " has a " << (teamFinder(team2Name).trueMu/(teamFinder(team1Name).trueMu + teamFinder(team2Name).trueMu) * 100) << " percent chance of winning" << endl;
    }
    else {
        cout << "The game will likely be a tie" << endl;
    }
}

//general normal distribution
double gnd(double x, double mu, double sigma) {
    return ((1.0/sigma) * (snd((x-mu)/sigma)));
}

//standard normal distribution
double snd(double x) {
    return ((1.0/(sqrt(2.0 * M_PI))) * (exp(-0.5 * pow(x, 2.0))));
}

//Mean Additive Truncated Gaussian Function: “v” (non-draw)
double v(double t) {
    return (snd(t))/ Gaussian::cdf(t);
}

//Variance Multiplicative Function: “w” (non-drawn)
double w(double t) {
    return v(t) * (v(t) + t);
}

bool iequals(const string& a, const string& b)
{
    return equal(a.begin(), a.end(),b.begin(), b.end(),[](char a, char b) {
                          return tolower(a) == tolower(b);
    });
}

/*bool iequals(string a, string b) {
    return strcasecmp(a.c_str(), b.c_str());
}*/

int activeTeams() {
    int count = 0;
    for (Team x: teams) {
        count++;
    }
    return count;
}

void splitter(string line) {

}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    tem.clear();

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}