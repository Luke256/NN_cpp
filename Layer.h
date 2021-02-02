#pragma once
#include <bits/stdc++.h>
#include "Activations.h"

#define rep(i,n) for(ll i=0;i<n;++i)

using namespace std;
using ll=long long;

class Layer{
public:
    int input,output;
    vector<vector<double> >param;
    vector<double> bias;
    Activation activation;
    
    Layer(int input_,int output_, string activation_="leaner");
    vector<vector<double>>forward(const vector<vector<double>>&input);
};