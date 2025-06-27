#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;
typedef pair<int, bool> pib;
typedef pair<pii, pib> piiib;

const int inf = 1e9, maxn = 2001;
vector<vector<int>> tree(maxn);
vector<vector<pii>> graph(maxn);
set<pii> edgeI;

struct comp{
    bool operator() (piiib a, piiib b){
        if(a.fi.se == b.fi.se) return a.se.se < b.se.se;
        return a.fi.se > b.fi.se;
    }
};

void Dijsktra(int s, int n, vector<int>& d, bool add, vector<int>& parent){
    d[s] = 0;
    priority_queue<piiib, vector<piiib>, comp> pq;
    pq.push({{s, 0}, {-1, 0}});
    while(!pq.empty()){
        int u = pq.top().fi.fi, w1 = pq.top().fi.se, pa = pq.top().se.fi;
        pq.pop();

        if(d[u] != w1) continue;
        if(add){
            parent[u] = pa;
        }

        for(pii edge : graph[u]){
            int v = edge.fi, w2 = edge.se;
            if(d[v] > w1 + w2){
                d[v] = w1 + w2;
                bool cond = 0;
                if(edgeI.find({u, v}) != edgeI.end()) cond = 1;
                pq.push({{v, d[v]}, {u, cond}});
            }
        }
    }
}

void fillGrupo(int n, int s, int skip, vector<bool>& grupo){
    vector<bool> visited(n+1);
    visited[s] = 1; visited[skip] = 1;

    grupo[s] = 1;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            q.push(v);
            grupo[v] = 1;
        }
    }
}

void solver(){
    int n, m, a, b; cin>>n>>m>>a>>b;
    vector<pii> skip;
    for(int i = 1; i <= m; i++){
        int u, v, w; cin>>u>>v>>w;
        // if(u > v) swap(u, v);
        // edges[i] = {u, v, w, 1};
        // edgeI[{u, v}] = i;
        graph[u].pb({v, w});
        graph[v].pb({u, w});
    }

    int k; cin>>k;
    int last; cin>>last;
    map<int, int> pa;
    for(int i = 1; i < k; i++){
        int next; cin>>next;

        // edges[edgeI[{min(last, next), max(last, next)}]].used = 0;
        // skip.pb({min(last, next), max(last, next)});
        skip.pb({last, next});
        edgeI.insert({last, next});
        pa[next] = last;
        last = next;
    }

    vector<int> da(n+1, inf), db(n+1, inf);
    vector<int> parent(n+1);
    Dijsktra(a, n, da, 1, parent);
    Dijsktra(b, n, db, 0, parent);

    // Al parecer esto lo halla bien
    for(int i = 1; i <= n; i++){
        if(pa.find(i) != pa.end()){
            assert(pa[i] == parent[i]);
        }

        if(parent[i] > 0){
            tree[i].pb(parent[i]);
            tree[parent[i]].pb(i);
        }
    }

    // for(int u = 1; u <= n; u++){
    //     for(int v : tree[u]) cout<<u<<" -> "<<v<<endl;
    // }

    for(pii edge : skip){
        int u = edge.fi, v = edge.se;
        // cout<<"u -> "<<u<<" v -> "<<v<<endl;

        vector<bool> grupo(n+1);
        fillGrupo(n, u, v, grupo);
        
        // Recorrer el grafo
        int ans = inf;
        for(int i = 1; i <= n; i++){
            if(!grupo[i]) continue;
            for(pii e : graph[i]){
                int j = e.fi, w = e.se;
                if(grupo[j] || (i == u && j == v)) continue;
                ans = min(ans, da[i] + w + db[j]);
            }
        }

        cout<<(ans == inf ? -1 : ans)<<endl;
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