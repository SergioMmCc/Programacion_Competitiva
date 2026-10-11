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
typedef pair<ld, int> pdi;
typedef pair<pdi, pii> pdiii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pdiii> vdiii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void solver(){
    int n, p; cin>>n>>p;
    vdiii a(n);
    for0(i,n){
        cin>>a[i].fi.se>>a[i].se.fi>>a[i].se.se;
        ld aux = (ld)((ld)a[i].fi.se - 1.0) / (ld)a[i].se.fi;
        a[i].fi.fi = aux;
    }

    sort(all(a));
    // reverse(all(a));

    vector<vi> dp(n, vi(p+1));
    int ans = 0;

    for0(i,n){
        forn1(j,p){
            if(i) dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if(j < a[i].se.fi) continue;
            int aux = (j - a[i].se.fi) / a[i].fi.se;
            dp[i][aux] = max(dp[i][aux], (i ? dp[i-1][j] : 0) + a[i].se.se);
        }
    }

    for0(i,n){
        for0(j,p+1){
            ans = max(ans, dp[i][j]);
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
