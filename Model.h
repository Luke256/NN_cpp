#pragma once
#include <bits/stdc++.h>
#include "Layer.h"

using namespace std;
using v3d=vector<vector<vector<double>>>;

class Model{
private:
    string optimizer;
    map<string,double> optimizer_options;
    vector<Layer>layers;
    int num_layers;
    
public:
    Model(int input_size,int output_size,int hidden_layers,const vector<pair<int,string>>&configs);
    vector<vector<double>> predict(const vector<vector<double>>&input);
    void set_optimizer(string name,const map<string,double>&options);
    vector<double>fit(const vector<vector<double>>&x,const vector<vector<double>>&y, int epochs, int verbose,string loss_method,int batch_size=-1);
    vector<map<string,vector<vector<double>>>>numical_gradient(string loss,const vector<vector<double>>&x,const vector<vector<double>>&y);
    void print_weights();
};