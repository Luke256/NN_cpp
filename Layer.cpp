#include "Layer.h"
#include "Activations.h"
#include <bits/stdc++.h>

#define rep(i,n) for(ll i=0;i<n;++i)

using namespace std;
using ll=long long;

Layer::Layer(int input_,int output_, string activation_):
input(input_), //input * output
output(output_),
param(vector<vector<double> >(input,vector<double>(output,0))),
bias(vector<double>(output,0)),
activation(Activation(activation_))
{
    srand(time(nullptr));
    rep(i,input){
        rep(j,output){
            param[i][j]=(double)rand()/RAND_MAX;
        }
    }
}

vector<vector<double>>Layer::forward(const vector<vector<double>>&input){
    if(input[0].size()!=param.size()){
        cerr<<"Invalid shape. input's size is "<<input[0].size()<<", but param's size is "<<param.size()<<"."<<endl;
        return input;
    }

    vector<vector<double>> output(input.size(),vector<double>(bias.size(),0));
    rep(batch,input.size()){
        rep(i,param[0].size()){ //outputs
            output[batch][i]=bias[i];
            rep(j,param.size()){ //inputs
                output[batch][i]+=input[batch][j]*param[j][i];
            }
            output[batch][i]=activation.forward(output[batch][i]);
        }
    }
    return output;
}