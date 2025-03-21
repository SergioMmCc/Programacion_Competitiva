#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, ll> pil;

struct Edge{
    int u, v; ll w;
};

const ll inf = 1e15;
const int maxn = 2501;
vector<vector<int>> graph(maxn);

void bellmanFord(int s, int n, vector<Edge>& edges, vector<ll>& d, vector<bool>& mark){
    for(int i = 1; i <= n; i++) d[i] = inf;
    d[s] = 0;

    for(int i = 1; i < n; i++){
        bool cond = 0;
        for(Edge e : edges){
            int u = e.u, v = e.v; ll w = e.w;
            if(d[u] < inf && d[v] > d[u] + w){
                d[v] = d[u] + w;
                cond = 1;
            }
        }

        if(!cond) return;
    }

    for(Edge e : edges){
        int u = e.u, v = e.v; ll w = e.w;
        if(d[u] < inf && d[v] > d[u] + w) mark[v] = 1; // Si hay ciclos de peso negativo pasando por ese vertice
    }
}

bool BFS(int s, int n, vector<bool>& marked){
    vector<bool> visited(n+1); visited[s] = 1;
    queue<int> q; q.push(s);

    while(!q.empty()){
        int u = q.front(); q.pop();
        if(marked[u]) return 0;
        for(int v : graph[u]){
            if(visited[v]) continue;

            visited[v] = 1;
            q.push(v);
        }
    }

    return 1;
}

void solver(){
    int n, m; cin>>n>>m;
    vector<Edge> edges;
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin>>u>>v>>w; w *= -1;
        graph[v].pb(u);
        edges.pb({u, v, w});
    }

    vector<ll> d(n+1); vector<int> parent(n+1); vector<bool> marked(n+1);
    bellmanFord(1, n, edges, d, marked);

    bool cond = BFS(n, n, marked);

    cout<<(cond ? -1 * d[n] : -1)<<endl;
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