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

const int maxn = 1e5 + 1;
vector<vi> tree(maxn);
vi id, depth(maxn), start(maxn);

struct rmq {
    int n, lgn;
    vector<vii> st;
    inline pii oper(pii a, pii b){ return a < b ? a : b; } // Change

    void build(const vii& a){
        n = sz(a);
        lgn = 32 - __builtin_clz(n); // floor(log2(n))
        st.assign(lgn, vii(n));
        st[0] = a;
        for1(j,lgn) 
            for(int i = 0; i + (1 << j) - 1 < n; i++) 
                st[j][i] = oper(st[j-1][i], st[j-1][i + (1 << (j-1))]);
    }

    pii calc(int l, int r){ // [l, r]
        int j = 31 - __builtin_clz(r-l+1); // floor(log2(r-l+1))
        return oper(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

// Halla los valores correspondientes de los arrays depth, id y start
void DFS(int u, int pa){
    start[u] = sz(id); // Marcar en que momento se visito por primera vez
    id.pb(u); // Insertar cuando se visita el nodo por primera vez
    for(int v : tree[u]){
        if(v == pa) continue;
        depth[v] = depth[u] + 1;
        DFS(v, u);
        id.pb(u); // Insertar cada vez que se regresa al nodo
    }
}

int LCA(int a, int b, rmq& st){
    if(start[a] > start[b]) swap(a, b); // Se asegura que start[a] corresponda a l y start[b] a r
    return st.calc(start[a], start[b]).se; // Query a la sparse table
}

void addVertex(int n, vi& roots, vi& dis){
    vb vis(n+1);
    vi ndis(n+1);
    queue<int> q;
    for(int x : roots){
        vis[x] = 1;
        dis[x] = 0;
        q.push(x);
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(vis[v]) continue;
            vis[v] = 1;
            ndis[v] = ndis[u] + 1;
            q.push(v);
            if(ndis[v] < dis[v]) dis[v] = ndis[v];
        }
    }
}

void solver(){
    int n, q; cin>>n>>q;
    for1(i,n-1){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }
    DFS(1, -1);
    vii a;
    for0(i,sz(id)) a.pb({depth[id[i]], id[i]});
    rmq st; st.build(a);

    int r = sqrt(n);
    if(r*r < n) r++;
    vi add = {1}, dis(n+1, n); dis[1] = 0;
    vb mark(n+1); mark[1] = 1;
    while(q--){
        int op, u; cin>>op>>u;
        if(op == 1){
            if(mark[u]) continue;
            mark[u] = 1;
            add.pb(u);
            if(sz(add) == r){
                addVertex(n, add, dis);
                add.clear();
            }
        }
        else{
            if(mark[u]){
                cout<<0<<endl;
                continue;
            }
            int ans = dis[u];
            for(int x : add) ans = min(ans, depth[u] + depth[x] - 2*depth[LCA(u, x, st)]);
            cout<<ans<<endl;
        }
    }
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
