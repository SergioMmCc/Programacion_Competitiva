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
typedef pair<pii, ll> piil;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<piil> viil;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

struct segTree{
    int n; ll neutro = 0LL; // CHANGE neutro
    vl tree;
    inline ll op(ll a, ll b){ return max(a, b); } // CHANGE
    void init(int _n){
        n = _n;
        tree.assign(2*n, neutro);
    }
    void build(vl& a){
        for0(i, n) tree[n + i] = a[i];
        forrl(i, 1, n-1) tree[i] = op(tree[i<<1], tree[i<<1|1]);
    }
    ll calc(int l, int r){  // [l, r)
        ll resL = neutro, resR = neutro;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l&1) resL = op(resL, tree[l++]);
            if(r&1) resR = op(tree[--r], resR);
        }
        return op(resL, resR);
    }
    void update(int p, ll val){  // set val at position p (0 - idx)
        for(tree[p += n] = val; p > 1; p >>= 1) tree[p>>1] = op(tree[p], tree[p^1]);
    }
};

struct HLD {
    int n, t = 0; bool ve; vector<vi> g; vi par, dep, sub, head, pos, ord; segTree st;

    // g: lista de adyacencia, a: valor de cada nodo, r: raíz (1 por defecto), e: 1 si val en aristas, 0 si val en nodos
    HLD(vector<vi>& adj, vl& a, int r = 1, bool e = 0) : n(sz(adj)), ve(e), g(adj), par(n), dep(n), sub(n), head(n), pos(n) {
        dfs1(r); head[r] = r; dfs2(r);
        vl b; for(int x : ord) b.pb(a[x]);
        st.init(sz(b)); st.build(b);
    }
    void dfs1(int x){
        sub[x] = 1; // sub es el tamaño del subarbol
        for(int &y : g[x]){
            par[y] = x; dep[y] = dep[x] + 1;
            g[y].erase(find(all(g[y]), x));
            dfs1(y); sub[x] += sub[y];
            if(sub[y] > sub[g[x][0]]) swap(y, g[x][0]);
        }
    }
    void dfs2(int x){
        pos[x] = t++; ord.pb(x); // pos[x] es la posicion de x en el arreglo del segtree
        for(int y : g[x]){ head[y] = (y == g[x][0] ? head[x] : y); dfs2(y); } // g[x][0] es el hijo pesado de x
    }
    // rangos [l, r) a procesar (hacen parte del camino entre 'x' y 'y'), sin rangos vacíos
    vii path(int x, int y){
        vii r;
        for(; head[x] != head[y]; y = par[head[y]]){
            if(dep[head[x]] > dep[head[y]]) swap(x, y);
            r.pb({pos[head[y]], pos[y] + 1});
        }
        if(dep[x] > dep[y]) swap(x, y);
        if(pos[x] + ve < pos[y] + 1) r.pb({pos[x] + ve, pos[y] + 1});
        return r;
    }
    void updatePath(int x, ll v){ st.update(pos[x], v); }
    ll queryPath(int x, int y){
        ll res = 0; // CHANGEEE: Valor neutro de cual sea la operacion
        for(auto p : path(x, y)) res = max(res, st.calc(p.fi, p.se)); // CHANGEEE segun la operacion
        return res;
    }
};

void solver(){
    int n; cin>>n;
    vector<vi> tree(n+1);
    vi idxEdge(n+1);
    vector<viil> aux(n+1);

    for0(i, n-1){
        int u, v; cin>>u>>v;
        ll w; cin>>w; // Si los pesos estan en las aristas
        tree[u].pb(v); tree[v].pb(u);
        aux[u].pb({{v, i+1}, w}); aux[v].pb({{u, i+1}, w}); // Si los pesos estan en las aristas
    }
    vl val(n+1);

    // Si los pesos estan en las aristas:
    function<void(int,int)> go = [&](int x, int p){ 
        for(auto edj : aux[x]) if(edj.fi.fi != p){ val[edj.fi.fi] = edj.se; idxEdge[edj.fi.se] = edj.fi.fi; go(edj.fi.fi, x); }
    };
    go(1, -1);

    HLD h(tree, val, 1, 1);
    while(1){
        string op; cin>>op;
        if(op == "DONE") return;
        if(op == "CHANGE"){
            int idx; ll v; cin>>idx>>v;
            h.updatePath(idxEdge[idx], v);
        }
        else{
            int u, v; cin>>u>>v;
            cout<<h.queryPath(u, v)<<endl;
        }
    }
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
