#include <bits/stdc++.h>
using namespace std;

using ll=long long;

void solver() {
    int n;cin>>n;
    vector<int>pos(n+1);
    for(int i=0;i<n;i++){
        int x;cin>>x;
        pos[x]=i;
    }
    int m=1;
    for(int i=1;i<n;i++)
        if(pos[i]>pos[i+1])
            m++;
    int ans=0;
    while((1<<ans)<m)ans++;
    cout<<ans<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
