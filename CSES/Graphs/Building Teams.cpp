#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 100005;
vector<int> graph[maxn];
vector<bool> color(maxn);
vector<bool> visited(maxn);
bool bipartite = 1;

void DFS(int u){
    for(int v : graph[u]){
        if(!visited[v]){
            color[v] = !color[u];
            visited[v] = 1;
            DFS(v);
        }
        else if(color[v] == color[u]) bipartite = 0;
    }
}

void DFS_visit(int n){
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            visited[i] = 1;
            DFS(i);
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    DFS_visit(n);

    if(!bipartite) cout<<"IMPOSSIBLE"<<endl;
    else{
        for(int i = 1; i <= n; i++){
            if(i > 1) cout<<' ';
            if(color[i]) cout<<2;
            else cout<<1;
        }
        cout<<endl;
    }
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