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
typedef pair<pil, int> pili;
typedef pair<pil, pili> pilili;

const int maxn = 1e5 + 1;
const ll inf = 1e18;
vector<vector<pili>> graph(maxn);
vector<int> degree(maxn);
vector<map<int, ll>> adj(maxn);

struct comp{
    bool operator() (pilili a, pilili b){
        if(a.fi.se == b.fi.se) return a.se.fi.se > b.se.fi.se;
        return a.fi.se > b.fi.se;
    }
};

// Complejidad O(m*log(n))
ll dijkstra(int n){
    vector<ll> d(n+1, inf);
    d[1] = 0;
    priority_queue<pilili, vector<pilili>, comp> pq;
    pq.push({{1, 0}, {{-1, 0}, -1}});
    while(!pq.empty()){
        int u = pq.top().fi.fi, lastC = pq.top().se.fi.fi, pa = pq.top().se.se; ll w1 = pq.top().fi.se, change = pq.top().se.fi.se;
        pq.pop();
        if(!degree[u]) continue;
        degree[u]--;

        // cout<<"u -> "<<u<<" w1 -> "<<w1<<" parent -> "<<pa<<" color -> "<<lastC<<" change -> "<<change<<endl;

        for(pili edge : graph[u]){
            int v = edge.fi.fi, c = edge.se; ll w2 = edge.fi.se;
            if(pa == v) continue;

            // cout<<"\tv -> "<<v<<" w2 -> "<<w2<<" c -> "<<c<<" adj -> "<<adj[u][c]<<endl;

            if(c == lastC){
                ll tw = w1 + adj[u][c] - change - w2;
                d[v] = min(d[v], tw);
                pq.push({{v, tw}, {{c, 0}, u}});
            }
            else{
                ll tw = w1 + adj[u][c] - w2;
                d[v] = min(d[v], tw);
                pq.push({{v, tw}, {{c, 0}, u}});
            }
            
            d[v] = min(d[v], w1 + w2);
            pq.push({{v, w1 + w2}, {{c, w2}, u}});
        }
    }

    return d[n];
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v, c; ll w; cin>>u>>v>>c>>w;
        degree[u] += 2;
        degree[v] += 2;
        adj[u][c] += w;
        adj[v][c] += w;
        graph[u].pb({{v, w}, c});
        graph[v].pb({{u, w}, c});
    }

    ll ans = dijkstra(n);
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