// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int dfs(int v, int p, vector<vector<int>>& gp, vector<int>& vis){
    if(vis[v]) return 0;
    vis[v] = 1;
    int k=1;
    for(int x : gp[v]){
        if(vis[x]) continue;
        k += dfs(x, -1, gp, vis);
    }
    return k;
}

int main() {

    int n, p;
    while(true){
        cin>>n>>p;
        if(n == 0 && p == 0) break;

        vector<vector<int>> gp(n+1);
        int u, v;
        for(int i=0; i<p; i++){
            cin>>u>>v;
            gp[u].push_back(v);
            gp[v].push_back(u);
        }

        vector<int> vis(n+1);
        int up=1, cnt=0;
        for(int i=1; i<=n; i++){
            if(!vis[i]){
                //cout<<i<<" - "<<k<<" -*\n";
                up = max(up, dfs(i, -1, gp, vis));
                cnt++;
            }
        }

        cout<<cnt<<" "<<up<<"\n";
    }
    return 0;
}
