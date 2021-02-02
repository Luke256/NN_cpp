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
            if(!isnan(t[i][j]) && isnan(log(t[i][j]+(1e-7))))exit(1);
        }
    }

    return error;
}

vector<double>Loss::mean_squared_error(const vector<vector<double>>&y, const vector<vector<double>>&t){
    vector<double>error(y.size(),0);
    rep(i,y.size()){
        rep(j,y[0].size()){
            error[i]+=pow(y[i][j]-t[i][j],2);
        }
    }

    return error;
}