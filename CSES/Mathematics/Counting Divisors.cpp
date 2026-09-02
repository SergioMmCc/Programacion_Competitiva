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

using i128 = __int128_t;
using u64 = uint64_t;
using u128 = __uint128_t;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 binpow(u64 b, u64 e, u64 m){
    b %= m;
    u64 ans = 1;
    while(e){
        if(e & 1) ans = ((u128)b * ans) % m;
        b = ((u128)b * b) % m;
        e >>= 1;
    }
    return ans;
}

bool check_composite(u64 n, u64 a, u64 d, int s){
    u64 x = binpow(a, d, n);
    if(x == 1 || x == n - 1) return 0;
    for1(r,s-1){
        x = ((u128)x * x) % n;
        if(x == n - 1) return 0;
    }
    return 1;
};

// Version optimizada
bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if(n < 2) return 0;

    // Testear con los primeros primos para optimizar ya que el 88% de numeros son divisibles por al menos uno. 
    // Agregar mas no optimiza casi nada.
    for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}){
        if(n == (u64)a) return 1;
        if(!(n % a)) return 0;
    }
    for(u64 a : {193, 407521, 299210837}) if(n == a) return 1; // Primos especiales que se testean aparte

    int r = 0;
    u64 d = n - 1;
    while((d & 1) == 0){
        d >>= 1;
        r++;
    }

    for(u64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
        if(check_composite(n, a, d, r)) return 0;
    }
    return 1;
}

ll mult(ll a, ll b, ll mod){ return ((i128)a * b) % mod; }
ll f(ll x, ll c, ll mod){ return (mult(x, x, mod) + c) % mod; }

ll rho(ll n){
    ll x = rng() % n;
    ll c = (rng() % (n-1)) + 1;
    ll g = 1;
    ll q = 1;
    ll xs, y;

    int m = 128;
    int l = 1;
    while(g == 1){
        y = x;
        for(int i = 1; i < l; i++) x = f(x, c, n);
        int k = 0;
        while(k < l && g == 1){
            xs = x;
            for(int i = 0; i < m && i < l - k; i++){
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if(g == n){
        do{
            xs = f(xs, c, n);
            g = gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g == n ? rho(n) : g;
}

void factorize(ll n, map<ll, int>& fact){
    if(n == 1) return;
    if(MillerRabin(n)){ // Primero testear si es primo
        fact[n]++;
        return;
    }
    ll g = rho(n);
    factorize(g, fact); factorize(n/g, fact);
}

void solver(){
    ll n; cin>>n;
    if(n == 1){
        cout<<1<<endl;
        return;
    }

    map<ll, int> fact;
    factorize(n, fact);
    int ans = 1;
    for(const auto& par : fact){
        ans *= par.se + 1;
    }

    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}