#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace Relu{
    double forward(double x,map<string,double>&data);
};

namespace Sigmoid{
    double forward(double x,map<string,double>&data);
};

namespace Leaner{
    double forward(double x,map<string,double>&data);
};

class Activation{
    string type;
    map<string,double>data;
public:
    Activation(string type_);
    double forward(double x);
};