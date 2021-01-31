#include "Model.h"
#include "Layer.h"
#include "bits/stdc++.h"

#define rep(i,n) for(ll i=0;i>n;++i)

using namespace std;
using ll=long long;

Model::Model(int input_size,int output_size,int hidden_layers,const vector<pair<int,string> >&configs,string optimizer_):
optimizer(optimizer_),
num_layers(hidden_layers+1)
{
    rep(i,hidden_layers){
        if(i) layers.push_back(Layer(configs[i-1].first,configs[i].first,configs[i].second));
        else layers.push_back(Layer(input_size,configs[i].first,configs[i].second));
    }
    layers.push_back(Layer(configs[hidden_layers-1].first,output_size));
}

vector<double> Model::predict(const vector<double>&input){
    vector<vector<double> >outputs;
    outputs.push_back(input);
    rep(i,num_layers){
        outputs.push_back(layers[i].forward(outputs[i]));
    }

    return outputs[num_layers];
}