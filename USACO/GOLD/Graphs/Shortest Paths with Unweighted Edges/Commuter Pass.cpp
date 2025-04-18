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
typedef pair<int, ll> pil;

const int maxn = 1e5 + 1;
const ll inf = 1e15;
vector<vector<pil>> graph(maxn);

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int source, int n, vector<ll>& d){
    for(int i = 1; i <= n; i++) d[i] = inf;
    d[source] = 0;
    priority_queue<pil, vector<pil>, comp> pq;
    pq.push({source, 0});
    while(!pq.empty()){
        int u = pq.top().first; ll w1 = pq.top().second;
        pq.pop();
        if(d[u] < w1) continue;
        for(pil edge : graph[u]){
            int v = edge.first; ll w2 = edge.second;
            if(d[v] > w1 + w2){
                d[v] = w1 + w2;
                pq.push({v, d[v]});
            }
        }
    }
}

ll dijkstra2(int s, int t, int n, vector<ll>& du, vector<ll>& dv){
    vector<bool> visited(n+1);
    vector<ll> dpU(n+1, inf), dpV(n+1, inf), ds(n+1, inf); 

    priority_queue<pair<ll, pii>> pq;
    pq.push({0, {s, 0}});
    while(!pq.empty()){
        ll w1 = pq.top().fi; int u = pq.top().se.fi, par = pq.top().se.se;
        pq.pop();

        if(!visited[u]){
            visited[u] = 1;
            ds[u] = -w1;
            dpU[u] = min(du[u], dpU[par]);
            dpV[u] = min(dv[u], dpV[par]);
            for(pil edge : graph[u]){
                int v = edge.fi; ll w2 = edge.se;
                if(ds[u] + w2 <= ds[v]) pq.push({-(ds[u] + w2), {v, u}});
            }
        }
        else if(ds[u] == -w1){
            if(min(du[u], dpU[par]) + min(dv[u], dpV[par]) <= dpU[u] + dpV[u]){
                // Aqui esta la clave:
                // Si la distancia usando otro nodo padre es mejor, entonces actualizo 
                // el dp bassado en ese, lo cual va a reducir la suma total pero
                // puede que incremente uno de los dos valores, asi se asegura que no utilice
                // optimizaciones de dos caminos diferentes
                dpU[u] = min(du[u], dpU[par]);
                dpV[u] = min(dv[u], dpV[par]);
            }
        }
    }
    
    return dpU[t] + dpV[t];
}

void solver(){
    int n, m, s, t, u, v; cin>>n>>m>>s>>t>>u>>v;
    for(int i = 0; i < m; i++){
        int a, b; ll w;
        cin>>a>>b>>w;
        graph[a].pb({b, w});
        graph[b].pb({a, w});
    }
    vector<ll> ds(n+1), du(n+1), dv(n+1);
    dijkstra(u, n, du);
    dijkstra(v, n, dv);

    ll ans = du[v];
    ans = min(ans, dijkstra2(s, t, n, du, dv));
    ans = min(ans, dijkstra2(t, s, n, du, dv));
    cout<<ans<<endl;
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