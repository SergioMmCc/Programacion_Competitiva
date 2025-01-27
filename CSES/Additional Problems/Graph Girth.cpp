#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2501, inf = 1e9;
vector<vector<int>> graph(maxn);
vector<bool> visited(maxn);
set<pii> used;

int BFS2(int s, int des, int n){
    vector<bool> visitedAux(n+1); visitedAux[s] = 1;
    vector<int> d(n+1); d[s] = 0;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            if((u == s && v == des) || (u == des && v == s)) continue;
            if(visitedAux[v]) continue;
            visitedAux[v] = 1;
            d[v] = d[u] + 1;
            q.push(v); 
        }
    }

    return d[des];
}

int BFS1(int s, int n){
    int ans = inf;
    visited[s] = 1;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            int x = min(u, v), y = max(u, v);
            if(used.find({x, y}) != used.end()) continue;
            used.insert({x, y});
            if(visited[v]) ans = min(ans, BFS2(x, y, n) + 1);
            else{
                visited[v] = 1;
                q.push(v);
            }
        }
    }

    return ans;
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    int ans = inf;
    for(int i = 1; i <= n; i++){
        if(!visited[i]) ans = min(ans, BFS1(i, n));
    }

    cout<<(ans == inf ? -1 : ans)<<endl;
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