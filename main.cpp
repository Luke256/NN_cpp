#include <bits/stdc++.h>
#include"Model.h"

#define rep(i,n) for(ll i=0;i<n;++i)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
    vector<pair<int,string> >config;
    config.push_back(make_pair<int,string>(10,"leaner"));
    config.push_back(make_pair<int,string>(10,"sigmoid"));
    Model model(2,1,2,config);
    map<string,double> optimizer_option;
    optimizer_option["learning_rate"]=0.001;
    model.set_optimizer("sgd",optimizer_option);
    

    vector<vector<double>>x;
    x.push_back({1,0});
    x.push_back({1,1});
    x.push_back({0,0});
    x.push_back({0,1});

    vector<vector<double>>y;
    y.push_back({0});
    y.push_back({1});
    y.push_back({0});
    y.push_back({0});

    model.print_weights();

    auto history=model.fit(x,y,1000,0,"mean_squared_error",4);

    cout<<"-------------------"<<endl;
    model.print_weights();

    // auto t=model.predict(x);
    // for(auto i:t){
    //     for(auto j:i){
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
}