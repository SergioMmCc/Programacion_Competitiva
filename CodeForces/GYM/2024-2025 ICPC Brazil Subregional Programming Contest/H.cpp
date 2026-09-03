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

ll binpow(ll b, ll e, ll mod){
    b %= mod;
    ll ans = 1;
    while(e){
        if(e & 1) ans = (ans * b) % mod;
        b = (b * b) % mod;
        e >>= 1;
    }
    return ans;
}

void solver(){
    string a, b; cin>>a>>b;
    vi ba, bb;
    ll mod = 0;
    for0(i,sz(a)) if(a[i] == '*') ba.pb(sz(a)-i-1);
    for0(i,sz(b)) if(b[i] == '*') bb.pb(sz(b)-i-1);
    for0(i,sz(b)) if(b[i] == '1') mod += (1 << (sz(b)-i-1));

    int n = sz(ba) + sz(bb);
    for(int mask = 0; mask < (1<<n); mask++){
        ll aux = mod;
        for0(i,sz(bb)) if(mask & (1 << i)) aux += (1 << bb[i]);
        ll num = 0;
        for0(i,sz(a)) if(a[i] == '1') num = (num + binpow(2, sz(a)-i-1, aux)) % aux;
        // cout<<"num -> "<<num<<endl;

        for0(i,sz(ba)) if(mask & (1 << (sz(bb) + i))) num = (num + binpow(2, ba[i], aux)) % aux;
        // cout<<"mask -> "<<mask<<" num -> "<<num<<" aux -> "<<aux<<endl;

        if(!num){
            string ans = "";
            for0(i,sz(a)) ans += '0';
            for0(i,sz(a)) if(a[i] == '1') ans[i] = '1';
            for0(i,sz(ba)){
                if(mask & (1 << (sz(bb) + i))){
                    ans[sz(a) - ba[i] - 1] = '1';
                    // cout<<"ba -> "<<ba[i]<<endl;
                }
            }
            cout<<ans<<endl;
            return;
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
