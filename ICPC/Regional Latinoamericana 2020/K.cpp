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
const ll mod = 1e9 + 7;

void solver(){
    int k; ll l; cin>>k>>l;

    vector<vl> cost(k, vl(k));
    for0(i,k){
        for0(j,k){
            cin>>cost[i][j];
        }
    }

    int n; cin>>n;
    vl a(n);
    for1(i,n-1) cin>>a[i];

    vl dp(k, 1);
    for1(i,n-1){
        vl aux(k, 0);
        for0(j,k){
            auto itl = lb(all(cost[j]), a[i] - l);
            auto itr = ub(all(cost[j]), a[i] + l);

            if(itl != cost[j].end()){
                int idx = distance(cost[j].begin(), itl);
                aux[idx] = (aux[idx] + dp[j]) % mod;
            }
            if(itr != cost[j].end()){
                int idx = distance(cost[j].begin(), itr);
                aux[idx] = (aux[idx] - dp[j] + mod) % mod;
            }
        }

        aux[0] = (aux[0] + mod) % mod;
        for1(j,k-1) aux[j] = (aux[j-1] + aux[j] + mod) % mod;
        swap(dp, aux);
    }

    ll ans = 0;
    for0(i,k) ans = (ans + dp[i]) % mod;
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
