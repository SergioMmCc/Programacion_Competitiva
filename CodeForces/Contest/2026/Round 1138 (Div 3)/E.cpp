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
// #include<ext/pb_ds/assoc_container.hpp> // Poner arriba de #define int long long si lo hay
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;
using i128 = __int128;

bool check(ll a, ll x, ll k, ll m){
    ll s = (m - a + x - 1) / x;
    // cout<<"m -> "<<m<<endl;

    k++;
    ll flo = s/k, cntflo = k - (s%k);
    ll cei = (s+k-1)/k, cntcei = s%k;
    if(cntflo > 0 && flo > 43) return 0;
    if(cntcei > 0 && cei > 43) return 0;

    i128 wh = (i128)(((i128)1 << flo) - 1)*(i128)cntflo + (((i128)1 << cei) - 1)*(i128)cntcei;
    // assert(wh >= 0);
    return wh < (i128)m;
}

void solver(){
    ll a, x, k; cin>>a>>x>>k;

    ll lo = 0, hi = 1732261871;
    while(lo < hi){
        ll m = (hi + lo + 1) / 2;
        if(check(a, x, k, m * x + a)) lo = m;
        else hi = m-1;
    }

    cout<<lo * x + a<<endl;
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
