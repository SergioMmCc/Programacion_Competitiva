#include <bits/stdc++.h>
using namespace std;

using ll=long long;

void solver(){
    int n,k,l;cin>>n>>k>>l;
    string s;cin>>s;
    string r="";
    if(l>0)cin>>r;
    vector<bool> bad(26,0);
    for(char c:r)bad[c-'a']=1;
    vector<int> p;
    p.push_back(-1);
    for(int i=0;i<n;i++)
        if(bad[s[i]-'a'])p.push_back(i);
    p.push_back(n);
    ll ans=0;
    for(int i=1;i+k<(int)p.size();i++){
        ll left=p[i]-p[i-1];
        ll right=p[i+k]-p[i+k-1];
        ans+=left*right;
    }
    cout<<ans<<"\n";
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}