#include "Model.h"
#include "Layer.h"
#include "Loss.h"
#include <bits/stdc++.h>

#define rep(i,n) for(ll i=0;i<n;++i)

using namespace std;
using ll=long long;

Model::Model(int input_size,int output_size,int hidden_layers,const vector<pair<int,string>>&configs):
num_layers(hidden_layers+1)
{
    if(hidden_layers!=configs.size()){
        cout<<"Unexpected size: hidden_layers is "<<hidden_layers<<", but the size of configs is "<<configs.size()<<". These two need to match."<<endl;
        return;
    }
    rep(i,hidden_layers){
        if(i) layers.push_back(Layer(configs[i-1].first,configs[i].first,configs[i].second));
        else layers.push_back(Layer(input_size,configs[i].first,configs[i].second));
    }
    layers.push_back(Layer(configs[hidden_layers-1].first,output_size));
}

vector<vector<double>> Model::predict(const vector<vector<double>>&input){
    vector<vector<vector<double>>>outputs;
    outputs.push_back(input);
    rep(i,num_layers){
        outputs.push_back(layers[i].forward(outputs[i]));
    }

    return outputs[num_layers];
}

void Model::set_optimizer(string name,const map<string,double>&options){
    optimizer=name;
    optimizer_options=options;
}

vector<double>Model::fit(const vector<vector<double>>&x,const vector<vector<double>>&y, int epochs, int verbose,string loss_method, int batch_size){
    vector<double>history;
    
    vector<pair<vector<double>,vector<double>>> sample;
    rep(i,x.size()){
        sample.push_back(make_pair(x[i],y[i]));
    }
    mt19937 mt;
    shuffle(sample.begin(),sample.end(),mt);

    rep(epoch,epochs){
        // バッチ作成
        vector<vector<double>>batch_x;
        vector<vector<double>>batch_y;
        rep(j,batch_size){
            batch_x.push_back(sample[(epoch*batch_size+j)%sample.size()].first);
            batch_y.push_back(sample[(epoch*batch_size+j)%sample.size()].second);
        }

        // 誤差確認
        auto t=predict(batch_x);
        vector<double> error;
        if(loss_method=="cross_entropy_error") error=Loss::cross_entropy_error(y,t);
        else if(loss_method=="mean_squared_error") error=Loss::mean_squared_error(y,t);
        auto loss=0;
        for(auto i:error) loss+=i;
        loss/=batch_size;
        history.push_back(loss);

        // 勾配計算
        auto grad=numical_gradient(loss_method,batch_x,batch_y);
        // 最適化
        rep(l,num_layers){
            rep(j,layers[l].output){
                rep(i,layers[l].input){
                    if(optimizer=="sgd"){
                        layers[l].param[i][j]-=optimizer_options["learning_rate"]*grad[l]["param"][i][j];
                    }
                }
                if(optimizer=="sgd"){
                    layers[l].bias[j]-=optimizer_options["learning_rate"]*grad[l]["bias"][0][j];
                }
            }
        }
    }
    return history;
}

vector<map<string,vector<vector<double>>>>Model::numical_gradient(string loss,const vector<vector<double>>&x,const vector<vector<double>>&y){
    vector<map<string,vector<vector<double>>>>grad(num_layers);
    rep(l,num_layers){
        grad[l]["param"]=vector<vector<double>>(layers[l].input,vector<double>(layers[l].output,0));
        grad[l]["bias"]=vector<vector<double>>(1,vector<double>(layers[l].output,0));
        rep(j,layers[l].output){
            // param
            rep(i,layers[l].input){
                double tmp=layers[l].param[i][j];

                // x-h
                layers[l].param[i][j]=tmp-(1e-4);
                auto t_minus=predict(x);
                vector<double> error_minus;
                if(loss=="cross_entropy_error") error_minus=Loss::cross_entropy_error(y,t_minus);
                else if(loss=="mean_squared_error") error_minus=Loss::mean_squared_error(y,t_minus);

                // x+h
                layers[l].param[i][j]=tmp+(1e-4);
                auto t_plus=predict(x);
                vector<double> error_plus;
                if(loss=="cross_entropy_error") error_plus=Loss::cross_entropy_error(y,t_plus);
                else if(loss=="mean_squared_error") error_plus=Loss::mean_squared_error(y,t_plus);

                layers[l].param[i][j]=tmp;

                double gradient=0;
                rep(k,y.size()){
                    gradient+=(error_plus[i]-error_minus[i])/(2*1e-4);
                }
                gradient/=y.size();
                grad[l]["param"][i][j]=gradient;
            }

            // bias
            double tmp_bias=layers[l].bias[j];

            // x-h
            layers[l].bias[j]=tmp_bias-(1e-4);
            auto t_minus_bias=predict(x);
            vector<double> error_minus_bias;
            if(loss=="cross_entropy_error") error_minus_bias=Loss::cross_entropy_error(y,t_minus_bias);
            else if(loss=="mean_squared_error") error_minus_bias=Loss::mean_squared_error(y,t_minus_bias);


            // x+h
            layers[l].bias[j]=tmp_bias+(1e-4);
            auto t_plus_bias=predict(x);
            vector<double> error_plus_bias;
            if(loss=="cross_entropy_error") error_plus_bias=Loss::cross_entropy_error(y,t_plus_bias);
            else if(loss=="mean_squared_error") error_plus_bias=Loss::mean_squared_error(y,t_plus_bias);

            layers[l].bias[j]=tmp_bias;

            double gradient_bias=0;
            rep(i,y.size()){
                gradient_bias+=(error_plus_bias[j]-error_minus_bias[j])/(2*1e-4);
            }
            gradient_bias/=y.size();
            cout<<gradient_bias<<endl;
            grad[l]["bias"][0][j]=gradient_bias;
        }
    }

    return grad;
}


void Model::print_weights(){
    for(auto i:layers){
        cout<<"[";
        for(auto j:i.param){
            cout<<"[";
            for(auto k:j){
                cout<<k<<" ";
            }
            cout<<"]"<<endl;
        }
        cout<<"]"<<endl<<"[";
        for(auto j:i.bias){
            cout<<j<<" ";
        }
        cout<<"]"<<endl;
    }
}