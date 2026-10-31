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

class segTree {
private:
    int size;
    vii lazy;
    vii tree;

    pii neutro = {INT_MAX - 1, INT_MIN + 1};

    pii updateOp(pii a, pii b, int len){
        if(b.fi == neutro.fi) return a;
        if(a.fi == neutro.fi) return b;
        return {a.fi + b.fi, a.se + b.se};
    }
    pii calcOp(pii a, pii b){
        if(a.fi == neutro.fi) return b;
        if(b.fi == neutro.fi) return a;
        return {min(a.fi, b.fi), max(a.se, b.se)};
    }

    void applyUpdOp(pii &a, pii b, int len){
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
    void update(int l, int r, int val, int v, int tl, int tr){
        propagate(v, tl, tr);
        if(tl >= r || l >= tr) return;
        if(tl >= l && tr <= r){
            applyUpdOp(lazy[v], {val, val}, 1);
            applyUpdOp(tree[v], {val, val}, tr - tl);
            return;
        }
        
        int tm = (tl + tr) / 2;
        update(l, r, val, 2*v + 1, tl, tm);
        update(l, r, val, 2*v + 2, tm, tr);
        tree[v] = calcOp(tree[2*v + 1], tree[2*v + 2]);
    }

    // [l, r)
    pii calc(int l, int r, int v, int tl, int tr){
        propagate(v, tl, tr);
        if(tl >= r || l >= tr) return neutro;
        if(tl >= l && tr <= r) return {tree[v]};

        int tm = (tl + tr) / 2;
        pii m1 = calc(l, r, 2*v + 1, tl, tm);
        pii m2 = calc(l, r, 2*v + 2, tm, tr);
        return calcOp(m1, m2);
    }

    void build(vi& a, int v, int tl, int tr){ 
        if(tr == tl + 1){
            if(tl < sz(a)) tree[v] = {a[tl], a[tl]};
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
        tree.assign(2*size, neutro); // Change
    }
    void update(int l, int r, int val){update(l, r, val, 0, 0, size);}
    pii calc(int l, int r){return calc(l, r, 0, 0, size);}
    void build(vi& a){build(a, 0, 0, size);}
};

void solver(){
    int n; cin>>n;
    vi a(n), inv(n);
    for0(i,n){
        int num; cin>>num; num--;
        a[i] = num; inv[num] = i;
    }

    vi ps(n), ss(n);
    for0(i,n){
        if(!a[i]) ps[i] = -1;
        else ps[i] = 1;
        if(i) ps[i] += ps[i-1];
    }
    forn0(i,n){
        if(!a[i]) ss[i] = -1;
        else ss[i] = 1;
        if(i < n-1) ss[i] += ss[i+1];
    }

    segTree suf, pre; suf.init(n); pre.init(n); suf.build(ss); pre.build(ps);

    vb ans(n);
    for1(i,n-2){
        int idx = inv[i];

        int vals = suf.calc(idx,idx+1).fi, valp = pre.calc(idx, idx+1).fi;
        if(!idx){
            pii aux = pre.calc(idx+1, n);
            int mini = aux.fi - valp, maxi = aux.se - valp;
            if(maxi >= 0 && mini <= 0) ans[idx] = 1;
        }
        else if(idx == n-1){
            pii aux = suf.calc(0,idx);
            int mini = aux.fi - vals, maxi = aux.se - vals;
            if(maxi >= 0 && mini <= 0) ans[idx] = 1;
        }
        else{
            pii auxs = suf.calc(0,idx);
            int mins = auxs.fi - vals, maxs = auxs.se - vals;
            pii auxp = pre.calc(idx+1, n);
            int minp = auxp.fi - valp, maxp = auxp.se - valp;

            if((maxs >= 0 && mins <= 0) || (maxp >= 0 && minp <= 0)) ans[idx] = 1;
            else{
                if(mins + minp <= 0 && maxs + maxp >= 0) ans[idx] = 1;
            }
        }   

        suf.update(0, idx+1, -2);
        pre.update(idx, n, -2);
    }

    for0(i,n){
        if(i) cout<<' ';
        cout<<(ans[i] ? "YES" : "NO");
    }
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
