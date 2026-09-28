// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

const long double INF=1e9, DELTA=1E-7;

long double form(long double r, long double R, long double h){
    return (M_PI * h * (R*R + r*r + R*r)) / 3.0;
}

bool op(long double x, long double r, long double R, long double h){
    long double k = x*(R-r)/h;
    //cout<<x<<" | "<<form(r, k, x)<<" # "<<form(k, R, h-x)<<" => "<<(form(r, k, x) < form(k, R, h-x))<<"\n";
    return form(r, r+k, x) < form(r+k, R, h-x);
}

void solve(){
    long double r, R, h;
    cin>>r>>R>>h;

    long double ll=0, lr=h;
    while(lr-ll > DELTA){
        long double x = (lr+ll)/2;
        if(op(x, r, R, h)){
            ll = x;
        }else{
            lr = x - DELTA;
        }
    }
    //cout<<"["<<ll<<", "<<lr<<"]\n";
    cout<<fixed<<setprecision(7)<<ll<<"\n";
}

int main() {

    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
