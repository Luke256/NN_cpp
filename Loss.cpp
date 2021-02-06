#include <bits/stdc++.h>
#include "Loss.h"

#define rep(i,n) for(ll i=0;i<n;++i)

using namespace std;
using ll=long long;

vector<double>Loss::cross_entropy_error(const vector<vector<double>>&y, const vector<vector<double>>&t){
    vector<double>error(y.size(),0);
    rep(i,y.size()){
        rep(j,y[0].size()){
            error[i]-=y[i][j]*log(t[i][j]+(1e-7));
        }
    }

    return error;
}

vector<double>Loss::mean_squared_error(const vector<vector<double>>&y, const vector<vector<double>>&t){
    vector<double>error(y.size(),0);
    rep(i,y.size()){
        rep(j,y[i].size()){
            double o=error[i];
            error[i]+=pow(t[i][j]-y[i][j],2);
            // cout<<o<<":"<<error[i]<<":"<<y[i][j]<<":"<<t[i][j]<<":"<<endl;
        }
        error[i]/=2.0;
    }

    return error;
}