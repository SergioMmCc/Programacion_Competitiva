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
const ll mod = 998244353;

vl fact(12005);
void calcFact(){
    fact[0] = 1;
    for1(i,12004) fact[i] = (fact[i-1] * (ll)i) % mod;
}

ll mod_inverse(ll a){
    ll i = mod, v = 0, d = 1;
    while(a > 0){
        ll t = i/a, x = a;
        a = i%x;
        i = x;
        x = d;
        d = v - t*x;
        v = x;
    }
    v %= mod;
    if(v < 0) v += mod;
    return v; // (a * v) % mod = 1
}

ll calc(int a, int b){
    vl last(a, 1);
    for1(j,b){
        vl dp(a);
        for0(i,a){
            if(i) dp[i] = (dp[i] + dp[i-1]) % mod;
            if(i < a-1) dp[i] = (dp[i] + last[i+1]) % mod;
        }

        swap(dp, last);
    }

    return last[a-1];
}

ll binom(ll a, ll b){
    return fact[a] * mod_inverse(fact[b] * fact[a - b] % mod) % mod;
}

void solver(){
    int d, r, u, l; cin>>d>>r>>u>>l;

    int a = d - 1 + 2*u, b = r - 1 + 2*l;

    ll s1 = calc(d, u), s2 = calc(r, l);
    ll ans = (((s1 * s2) % mod) * ((binom(b + a - 1, b) + binom(b + a - 1, a)) % mod)) % mod;
    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calcFact();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
