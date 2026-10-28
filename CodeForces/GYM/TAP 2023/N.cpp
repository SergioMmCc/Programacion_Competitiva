#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;

ll c[5];
ll ans=0;

void make_groups(int x,int need_x,int y,int need_y){
    ll groups=min(c[x]/need_x,c[y]/need_y);
    ans+=groups;
    c[x]-=groups*need_x;
    c[y]-=groups*need_y;
}

void solver(){
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        c[x%5]++;
    }
    ans+=c[0];
    make_groups(1,1,4,1);
    make_groups(2,1,3,1);
    make_groups(1,1,2,2);
    make_groups(2,1,4,2);
    make_groups(3,1,1,2);
    make_groups(4,1,3,2);
    make_groups(2,1,1,3);
    make_groups(4,1,2,3);
    make_groups(1,1,3,3);
    make_groups(3,1,4,3);
    for(int i=1;i<=4;i++){
        ans+=c[i]/5;
    }
    cout<<ans<<"\n";
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}