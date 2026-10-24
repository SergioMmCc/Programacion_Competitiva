#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;

void solver(){
    int n,a,b;cin>>n>>a>>b;
    vector<ld>dp(n+1,0.0),ps(n+1,0.0);
    ld len=b-a+1;
    for(int i=1;i<=n;i++){
        int l=max(0,i-b);
        int r=i-max(1,a);
        ld s=0.0;
        if(r>=0){
            s=ps[r];
            if(l>0)
                s-=ps[l-1];
        }
        if(a==0)
            dp[i]=(s+len)/(len-1.0);
        else
            dp[i]=1.0+s/len;
        ps[i]=ps[i-1]+dp[i];
    }
    cout<<fixed<<setprecision(6)<<dp[n]<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
