#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, ll> pil;

const int maxn = 1000;
const ll inf = 1e17;

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

void dijkstra(int source, int n, vector<ll>& d, vector<vector<pil>>& graph){
    for(int i = 0; i < n; i++) d[i] = inf;
    d[source] = 0;
    priority_queue<pil, vector<pil>, comp> pq;
    pq.push({source, 0});
    while(!pq.empty()){
        int u = pq.top().first; ll w1 = pq.top().second;
        pq.pop();
        if(d[u] < w1) continue;
        for(pil edge : graph[u]){
            int v = edge.first; ll w2 = edge.second;
            if(!w2) w2 = 1;
            if(d[v] > w1 + w2){
                d[v] = w1 + w2;
                pq.push({v, d[v]});
            }
        }
    }
}

void dijkstra2(int source, int n, ll l, vector<ll>& d1, vector<ll>& d2, map<pii, ll>& edges, vector<vector<pil>>& graph){
    for(int i = 0; i < n; i++) d2[i] = inf;
    d2[source] = 0;
    priority_queue<pil, vector<pil>, comp> pq;
    pq.push({source, 0});
    while(!pq.empty()){
        int u = pq.top().first; ll w1 = pq.top().second;
        pq.pop();
        if(d2[u] < w1) continue;
        for(int i = 0; i < graph[u].sz; i++){
            pil edge = graph[u][i];
            int v = edge.first;
            ll w2;
            if(edges.find({u, v}) == edges.end()) w2 = edges[{v, u}];
            else w2 = edges[{u, v}];
            if(!w2){
                w2 = 1;
                if(w2 + w1 + d1[v] < l) w2 = l - w1 - d1[v];
                // cout<<"u -> "<<u<<" v -> "<<v<<" w2 -> "<<w2<<" w1 -> "<<w1<<" d1[v] -> "<<d1[v]<<endl;
                if(edges.find({u, v}) == edges.end()) edges[{v, u}] = w2;
                else edges[{u, v}] = w2;
            }

            if(d2[u] + w2 < d2[v]){
                d2[v] = d2[u] + w2;
                pq.push({v, d2[v]});
            }
        }
    }
}

void solver(){
    int n, m, s, t; ll l; cin>>n>>m>>l>>s>>t;
    vector<vector<pil>> graph(n);
    map<pii, ll> edges;
    for(int i = 0; i < m; i++){
        int u, v; ll w;
        cin>>u>>v>>w;
        edges[{u, v}] = w;
        graph[u].pb({v, w});
        graph[v].pb({u, w});
    }
    vector<ll> dt(n);
    dijkstra(t, n, dt, graph);

    if(dt[s] > l){
        cout<<"NO"<<endl;
        return;
    }

    vector<ll> ds(n);
    dijkstra2(s, n, l, dt, ds, edges, graph);
    if(ds[t] < l){
        cout<<"NO"<<endl;
        return;
    }

    cout<<"YES"<<endl;
    for(auto edge : edges){
        cout<<edge.first.first<<' '<<edge.first.second<<' '<<edge.second<<endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}