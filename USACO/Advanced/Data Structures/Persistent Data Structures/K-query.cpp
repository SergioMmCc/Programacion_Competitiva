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
    ll val; int l, r; // Change
};

const int LEN = 1e7; // tope de nodos totales (usar aprox 4*n + (q+5)*(log(n) + 5))

class segTree {
private:
    node neutro = {LLONG_MAX - 1, -1, -1}; // Change

    node calcOp(node a, node b){ // Change
        if(a.val == neutro.val) return b;
        if(b.val == neutro.val) return a;
        node ans = {a.val + b.val, -1, -1}; // Change
        return ans;
    }

    node calcDifBetween(node v1, node v2){
        if(v1.val == neutro.val) return neutro;
        return {v2.val - v1.val, -1, -1}; // Change
    }

    node calcSolapeBetween(node a, node b){
        if(a.val == neutro.val) return b;
        if(b.val == neutro.val) return a;
        return {a.val + b.val, -1, -1};  // Change
    }

    vector<node> tree;
    int n, idx = 0;

    int update(int prv, int pos, ll val, int tl, int tr){
        int v = idx++;
        tree[v] = tree[prv];
        if(tr - tl == 1){
            tree[v].val = val; // Change
            return v;
        }
        int tm = (tl + tr) / 2;
        if(pos < tm) tree[v].l = update(tree[v].l, pos, val, tl, tm);
        else tree[v].r = update(tree[v].r, pos, val, tm, tr);
        node combined = calcOp(tree[tree[v].l], tree[tree[v].r]);
        tree[v].val = combined.val;
        return v;
    }

    // [l, r)
    node calc(int v, int l, int r, int tl, int tr){ // Change si walking on segment tree
        if(tl >= r || l >= tr) return neutro;
        if(tl >= l && tr <= r) return tree[v]; // si walking -> tr - tl == 1

        int tm = (tl + tr) / 2;
        node m1 = calc(tree[v].l, l, r, tl, tm);
        node m2 = calc(tree[v].r, l, r, tm, tr);
        return calcOp(m1, m2);
    }

    // [l, r) y [v1, v2]
    node calcBetween(int v1, int v2, int l, int r, int tl, int tr){
        if(tl >= r || l >= tr) return neutro; // sin overlap con [lo, hi] de VALORES
        if(tl >= l && tr <= r) return calcDifBetween(tree[v1], tree[v2]);
        int tm = (tl + tr) / 2;
        node lc = calcBetween(tree[v1].l, tree[v2].l, l, r, tl, tm);
        node rc = calcBetween(tree[v1].r, tree[v2].r, l, r, tm, tr);
        return calcSolapeBetween(lc, rc);
    }

    int build(int tl, int tr, vl& a){
        int v = idx++;
        if(tr - tl == 1){
            if(tl < sz(a)) tree[v] = {a[tl], -1, -1}; // Change
            return v;
        }
        int tm = (tl + tr) / 2;
        int l = build(tl, tm, a), r = build(tm, tr, a);
        node combined = calcOp(tree[l], tree[r]);
        tree[v] = {combined.val, l, r};
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
    void update(int ver, int pos, ll val){
        roots.pb(update(roots[ver], pos, val, 0, n));
    }

    // Calculo sobre la version "ver"
    node calc(int ver, int l, int r){
        return calc(roots[ver], l, r, 0, n);
    }

    // Para hacer calculos entre versiones
    node calcBetween(int v1, int v2, int l, int r){
        return calcBetween(roots[v1], roots[v2], l, r, 0, n);
    }

    // Crea la version 0 a partir del arreglo inicial
    void build(vl& a){
        roots.pb(build(0, sz(a), a));
    }
};

void solver(){
    int n; cin>>n;
    vl a(n);
    segTree st; st.init(n);
    st.build(a);
    for0(i,n) cin>>a[i];
    
    // Comprimir
    vl comp = a;
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    for0(i,sz(a)) a[i] = lb(all(comp), a[i]) - comp.begin();

    vi cnt(n);
    for0(i,n){
        cnt[a[i]]++;
        st.update(sz(st.roots) - 1, a[i], cnt[a[i]]);
    }

    int q; cin>>q;
    while(q--){
        int v1, v2, k; cin>>v1>>v2>>k;
        v1--;
        k = ub(all(comp), k) - comp.begin();

        ll ans = st.calcBetween(v1, v2, k, n).val;
        if(ans == LLONG_MAX - 1) cout<<0<<endl;
        else cout<<ans<<endl;
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
