#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, int> pil;

struct edge {
    int u, v; ll w;

    // Ordenar las aristas por el menor peso
    bool operator<(const edge& that) const {
        if(w != that.w) return w < that.w;
        if(v != that.v) return v < that.v;
        return u < that.u;
    }
};

const int maxn = 1e5 + 5;
vector<vector<int>> graph(maxn);
map<edge, int> T;
vector<int> ans(maxn);
int components;
vector<int> leader(maxn), sizen(maxn);
vector<bool> visited(maxn);
vector<int> sons[maxn], father(maxn);
map<int, int> dp;
set<pii> used;

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sizen[i] = 1;
    }
}

int find(int u){
    if(leader[u] != u)
        leader[u] = find(leader[u]);
    return leader[u];
}

void join(int u, int v){
    int leaderU = find(u), leaderV = find(v);
    if(leaderU != leaderV){
        if(sizen[leaderV] > sizen[leaderU])
            swap(leaderU, leaderV);
        leader[leaderV] = leaderU;
        sizen[leaderU] += sizen[leaderV];
        components--;
    }
}

void DFS(int u, int prev){
    visited[u] = 1;
    for(int v : graph[u]){
        if(v == prev) continue;
        if(visited[v]){
            if(used.find({v, u}) != used.end()) continue;
            dp[u]++;
            dp[v]--;
            used.insert({u, v});
            continue;
        }
        sons[u].pb(v);
        used.insert({u, v});
        father[v] = u;
        DFS(v, u);
    }
}

int calc(int u){
    for(int v : sons[u]) dp[u] += calc(v);
    return dp[u];
}

void groupProcess(vector<edge>& edges){
    set<int> a;

    map<pii, int> freq;
    for(int i = 0; i < edges.sz; i++){
        int u = find(edges[i].u), v = find(edges[i].v);
        if(u == v){
            ans[T[edges[i]]] = -1;
            continue;
        }
        
        if(u > v) swap(u, v);
        freq[{u, v}]++;
        a.insert(u); a.insert(v);
        graph[u].pb(v);
        graph[v].pb(u);
    }
    
    if(a.empty()) return;

    // set<int> roots;
    for(int vertex : a){
        if(!visited[vertex]){
            // roots.insert(vertex);
            DFS(vertex, -1);
            calc(vertex);
        }
    }
    
    for(int i = 0; i < edges.sz; i++){
        int u = find(edges[i].u), v = find(edges[i].v); if(u > v) swap(u, v);
        if(ans[T[edges[i]]] == -1) ans[T[edges[i]]] = 0;
        else if(((father[v] == u && (dp.find(v) == dp.end() || !dp[v])) || (father[u] == v && (dp.find(u) == dp.end() || !dp[u]))) && freq[{u, v}] == 1){
            ans[T[edges[i]]] = 2;
        }
        else ans[T[edges[i]]] = 1;
    }

    dp.clear();
    used.clear();
}

void kruskal(vector<edge>& edges, int n){
    sort(edges.begin(), edges.end());
    initDSU(n);

    ll lastW = edges[0].w;
    vector<edge> process;
    for(int i = 0; i < edges.sz; i++){
        if(components == 1) return;
        int u = edges[i].u, v = edges[i].v; ll w = edges[i].w;
        if(w != lastW){
            groupProcess(process);
            for(int j = 0; j < process.sz; j++){
                int u = find(process[j].u), v = find(process[j].v);
                join(u, v);
                visited[u] = visited[v] = 0;
                sons[u].clear(); sons[v].clear();
                father[u] = father[v] = 0;
                graph[u].clear(); graph[v].clear();
            }
            process.clear();
        }
        process.pb(edges[i]);
        lastW = w;
    }

    groupProcess(process);
}

void solver(){
    int n, m; cin>>n>>m;
    vector<edge> edges;
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin>>u>>v>>w;
        if(u > v) swap(u, v);
        edge newEdge; newEdge.w = w, newEdge.u = u, newEdge.v = v;
        T[newEdge] = i;
        edges.pb(newEdge);
    }

    kruskal(edges, n);

    for(int i = 0; i < m; i++){
        if(ans[i] < 1) cout<<"none"<<endl;
        else if(ans[i] == 1) cout<<"at least one"<<endl;
        else cout<<"any"<<endl;
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
