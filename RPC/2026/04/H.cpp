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
typedef int ll;
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

class segTree {
private:
    int size;
    vl lazy;
    vl tree;

    ll neutro = INF - 1;

    // Para query suma y update assign
    ll updateOp(ll a, ll b, ll len){
        if(b == neutro) return a;
        return b * len;
    }
    ll calcOp(ll a, ll b){
        if(a == neutro) return b;
        if(b == neutro) return a;
        return a + b;
    }

    void applyUpdOp(ll &a, ll b, ll len){
        a = updateOp(a, b, len);
    }

    void propagate(int v, int tl, int tr){
        if(tr - tl == 1) return;
        int tm = (tr + tl) / 2;
        applyUpdOp(lazy[2*v + 1], lazy[v], 1);
        applyUpdOp(tree[2*v + 1], lazy[v], tm - tl);
        applyUpdOp(lazy[2*v + 2], lazy[v], 1);
        applyUpdOp(tree[2*v + 2], lazy[v], tr - tm);
        lazy[v] = neutro;
    }

    // [l, r)
    void update(int l, int r, ll val, int v, int tl, int tr){
        propagate(v, tl, tr);
        if(tl >= r || l >= tr) return;
        if(tl >= l && tr <= r){
            applyUpdOp(lazy[v], val, 1);
            applyUpdOp(tree[v], val, tr - tl);
            return;
        }
        
        int tm = (tl + tr) / 2;
        update(l, r, val, 2*v + 1, tl, tm);
        update(l, r, val, 2*v + 2, tm, tr);
        tree[v] = calcOp(tree[2*v + 1], tree[2*v + 2]);
    }

    // [l, r)
    ll calc(int l, int r, int v, int tl, int tr){
        propagate(v, tl, tr);
        if(tl >= r || l >= tr) return neutro;
        if(tl >= l && tr <= r) return tree[v];

        int tm = (tl + tr) / 2;
        ll m1 = calc(l, r, 2*v + 1, tl, tm);
        ll m2 = calc(l, r, 2*v + 2, tm, tr);
        return calcOp(m1, m2);
    }

    void build(vl& a, int v, int tl, int tr){ 
        if(tr == tl + 1){
            if(tl < sz(a)) tree[v] = a[tl];
            return;
        }
        int tm = (tr + tl) / 2;
        build(a, 2*v + 1, tl, tm);
        build(a, 2*v + 2, tm, tr);
        tree[v] = calcOp(tree[2*v + 1], tree[2*v + 2]);
    }

public:
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        lazy.assign(2*size, neutro);
        tree.assign(2*size, 0LL); // Change
    }
    void update(int l, int r, ll val){update(l, r, val, 0, 0, size);}
    ll calc(int l, int r){return calc(l, r, 0, 0, size);}
    void build(vl& a){build(a, 0, 0, size);}
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
            auto it = find(all(g[y]), x); if(it != g[y].end()) g[y].erase(it);
            dfs1(y); sub[x] += sub[y];
            if(sub[y] > sub[g[x][0]]) swap(y, g[x][0]);
        }
    }
    void dfs2(int x){
        pos[x] = t++; ord.pb(x); // pos[x] es la POSICION de x en el arreglo del segtree
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
    void updatePath(int x, int y, ll v){ for(auto p : path(x, y)) st.update(p.fi, p.se, v); }
    ll queryPath(int x){
        return st.calc(pos[x], pos[x] + 1);
    }
};

const int maxn = 5e5 + 1;
typedef pair<ll, int> pli;
vector<vector<pli>> graph(maxn);

void prim(int s, int n, vl& dis, vi& pa){
    vb inQueue(n+1, 1); 
    dis[s] = 0;
    pqueue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, s});
    while(!pq.empty()){
        int u = pq.top().se;
        pq.pop();
        if(!inQueue[u]) continue;
        inQueue[u] = 0;
        for(pli &edge : graph[u]){
            int v = edge.se; ll w = edge.fi;
            if(inQueue[v] && dis[v] > w){
                dis[v] = w;
                pa[v] = u;
                pq.push({dis[v], v});
            }
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    int ans = m - n + 1;
    set<pair<ll, pii>, greater<pair<ll, pii>>> edj;
    for0(i,m){
        int u, v; ll w; cin>>u>>v>>w;
        if(u > v) swap(u, v);
        graph[u].pb({w, v});
        graph[v].pb({w, u});
        edj.insert({w, {u, v}});
    }

    vl dis(n+1, INF); // Distancia de cada nodo a su padre en el MST
    vi pa(n+1, -1); // Padre de cada nodo en el MST

    // Calcular
    prim(1, n, dis, pa);

    vector<vi> tree(n+1);
    forlr(i,2,n){
        tree[pa[i]].pb(i);
        edj.erase({dis[i], {min(i, pa[i]), max(i, pa[i])}});
    }
    
    vl a(n+1, INF);
    HLD h(tree, a, 1, 1);
    for(auto& e : edj){
        int u = e.se.fi, v = e.se.se; ll w = e.fi;
        h.updatePath(u, v, w);
    }

    forlr(i,2,n) if(dis[i] >= h.queryPath(i)) ans++;

    cout<<ans<<endl;
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
