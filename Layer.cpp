#include "Layer.h"
#include "Activations.h"
#include <random>



Layer::Layer(int input_,int output_, string activation_="leaner"):
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

vector<double>Layer::forward(vector<double> input){
     if(input.size()!=param[0].size()){
         cerr<<"Invalid shape. input's size is "<<input.size()<<", but param's size is "<<param.size()<<".";
         return input;
     }

    vector<double> output(bias.size(),0);
    rep(i,param[0].size()){ //outputs
        output[i]=bias[i];
        rep(j,param.size()){ //inputs
            output[i]+=input[j]*param[j][i];
        }
        output[i]=activation.forward(output[i]);
    }

    return output;
}