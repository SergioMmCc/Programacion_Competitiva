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

struct rmq {
    ll neutro = LLONG_MAX - 1; // Change
    int n, lgn;
    vector<vl> st;
    inline ll oper(ll a, ll b){ return __gcd(a,b); } // Change

    void build(const vl& a){
        n = sz(a);
        lgn = 32 - __builtin_clz(n); // floor(log2(n))
        st.assign(lgn, vl(n));
        st[0] = a;
        for1(j,lgn) 
            for(int i = 0; i + (1 << j) - 1 < n; i++) 
                st[j][i] = oper(st[j-1][i], st[j-1][i + (1 << (j-1))]);
    }

    ll calc(int l, int r){ // [l, r]
        if(l > r) return neutro;
        int j = 31 - __builtin_clz(r-l+1); // floor(log2(r-l+1))
        return oper(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

void solver(){
    int n; cin>>n;
    vl a(n);
    for0(i,n) cin>>a[i];

    rmq st; st.build(a);

    ll ans = st.calc(0, n-1);
    forlr(i, 1, n-2){
        ans += min(st.calc(0, i), st.calc(i, n-1));
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
