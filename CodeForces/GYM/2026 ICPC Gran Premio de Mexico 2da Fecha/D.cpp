#include <bits/stdc++.h>
using namespace std;

using ld=long double;

const ld EPS = numeric_limits<ld>::epsilon();

struct Vector2D {
  ld x,y;
  Vector2D(ld x,ld y):x(x),y(y){}
  static ld euclidean_distance(Vector2D a,Vector2D b){
    return hypot(a.x-b.x,a.y-b.y);
  }
};

void solver(){
    ld x1,y1,r1;cin>>x1>>y1>>r1;
    ld x2,y2,r2;cin>>x2>>y2>>r2;
    ld k;cin>>k;

    if(2.0L*max(r1,r2)-k>-EPS){
        cout<<"YES\n";
        return;
    }
    Vector2D A(x1,y1),B(x2,y2);
    ld dist=Vector2D::euclidean_distance(A,B);
    if(r1+r2>dist-EPS && dist+r1+r2>k-EPS){
        cout<<"YES\n";
        return;
    }
    cout<<"NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;cin>>t;
    while(t--)solver();
}
