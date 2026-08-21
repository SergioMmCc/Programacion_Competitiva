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
const int mod = 998244353;

void solver(){
    int n; cin>>n;
    int r = 451;
    vi a(n);
    for0(i,n) cin>>a[i];

    vi dp(n); dp[0] = 1;
    vector<vi> ps(r, vi(r));

    if(a[0] >= r) for(int j = a[0]; j < n; j += a[0]) dp[j] = 1;
    else ps[a[0]][0] = 1;

    int ans = 1;
    for1(i,n-1){
        for1(j,r-1){
            dp[i] = (dp[i] + ps[j][i%j]) % mod;
        }
        ans = (ans + dp[i]) % mod;

        if(a[i] >= r) for(int j = i + a[i]; j < n; j += a[i]) dp[j] = (dp[j] + dp[i]) % mod;
        else ps[a[i]][i % a[i]] = (ps[a[i]][i % a[i]] + dp[i]) % mod;
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
