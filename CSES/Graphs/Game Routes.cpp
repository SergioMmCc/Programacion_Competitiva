#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2e5 + 1, mod = 1e9 + 7;
vector<vector<int>> inGraph(maxn), outGraph(maxn);
vector<bool> visited(maxn);
vector<int> topo_sort;

void DFS(int u, vector<int>& orden){
    for(int v : inGraph[u]){
        if(visited[v]) continue;
        visited[v] = 1;
        DFS(v, orden);
    }
    orden.pb(u);
}

void topoSort(int n, vector<int>& orden){
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            visited[i] = 1;
            DFS(i, orden);
        }
    }

    reverse(orden.begin(), orden.end());
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        inGraph[u].pb(v);
        outGraph[v].pb(u);
    }

    vector<int> orden;
    topoSort(n, orden);
    vector<int> paths(n+1); paths[1] = 1;
    for(int u : orden){
        for(int v : outGraph[u]){
            paths[u] += paths[v];
            paths[u] %= mod;
        }
    }

    cout<<paths[n]<<endl;
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