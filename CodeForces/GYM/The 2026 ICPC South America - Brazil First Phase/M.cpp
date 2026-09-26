#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forlr(i,l,r) for(int i = (int)l; i <= (int)r; i++)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define forn0(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define forrl(i,l,r) for(int i = (int)r; i >= (int)l; i--)
#define pb push_back
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pqueue priority_queue
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, bool> pib;
typedef pair<int, ll> pil;
typedef pair<pib, ll> pibl;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

struct Edge {
    int to; ll f, w;
};

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};
struct comp1{
    bool operator() (pibl a, pibl b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
ll dijkstra(int n, int k, vector<vector<Edge>>& graf){
    vector<vl> dis(k+1, vl(n+1, INFL));
    for0(i,k+1) dis[i][1] = 0;
    
    // Primera corrida, sin edges especiales
    pqueue<pil, vector<pil>, comp> pq;
    pq.push({1, 0});
    while(!pq.empty()){
        int u = pq.top().fi; ll w1 = pq.top().se;
        pq.pop();
        if(dis[0][u] < w1) continue;

        for(Edge& e : graf[u]){
            int v = e.to; ll w2 = e.f;
            if(dis[0][v] > w1 + w2){
                dis[0][v] = w1 + w2;
                pq.push({v, dis[0][v]});
            }
        }
    }

    for1(i,k){
        for1(u,n) dis[i][u] = dis[i-1][u];
        for1(u,n){
            for(Edge e : graf[u]){
                int v = e.to; ll f = e.f, w = (e.w == -1 ? INFL : e.w);
                dis[i][v] = min(dis[i][v], dis[i-1][u] + min(f, w));
            }
        }
        for1(u,n) pq.push({u, dis[i][u]});

        while(!pq.empty()){
            int u = pq.top().fi; ll w1 = pq.top().se; pq.pop();
            if(dis[i][u] < w1) continue;

            for(Edge &e : graf[u]){
                int v = e.to; ll f = e.f;

                if(dis[i][v] > w1 + f){
                    dis[i][v] = w1 + f;
                    pq.push({v, dis[i][v]});
                }
            }
        }
    }

    return dis[k][n];
}

void solver(){
    int n, m, k; cin>>n>>m>>k;
    vector<vector<Edge>> graf(n+1);
    for0(i,m){
        int u, v; ll f, w; cin>>u>>v>>f>>w;
        graf[u].pb({v, f, w});
        graf[v].pb({u, f, w});
    }

    cout<<dijkstra(n, k, graf)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
