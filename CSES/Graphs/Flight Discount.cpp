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
typedef pair<pil, bool> pilb;

const int maxn = 1e5 + 1;
const ll inf = 1e15;
vector<pil> graph[maxn];

struct comp{
    bool operator() (pilb a, pilb b){
        if(a.fi.se == b.fi.se) return a.se > b.se;
        return a.fi.se > b.fi.se;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int source, int n, vector<ll>& d0, vector<ll>& d1){
    for(int i = 1; i <= n; i++){
        d0[i] = inf;
        d1[i] = inf;
    }
    d0[source] = 0;
    d1[source] = 0;

    priority_queue<pilb, vector<pilb>, comp> pq;
    pq.push({{source, 0}, 0});
    while(!pq.empty()){
        int u = pq.top().fi.fi; ll w1 = pq.top().fi.se; bool used = pq.top().se;
        pq.pop();
        if((used && d1[u] < w1) || (!used && d0[u] < w1)) continue;
        for(pil edge : graph[u]){
            int v = edge.fi; ll w2 = edge.se;
            if(used){
                if(d1[v] > w1 + w2){
                    d1[v] = w1 + w2;
                    pq.push({{v, d1[v]}, 1});
                }
            }
            else{
                if(d0[v] > w1 + w2){
                    d0[v] = w1 + w2;
                    pq.push({{v, d0[v]}, 0});
                }

                if(d1[v] > w1 + w2 / 2){
                    d1[v] = w1 + w2 / 2;
                    pq.push({{v, d1[v]}, 1});
                }
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
    vector<ll> d0(n+1), d1(n+1);
    dijkstra(1, n, d0, d1);
    cout<<d1[n]<<endl;
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