#include <bits/stdc++.h>
using namespace std;

void solver(){
    int n;cin>>n;
    long double ans=0;
    map<int,multiset<int>>mp;
    for(int i=0;i<n;i++){
        int s,c;cin>>s>>c;
        mp[s].insert(c);
    }
    for(auto&[a,b]:mp){
        auto b0=b.begin(),b1=b.end();b1--;
        while(b0!=b1){
            ans-=log(*b0);
            ans+=log(*b1);
            b0++;
            if(b0==b1)break;
            b1--;
        }
    }
    cout<<fixed<<setprecision(7)<<ans<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
