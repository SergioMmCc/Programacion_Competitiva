#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;

void solver(){
    int n,t;cin>>n>>t;
    ld ans=0.0L;
    for(int i=0;i<n;i++){
        char c;int x;cin>>c>>x;
        ans+=x;
    }
    ans/=t;
    cout<<fixed<<setprecision(6)<<ans<<"\n";
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
