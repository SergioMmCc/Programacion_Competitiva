#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
#define pb push_back
typedef pair<int, ll> pil;
typedef pair<pil, bool> pilb;

const int maxn = 1e5 + 1;
const ll inf = 1e17;
vector<pilb> graph[maxn];
vector<ll> d(maxn);
vector<bool> kind(maxn);
int ans = 0;

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

void dijkstra(int source, int n){
    priority_queue<pil, vector<pil>, comp> pq;
    for(int i = 1; i <= n; i++){
        if(d[i] != inf) pq.push({i, d[i]});
    }

    while(!pq.empty()){
        int u = pq.top().first; ll w = pq.top().second;
        pq.pop();
        if(d[u] < w) continue;
        for(pilb v : graph[u]){
            if(d[v.first.first] > w + v.first.second || (d[v.first.first] == w + v.first.second && kind[v.first.first] && !v.second)){
                if(kind[v.first.first] && !v.second){
                    ans++;
                    kind[v.first.first] = 0;
                }
                d[v.first.first] = w + v.first.second;
                pq.push({v.first.first, d[v.first.first]});
            }
        }
    }
}

void solver(){
    int n, m, k; cin>>n>>m>>k;
    for(int i = 2; i <= n; i++) d[i] = inf;
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin>>u>>v>>w;
        graph[u].pb({{v, w}, 0});
        graph[v].pb({{u, w}, 0});
    }

    for(int i = 0; i < k; i++){
        int u; ll w; cin>>u>>w;
        if(d[u] != inf) ans++;
        d[u] = min(d[u], w);
        graph[1].pb({{u, w}, 1});
        graph[u].pb({{1, w}, 1});
        kind[u] = 1;
    }

    dijkstra(1, n);
    cout<<ans<<endl;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    while(t--){
        solver();
    }

    return 0;
}