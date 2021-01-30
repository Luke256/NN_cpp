#include "bits/stdc++.h"
#include"Model.h"

#define rep(i,n) for(ll i=0;i<n;++i)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
    vector<pair<int,string> >config;
    config.push_back(make_pair<int,string>(10,"relu"));
    Model model(2,1,3,config,"sgd");

    vector<double> x;
    x.push_back(2);
    x.push_back(3);
}