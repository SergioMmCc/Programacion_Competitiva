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
typedef pair<pii, int> piii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<piii> viii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

struct node{ // Change
    ll val;
};

class segTree {
private:
    int size;
    vector<node> tree;
    node neutro = {LLONG_MAX - 1}; // Change

    node calcOp(node a, node b){ // Change
        if(a.val == neutro.val) return b;
        if(b.val == neutro.val) return a;
        node ans;
        ans.val = max(a.val, b.val);
        return ans;
    }

    void update(int pos, ll val, int v, int tl, int tr){
        if(tr - tl == 1){
            tree[v] = {val}; // Change
            return;
        }
        
        int tm = (tl + tr) / 2;
        if(pos < tm) update(pos, val, 2*v + 1, tl, tm);
        else update(pos, val, 2*v + 2, tm, tr);
        tree[v] = calcOp(tree[2*v + 1], tree[2*v + 2]);
    }

    // [l, r)
    node calc(int l, int r, int v, int tl, int tr){ // Change si walking on segment tree
        if(tl >= r || l >= tr) return neutro;
        if(tl >= l && tr <= r) return tree[v]; // si walking on seg tree -> tr - tl == 1

        int tm = (tl + tr) / 2;
        node m1 = calc(l, r, 2*v + 1, tl, tm);
        node m2 = calc(l, r, 2*v + 2, tm, tr);
        return calcOp(m1, m2);
    }

    void build(vl& a, int v, int tl, int tr){
        if(tr - tl == 1){
           if(tl < sz(a)) tree[v] = {a[tl]}; // Change
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
        tree.assign(2*size, {0LL});
    }
    void update(int pos, ll val){update(pos, val, 0, 0, size);}
    node calc(int l, int r){return calc(l, r, 0, 0, size);}
    void build(vector<ll>& a){build(a, 0, 0, size);}
};

const int maxn = 1e5 + 1;
int n;
vector<vi> tree(maxn);
vi pa(maxn), depth(maxn), val(maxn), ans(maxn);

void DFS(int u){
    for(int v : tree[u]){
        depth[v] = depth[u] + 1;
        DFS(v);
    }
}

segTree st;
void DFS2(int u){

    // cout<<"u -> "<<u<<" val -> "<<val[u]<<endl;
    // for1(i,n) cout<<"\ti -> "<<i<<" val -> "<<st.calc(i, i+1).val<<endl;

    int c1 = st.calc(0, val[u]).val + 1;
    st.update(val[u], c1);
    int c2 = st.calc(0, n+1).val;
    ans[u] = max(c1, c2);
    for(int v : tree[u]){
        DFS2(v);
    }

    st.update(val[u], 0);
}

void solver(){
    cin>>n;
    forlr(i,2,n){
        cin>>pa[i];
        tree[pa[i]].pb(i);
    }

    DFS(1);
    viii ord;
    for1(i,n){
        cin>>val[i];
        ord.pb({{val[i], n - depth[i]}, i});
    }
    sort(all(ord));
    for0(i,n) val[ord[i].se] = i+1;
    // for1(i,n) cout<<val[i]<<' '; cout<<endl;

    st.init(n+1);

    DFS2(1);
    forlr(i, 2, n) cout<<ans[i]<<' ';
    cout<<endl;
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
