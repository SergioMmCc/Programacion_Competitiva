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

vl fact(2e5 + 1);
void calc(){
    fact[0] = 1;
    for1(i,2e5) fact[i] = ((ll)i * fact[i-1]) % mod;
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

void solver(){
    int n; cin>>n;
    vl a(n+1);
    for1(i,n) cin>>a[i];
    if(n == 1){
        cout<<0<<endl;
        return;
    }
    sort(all(a));
    ll take = 0;
    for0(i,n) take = (take + a[i]) % mod;
    take = (take * fact[n-1]) % mod;

    ll ans = 0;
    ll sum = 0;
    forlr(i,2,n){
        sum = (sum + (fact[n-1] * mod_inverse(n - i + 1) % mod)) % mod;
        ans = (ans + ((a[i] % mod) * sum % mod)) % mod;
    }

    cout<<(ans - take + mod) % mod<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calc();
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
