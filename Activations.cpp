#include "Activations.h"
#include <math.h>

Activation::Activation(string type_):
type(type_)
{
}
double Activation::forward(double x){
    if(type=="relu") return Relu::forward(x,data);
    else if(type=="sigmoid") return Sigmoid::forward(x,data);
}

double Relu::forward(double x,map<string,double>data){
    if(x>0) return x;
    else return 0;
}

double Sigmoid::forward(double x,map<string,double>data){
    return 1/(1+exp(-x));
}

double Leaner::forward(double x,map<string,double>data){
    return x;
}