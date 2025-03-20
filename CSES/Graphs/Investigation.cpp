#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
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

void solver(){
    int n, m, s; cin>>n>>m>>s;
    for(int i = 0; i < m; i++){
        int u, v; ll w;
        cin>>u>>v>>w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    vector<ll> d(n+1);
    dijkstra(s, n, d);
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