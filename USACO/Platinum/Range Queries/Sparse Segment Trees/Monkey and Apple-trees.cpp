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

const int SZ = 1 << 30; // Techo del log2 del maximo indice
const int neutro = 0; // Change
const int LEN = 1e7; // tope de nodos totales (usar aprox lg(SZ) * q * 2)

struct node {
    int val = neutro, lazy = neutro;
    int c[2] = {-1, -1};
};

class segTree {
private:
    vector<node> tree;
    int idx = 0;
    int root;

    // Para query suma y update assign
    int updateOp(int a, int b, int len){
        if(b == neutro) return a;
        return b * len;
    }
    int calcOp(int a, int b){
        if(a == neutro) return b;
        if(b == neutro) return a;
        return a + b; // Change
    }
    void applyUpdOp(int &a, int b, int len){
        a = updateOp(a, b, len);
    }

    int newNode(){
        tree[idx] = node();
        return idx++;
    }

    void propagate(int v, int tl, int tr){
        if(tr - tl == 1) return;
        int tm = (tl + tr) / 2;
        if(tree[v].c[0] == -1) tree[v].c[0] = newNode();
        if(tree[v].c[1] == -1) tree[v].c[1] = newNode();

        int L = tree[v].c[0], R = tree[v].c[1];
        applyUpdOp(tree[L].lazy, tree[v].lazy, 1);
        applyUpdOp(tree[L].val, tree[v].lazy, tm - tl);
        applyUpdOp(tree[R].lazy, tree[v].lazy, 1);
        applyUpdOp(tree[R].val, tree[v].lazy, tr - tm);
        tree[v].lazy = neutro;
    }

    // [l, r)
    void update(int v, int l, int r, int val, int tl, int tr){
        if(r <= tl || tr <= l) return;
        if(l <= tl && tr <= r){
            applyUpdOp(tree[v].lazy, val, 1);
            applyUpdOp(tree[v].val, val, tr - tl);
            return;
        }
        propagate(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(tree[v].c[0], l, r, val, tl, tm);
        update(tree[v].c[1], l, r, val, tm, tr);
        tree[v].val = calcOp(tree[tree[v].c[0]].val, tree[tree[v].c[1]].val);
    }

    // [l, r)
    int calc(int v, int l, int r, int tl, int tr){
        if(r <= tl || tr <= l) return neutro;
        if(l <= tl && tr <= r) return tree[v].val;
        propagate(v, tl, tr);
        int tm = (tl + tr) / 2;
        int lv = tree[v].c[0] != -1 ? calc(tree[v].c[0], l, r, tl, tm) : neutro;
        int rv = tree[v].c[1] != -1 ? calc(tree[v].c[1], l, r, tm, tr) : neutro;
        return calcOp(lv, rv);
    }

public:
    void init(){
        tree.assign(LEN, node());
        idx = 0;
        root = newNode();
    }
    void update(int l, int r, int val){ update(root, l, r, val, 0, SZ); }
    int calc(int l, int r){ return calc(root, l, r, 0, SZ); }
};

void solver(){
    int q; cin>>q;
    int c = 0;
    segTree st; st.init(); 
    while(q--){
        int op, l, r; cin>>op>>l>>r; l += c; r += c;
        if(op == 1){
            c = st.calc(l, r+1);
            cout<<c<<endl;
        }
        else{
            st.update(l, r+1, 1);
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
