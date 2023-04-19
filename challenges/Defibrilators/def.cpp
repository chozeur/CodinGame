#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

#define RAD 0.01745329

float   distance(double longA, double longB, double latA, double latB){
    double x = (longB - longA) * cos((latA + latB) / 2);
    double y = latB - latA;
    return (sqrt(x*x + y*y) * 6371);
}

vector<string>  strSplit(string s, char del)
{
    vector<string>  split;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        split.push_back(word);
    }
    return (split);
}

string  comtodot(string num){
    string  res = "";
    for (string::const_iterator it = num.begin(); it != num.end(); ++it){
        if (*it == ',')
            res += '.';
        else
            res += *it;
    }
    return (res);
}

class   Defib {
    public:
        Defib(string str){
            vector<string>  spl = strSplit(str, ';');
            this->_id = stoi(spl[0]);
            this->_name = spl[1];
            this->_address = spl[2];
            this->_phone = spl[3];
            this->_long = RAD * stod(comtodot(spl[4]));
            this->_lat = RAD * stod(comtodot(spl[5]));
        }
        ~Defib(void){return ;}
        void    set_dist(double longA, double latA){
            this->_dist = distance(longA, this->_long, latA, this->_lat);
            return ;
        }
        double  get_dist(void){return (this->_dist);}
        string  get_name(void){return (this->_name);}
    private:
        int     _id;
        string  _name;
        string  _address;
        string  _phone;
        double  _long;
        double  _lat;
        double  _dist;
        
        Defib(void){}
};

int main()
{
    string lon;
    cin >> lon; cin.ignore();
    string lat;
    cin >> lat; cin.ignore();
    int n;
    cin >> n; cin.ignore();
    vector<Defib>   allDef;
    for (int i = 0; i < n; i++) {
        string defib;
        getline(cin, defib);
        Defib odef(defib);
        odef.set_dist(RAD * stod(comtodot(lon)), RAD * stod(comtodot(lat)));
        allDef.push_back(odef);
    }
    std::sort(allDef.begin(), allDef.end(), [](Defib& lhs, Defib& rhs){
        return lhs.get_dist() < rhs.get_dist();
    });
    cout << allDef.front().get_name() << endl;
}
