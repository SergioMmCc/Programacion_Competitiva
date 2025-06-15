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
typedef pair<ll, int> pli;
typedef pair<pli, int> plii;

const int maxn = 1e5 + 5;
const ll inf = 1e18;

map<int, vector<pli>> graph[maxn];
map<int, ll> pSum[maxn];
vector<ll> dp1(maxn, inf);
map<int, ll> dp2[maxn];

void dijkstra(){
    dp1[1] = 0;
    priority_queue<plii> pq;
    pq.push({{0, 1}, 0});

    while(!pq.empty()){
        int u = pq.top().fi.se, c = pq.top().se; ll w1 = -1 * pq.top().fi.fi; pq.pop();

        if(c){
            if(dp2[u][c] < w1) continue;
            
            ll total = w1 + pSum[u][c];
            for(pli edge : graph[u][c]){
                int v = edge.se; ll w2 = edge.fi;
                if(total - w2 < dp1[v]){
                    dp1[v] = total - w2;
                    pq.push({{-dp1[v], v}, 0});
                }
            }
        }

        else{
            if(dp1[u] < w1) continue;

            for(auto par : graph[u]){
                int c = par.fi;
                ll total = w1 + pSum[u][c];
                for(pli edge : graph[u][c]){
                    int v = edge.se; ll w2 = edge.fi;

                    // Flip esa arista
                    if(w1 + w2 < dp1[v]){
                        dp1[v] = w1 + w2;
                        pq.push({{-dp1[v], v}, 0});
                    }

                    // Flip las demas aristas
                    if(total - w2 < dp1[v]){
                        dp1[v] = total - w2;
                        pq.push({{-dp1[v], v}, 0});
                    }

                    // Flip esa y enviar a dp2
                    if(!dp2[v].count(c) || w1 < dp2[v][c]){
                        dp2[v][c] = w1;
                        pq.push({{-dp2[v][c], v}, c});
                    }
                }
            }
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v, c; ll w; cin>>u>>v>>c>>w;
        pSum[u][c] += w;
        pSum[v][c] += w;
        graph[u][c].pb({w, v});
        graph[v][c].pb({w, u});
    }

    dijkstra();
    cout<<(dp1[n] == inf ? -1 : dp1[n])<<endl;
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