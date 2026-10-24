#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;

int n,k;
vector<ll>w;
ll pascal[55][55];

ll calc(ll lim){
    ll ans=0;
    int need=k;
    for(int i=n-1;i>=0 && need>0;i--){
        if(w[i]>lim)continue;
        if(i>=need)
            ans+=pascal[i][need];
        lim-=w[i];
        need--;
    }
    if(need==0)
        ans++;
    return ans;
}

void solver(){
    cin>>n>>k;
    w.resize(n);
    for(auto&i:w)cin>>i;
    ll l,r;cin>>l>>r;
    sort(w.begin(),w.end());
    for(int i=0;i<=n;i++){
        pascal[i][0]=1;
        for(int j=1;j<=i;j++)
            pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
    }
    cout<<calc(r)-calc(l-1)<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
