#include <bits/stdc++.h>
using namespace std;
 
using ll=long long;

const int maxn=100'000;
ll c[maxn],tot[maxn+1],ans[maxn+1],cur[maxn+1];
vector<pair<int,int>>g[maxn+1];
map<int,ll>mp[maxn+1];

void dfs(int u, int p) {
    mp[u][c[u]]=1;
    cur[u]=tot[c[u]]-1;
    for (auto[v,id]:g[u]) {
        if(v==p)continue;
        dfs(v,u);
        ans[id]=cur[v];
        cur[u]+=cur[v];
        if(mp[v].size()>mp[u].size())
            swap(mp[u],mp[v]);
        for(auto[col,k]:mp[v]) {
            cur[u]-=2*mp[u][col]*k;
            mp[u][col]+=k;
        }
    }
}

void solver() {
    int n;cin>>n;
    for (int i=1;i<=n;i++){
        cin>>c[i];
        tot[c[i]]++;
    }
    for (int i=0;i<n-1;i++) {
        int u,v;cin>>u>>v;
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }
    dfs(1,0);
    for(int i=0;i<n-1;++i)
        cout<<ans[i]<<" ";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}