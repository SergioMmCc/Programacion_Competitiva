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

struct node{ // Change
    ll val, l, r;
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

    // Crea la version 0 a partir del arreglo inicial
    void build(vl& a){
        roots.pb(build(0, sz(a), a));
    }
};

void solver(){
    int n, q; cin>>n>>q;
    vl a(n);
    for0(i,n) cin>>a[i];

    segTree st; st.init(n); st.build(a);

    map<int, int> versions = {{1, 0}};
    int idx = 2;

    while(q--){
        int op; cin>>op;
        if(op == 1){
            int ver, idx; ll val; cin>>ver>>idx>>val; idx--;
            st.update(versions[ver], idx, val);
            versions[ver] = sz(st.roots) - 1;
        }
        else if(op == 2){
            int ver, l, r; cin>>ver>>l>>r; l--;
            cout<<st.calc(versions[ver], l, r).val<<endl;
        }
        else{
            int ver; cin>>ver;
            versions[idx] = sz(st.roots);
            idx++;
            st.roots.pb(st.roots[versions[ver]]);
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
