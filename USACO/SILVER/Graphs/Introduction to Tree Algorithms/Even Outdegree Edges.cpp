#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1e5 + 2;
set<int> graph[maxn];
vector<vector<int>> ans;
vector<int> edges(maxn);
vector<bool> visited(maxn);

bool DFS(int u, int prev){
    visited[u] = 1;
    for(int v : graph[u]){
        if(v == prev) continue;
        if(visited[v]){
            if(v < u){
                ans.pb({u, v});
                edges[u]++;
            }
        }
        else{
            if(DFS(v, u)){
                ans.pb({v, u});
                edges[v]++;
            }
            else{
                ans.pb({u, v});
                edges[u]++;
            }
        }
    }

    return edges[u] % 2;
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    for(int i = 1; i <= n; i++){
        if(!visited[i]) DFS(i, -1);
    }

    bool cond = 1;
    for(int i = 1; i <= n; i++) cond &= !(edges[i] % 2);

    if(!cond){
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }

    for(int i = 0; i < ans.sz; i++) cout<<ans[i][0]<<' '<<ans[i][1]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}