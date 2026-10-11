#include <bits/stdc++.h>
using namespace std;

using ll=long long;

void solver() {
    int n;cin>>n;
    int ans=0;
    int streak=0;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        ans+=((x*2)-1);
        if(x==0)streak=0;
        else streak++;
        ans+=(streak>=3);
    }
    cout<<ans<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
