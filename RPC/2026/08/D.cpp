// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

struct P{
    int x, y;
};

int n, r, w, h;

// NAAAAH A FUCKING INTEGRAL OF
// X^2+Y^2=R^2 -> [a, b] {sqrt(r^2 - x^2)}
// = 1/2 * ( x*sqrt(r^2-x^2) + r^2*arctg(x/sqrt(r^2-x^2))) | {a, b}
double form(double x){
    double I = max(0.0, sqrt(r*r - x*x));
    return 0.5 * (x*I + r*r * atan(x / I));
}

double Acircle(double a, double b){
    return form(b) - form(a);
}

// asume the part circle and rectagle start at the oirg point
//sending new rectangle
double Q(int nw, int nh){
    // find intersect points idiot
    double p;
    double L = min(nw, r);
    if(nh > r){
        p = 0;
    }else{
        // NO NEGATRIVES WHYYYYYYYYYYYYYYY HAPEND THAT
        p = max(0.0, sqrt(r*r - nh*nh));
    }
    p = min(p, L);

    double A = nh*p + Acircle(p, L);
    return A;


}

int main() {
    cin>>n>>r>>w>>h;
    vector<P> points(n);
    vector<int> cost(n);
    for(int i=0; i<n; i++){
        cin>>points[i].x>>points[i].y>>cost[i];
    }

    // all dumb data readeng, go to the stupid implementation

    double ans = 0;
    for(int i=0; i<n; i++){
        // too lazy to put this in the read input
        int x = points[i].x;
        int y = points[i].y;
        //cout<<x<<" - "<<y<<"\n";

        // ALL THE 4 FUCKING SEGMENTS AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        /*
        Q2 | Q1
        -------
        Q3 | Q4
        */
        double Q1, Q2, Q3, Q4;
        Q1 = Q(w-x, h-y);
        Q2 = Q(x, h-y);
        Q3 = Q(x, y);
        Q4 = Q(w-x, y);

        //cout<<Q1<<", "<<Q2<<", "<<Q3<<", "<<Q4<<"\n";

        // simplex sum
        double A = Q1+Q2+Q3+Q4;


        // probability weigtheded
        double P = A * cost[i];
        ans += P;
    }

    // WHAT ELSE MORE, JUST THE FUCKING RECTANGLE
    ans /= w*h;
    cout<<fixed<<setprecision(9)<<ans<<"\n";
}
