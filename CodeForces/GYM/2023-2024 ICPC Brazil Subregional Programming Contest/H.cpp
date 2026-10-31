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
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

struct segTree{
    int n; ll neutro = -LLONG_MIN + 1; // CHANGE neutro
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

void solver(){
    int n; ll s; cin>>n>>s;
    vector<piil> a(n);
    vi aux(1);
    for0(i,n){
        cin>>a[i].fi.fi>>a[i].fi.se>>a[i].se;
        aux.pb(a[i].fi.fi);
        aux.pb(a[i].fi.se);
    }
    sort(all(a));

    sort(all(aux));
    aux.erase(unique(all(aux)), aux.end());
    for0(i,n){
        a[i].fi.fi = lb(all(aux), a[i].fi.fi) - aux.begin();
        a[i].fi.se = lb(all(aux), a[i].fi.se) - aux.begin();
    }

    vl auxl(sz(aux)), auxr(sz(aux), -10000000000000000);
    segTree stl, str; stl.init(sz(aux)); str.init(sz(aux)); stl.build(auxl); str.build(auxr);
    vl dp(n);
    ll ans = 0;
    for0(j,n){
        int l = a[j].fi.fi, r = a[j].fi.se;
        ll lr = aux[l], rr = aux[r];
        // cout<<"l -> "<<l<<" lr -> "<<lr<<" r -> "<<r<<" rr -> "<<rr;
        ll le = stl.calc(0, l), re = str.calc(l, r+1);
        dp[j] = -a[j].se + max(s*(ll)(rr - lr + 1) + le, s*rr + re);
        // cout<<" dp -> "<<dp[j]<<endl;
        ans = max(ans, dp[j]);
        if(auxl[r] < dp[j]){
            auxl[r] = dp[j];
            stl.update(r, dp[j]);
        }
        if(auxr[r] < dp[j] - s*rr){
            auxr[r] = dp[j] - s*rr;
            str.update(r, auxr[r]);
        }
    }

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
