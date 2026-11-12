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

struct node{
    int val; int l, r; // Change
};

const int LEN = 6e6; // tope de nodos totales (usar aprox 4*n + (q+5)*(log(n) + 5))

class segTree {
private:
    node neutro = {0, -1, -1}; // Change

    node calcOp(node a, node b){
        node ans = {a.val + b.val, -1, -1}; // Change
        return ans;
    }

    vector<node> tree;
    int n, idx = 0;

    int update(int prv, int pos, int tl, int tr){
        int v = idx++;
        tree[v] = tree[prv];
        if(tr - tl == 1){
            tree[v].val++; // Change
            return v;
        }
        int tm = (tl + tr) / 2;
        if(pos < tm) tree[v].l = update(tree[v].l, pos, tl, tm);
        else tree[v].r = update(tree[v].r, pos, tm, tr);
        tree[v].val = tree[tree[v].l].val + tree[tree[v].r].val;
        return v;
    }

    // [l, r)
    int calc(int v, int l, int r, int tl, int tr){ // Change si walking on segment tree
        if(tl >= r || l >= tr) return 0;
        if(tl >= l && tr <= r) return tree[v].val; // si walking -> tr - tl == 1

        int tm = (tl + tr) / 2;
        return calc(tree[v].l, l, r, tl, tm) + calc(tree[v].r, l, r, tm, tr);
    }

    int build(int tl, int tr, vi& a){
        int v = idx++;
        if(tr - tl == 1){
            if(tl < sz(a)) tree[v] = {a[tl], -1, -1}; // Change
            return v;
        }
        int tm = (tl + tr) / 2;
        int l = build(tl, tm, a), r = build(tm, tr, a);
        tree[v] = {tree[l].val + tree[r].val, l, r};
        return v;
    }

public:
    vi roots; // roots[i] = índice de la raíz de la versión i

    void init(int n_){
        n = n_;
        idx = 0;
        tree.assign(LEN, neutro); // Cuidado si se debe inicializar en 0 o similar
        roots.clear();
    }

    // Crea una nueva version a partir de "ver" (indice en roots)
    void update(int ver, int pos){
        roots.pb(update(roots[ver], pos, 0, n));
    }

    // Calculo sobre la version "ver"
    int calc(int ver, int l, int r){
        return calc(roots[ver], l, r, 0, n);
    }

    // Crea la version 0 a partir del arreglo inicial
    void build(vi& a){
        roots.pb(build(0, sz(a), a));
    }
};

void solver(){
    int n; cin>>n;
    vii a(n);
    for0(i,n) cin>>a[i].fi>>a[i].se;
    sort(all(a));

    vi cero(n);
    segTree st; st.init(n); st.build(cero);
    map<ll, int> ver;
    vl vals;
    
    for0(i,n){
        if(i == n-1 || a[i].fi != a[i+1].fi){
            ver[a[i].fi] = i+1;
        }
        vals.pb(a[i].se - a[i].fi);
    }
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    for0(i,n){
        int aux = lb(all(vals), a[i].se - a[i].fi) - vals.begin();
        st.update(i, aux);
    }

    int q; cin>>q;
    while(q--){
        int cnt; ll h; cin>>cnt>>h;
        ll lo = 1, hi = 1000000010000000000;
        while(lo < hi){
            ll m = (lo + hi) / 2;

            bool cond = 0;
            auto version = ver.ub(m);
            if(version != ver.begin()){
                --version;
                int use = version->se;
                int index = lb(all(vals), h-m) - vals.begin();
                if(index < n && st.calc(use, index, n) >= cnt) cond = 1;
            }

            if(cond) hi = m;
            else lo = m+1;
        }

        cout<<lo<<endl;
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
