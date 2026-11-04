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
typedef pair<pii, pii> piiii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<piiii> viiii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void solver(){
    int n; cin>>n;
    viiii ev;
    for0(i,n){
        int k; cin>>k;
        for0(j,k){
            int l, r, val; cin>>l>>r>>val;
            ev.pb({{l, r}, {val, i}});
        }
    }

    sort(all(ev));

    int lim = 1 << n;
    vector<vi> dp(lim, vi(86401));
    for1(mask, lim-1){
        int idx = 0;
        for1(j,86400){ 
            dp[mask][j] = max(dp[mask][j], dp[mask][j-1]);

            while(idx < sz(ev) && ev[idx].fi.fi <= j){
                int r = ev[idx].fi.se, val = ev[idx].se.fi;
                if((mask & (1 << ev[idx].se.se))){
                    if(dp[mask][j]) dp[mask][r] = max(dp[mask][r], dp[mask][j] + val);
                    if(dp[mask ^ (1 << ev[idx].se.se)][j] || __builtin_popcount(mask) == 1) dp[mask][r] = max(dp[mask][r], dp[mask ^ (1 << ev[idx].se.se)][j] + val);
                }
                idx++;
            }

            // cout<<"mask -> "<<mask<<" j -> "<<j<<" dp -> "<<dp[mask][j]<<endl;
        }
    }

    cout<<(dp[lim-1][86400] <= 0 ? -1 : dp[lim-1][86400])<<endl;

    // cout<<"ARREGLAR TIEMPO"<<endl;
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
