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

struct edge {
    int u, v; ll w;

    // Ordenar las aristas por el menor peso
    bool operator<(const edge& that) const {
        return w < that.w; // Cambiar '<' por '>' para hallar el Maximal Spanning Tree
    }
};

const int maxn = 100005;
int components;
vector<int> leader(maxn), sizen(maxn);

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sizen[i] = 1;
    }
}

int find(int u){
    if(leader[u] != u)
        leader[u] = find(leader[u]);
    return leader[u];
}

void join(int u, int v){
    int leaderU = find(u), leaderV = find(v);
    if(leaderU != leaderV){
        if(sizen[leaderV] > sizen[leaderU])
            swap(leaderU, leaderV);
        leader[leaderV] = leaderU;
        sizen[leaderU] += sizen[leaderV];
        components--;
    }
}

ll kruskal(vector<edge>& edges, int n){
    ll total = 0;
    sort(edges.begin(), edges.end());
    initDSU(n);

    for(int i = 0; i < sz(edges); i++){
        int u = edges[i].u, v = edges[i].v; ll w = edges[i].w;
        if(find(u) != find(v)){
            total = max(total, w);
            join(u, v);
        }
    }

    return total; // Retornar el peso total del MST
}

void solver(){
    int n, m; cin>>n>>m;
    vector<edge> edges;
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin>>u>>v>>w;
        edge newEdge; newEdge.w = w, newEdge.u = u, newEdge.v = v;
        edges.pb(newEdge);
    }

    cout<<kruskal(edges, n)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
