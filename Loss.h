#pragma once
#include <bits/stdc++.h>

using namespace std;
using ll=long long;

namespace Loss{
    vector<double>cross_entropy_error(const vector<vector<double>>&y, const vector<vector<double>>&t);
    vector<double>mean_squared_error(const vector<vector<double>>&y, const vector<vector<double>>&t);
}