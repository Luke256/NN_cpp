#pragma once
#include "bits/stdc++.h"
#include "Layer.h"

using namespace std;

class Model{
private:
    string optimizer;
    vector<Layer>layers;
    int num_layers;
    
public:
    Model(int input_size,int output_size,int hidden_layers,vector<pair<int,string> >configs,string optimizer_);
    vector<double> predict(vector<double>input);
};