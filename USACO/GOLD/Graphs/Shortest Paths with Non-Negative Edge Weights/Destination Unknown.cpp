#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2001, inf = 1e9;
vector<vector<pii>> graph(maxn);

struct comp{
    bool operator() (pii a, pii b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int source, int n, vector<int>& d){
    for(int i = 1; i <= n; i++) d[i] = inf;
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
                pq.push({v.first, d[v.first]});
            }
        }
    }
}

void solver(){
    int n, m, t; cin>>n>>m>>t;
    for(int i = 1; i <= n; i++) graph[i].clear();

    int s, g, h; cin>>s>>g>>h;
    int edgeW;
    for(int i = 0; i < m; i++){
        int u, v, w; cin>>u>>v>>w;
        if((u == g && v == h) || (u == h && v == g)) edgeW = w;
        graph[u].pb({v, w});
        graph[v].pb({u, w});
    }

    vector<int> possible(t);
    for(int i = 0; i < t; i++) cin>>possible[i];
    sort(possible.begin(), possible.end());

    vector<int> ds(n+1), dg(n+1), dh(n+1);
    dijkstra(s, n, ds);
    dijkstra(g, n, dg);
    dijkstra(h, n, dh);

    vector<int> ans;
    for(int x : possible){
        if(ds[g] + dh[x] + edgeW == ds[x] || ds[h] + dg[x] + edgeW == ds[x]) ans.pb(x);
    }

    for(int i = 0; i < ans.sz; i++){
        if(i) cout<<' ';
        cout<<ans[i];
    }
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}