// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef pair<int, int> P;
typedef pair<int, int> V;

int dot(V a, V b){
    return a.x*b.x + a.y*b.y;
}

long double dist(P p){
    return sqrt(p.x*p.x + p.y*p.y); 
}

long double dist(long double a, long double b){
    return sqrt(a*a + b*b);
}

int main() {
    vector<P> p(3);
    cin>>
    p[0].x>>p[0].y>>
    p[1].x>>p[1].y>>
    p[2].x>>p[2].y;

    long double ans = 1e5;
    for(int i=0; i<3; i++){
        P A = p[i % 3];
        P B = p[(i+1) % 3];
        P C = p[(i+2) % 3];

        long double cx = (A.x + B.x)/2.0L;
        long double cy = (A.y + B.y)/2.0L;

        long double r = dist(A.x-B.x, A.y-B.y) / 2.0L;

        
        ans = min(ans, abs(dist(C.x-cx, C.y-cy) - r));


    }
    cout<<fixed<<setprecision(6)<<ans<<"\n";
}
