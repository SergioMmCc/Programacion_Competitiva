#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forn0(i,n) for(int i = (int)n-1; i >= 0; i--)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define pb push_back
#define sz(a) (int)a.size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;

const ll mod = 1e9 + 7;


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
    return v;
}

vl fact(1e6 + 1);
void calc(){
    fact[0] = 1;
    for1(i, 1e6) fact[i] = (fact[i-1] * (ll)i) % mod;
}

ll binom(int n, int k){
    if(k > n) return 0;
    return fact[n] * mod_inverse(fact[k] * fact[n-k] % mod) % mod;
}

void solver(int n, int k){
    vi a(n+1);
    for1(i,n){
        cin>>a[i];
        a[i] += 1e9 + 1;
    }
    sort(a.begin(), a.end());
    int med = a[(n+1) / 2];

    ll p = 0;
    for1(i, n){
        if(a[i] != med) continue;
        ll c1 = binom(i-1, k/2) * binom(n-i, k/2) % mod;
        p += c1;
        p %= mod;
    }

    ll q = binom(n, k);
    ll gc = __gcd(p, q);
    p /= gc; q /= gc;

    cout<<p * mod_inverse(q) % mod<<endl;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    calc();

    int n, k;
    while(cin>>n>>k){
        if(!n) break;
        solver(n, k);
    }

    return 0;
}