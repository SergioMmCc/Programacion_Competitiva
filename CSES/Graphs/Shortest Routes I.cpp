#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MAXN 200005
#define int long long

const int inf = 1e18;
typedef pair<int, int> pii;
vector<pii> graph[MAXN+1];

struct comp{
    bool operator() (pii a, pii b){
        return a.second > b.second;
    }
};

void dijkstra(int source, int n, vector<int>& d, vector<int>& parent){
    for(int i = 1; i <= n; i++){
        d[i] = inf;
        parent[i] = -1;
    }   
    d[source] = 0;
    priority_queue<pii, vector<pii>, comp> pq;
    pq.push({source, 0});
    while(!pq.empty()){
        int u = pq.top().first, w = pq.top().second;
        pq.pop();
        if(d[u] < w) continue;
        for(pii v : graph[u]){
            if(d[v.first] > w + v.second){
                d[v.first] = w + v.second;
                parent[v.first] = u;
                pq.push({v.first, d[v.first]});
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int n, m;cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        graph[u].push_back({v, w});
    }
    vector<int> d(n+1), parent(n+1);
    dijkstra(1, n, d, parent);
    for(int i = 1; i <= n; i++){
        if(i > 1) cout<<' ';
        cout<<d[i];
    }
    cout<<endl;

    return 0;
}