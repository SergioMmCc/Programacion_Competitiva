#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, ll> pil;

const int maxn = 1e5 + 1;
const ll inf = 1e15, mod = 1e9 + 7;
vector<vector<pil>> graph(maxn);

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int source, int n, vector<ll>& d, vector<ll>& formas, vector<int>& mini, vector<int>& maxi){
    for(int i = 1; i <= n; i++) d[i] = inf;
    d[source] = 0;
    formas[source] = 1;
    mini[source] = 0;
    maxi[source] = 0;
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
                formas[v] = formas[u];
                mini[v] = mini[u] + 1;
                maxi[v] = maxi[u] + 1;
                pq.push({v, d[v]});
            }

            else if(d[v] == w1 + w2){
                formas[v] = (formas[v] + formas[u]) % mod;
                mini[v] = min(mini[v], mini[u] + 1);
                maxi[v] = max(maxi[v], maxi[u] + 1);
            }
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; ll w;
        cin>>u>>v>>w;
        graph[u].push_back({v, w});
    }
    vector<ll> d(n+1), formas(n+1);
    vector<int> mini(n+1), maxi(n+1);
    dijkstra(1, n, d, formas, mini, maxi);
    cout<<d[n]<<' '<<formas[n]<<' '<<mini[n]<<' '<<maxi[n]<<endl;
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