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

vl pot10(17);
void calc(){
    pot10[0] = 1;
    for1(i,16) pot10[i] = 10LL * pot10[i-1];
}

void solver(){
    int n, k; cin>>n>>k;
    vl a(n);
    for0(i,n) cin>>a[i];
    sort(all(a));

    vector<vl> dp(k, vl(1 << n, -1)); dp[0][0] = 0;
    for(int mask = 1; mask < (1 << n); mask++){
        vb dig(10);
        bool cond = 1;
        vi rev;
        int cnt = 0;
        for(int i = 0; cond && i < n; i++){
            if(!(mask & (1 << i))){
                if(dig[a[i]]) cond = 0;
            }
            else{
                cnt++;
                if(!dig[a[i]]){
                    rev.pb(i);
                    dig[a[i]] = 1;
                }
            }
        }
        if(!cond) continue;

        for(int &idx : rev){
            int bit = 1 << idx;
            int num = mask ^ bit;
            for0(j, k){
                if(dp[j][num] == -1) continue;
                ll aux = dp[j][num] + a[idx] * pot10[cnt-1];
                ll mod = aux % k;
                dp[mod][mask] = max(dp[mod][mask], aux);
            }
        }
    }

    forn0(i, k){
        if(dp[i][(1 << n) - 1] != -1){
            cout<<dp[i][(1 << n) - 1]<<endl;
            return;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calc();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
