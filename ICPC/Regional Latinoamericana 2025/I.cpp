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

const int maxn = 501;
vector<vi> graf1(maxn), graf2(maxn);

bool go(int i, int j, int a, int b, vector<vb>& dp, vector<vii>& pa){
    if(dp[i][j] || (i == a && j == b)) return 1;

    if(i > j || i == a){
        for(int v : graf2[j]){
            if(v == i) continue;
            if(go(i, v, a, b, dp, pa)){
                pa[i][j] = {i, v};
                return 1;
            }
        }
    }

    if(i < j || j == b){
        for(int u : graf1[i]){
            if(u == j) continue;
            if(go(u, j, a, b, dp, pa)){
                pa[i][j] = {u, j};
                return 1;
            }
        }
    }

    return 0;
}   

void solver(){
    int n, m; cin>>n>>m;
    vii pro;
    for0(i,m){
        int u, v; cin>>u>>v;
        if(v == u+n) continue;
        if(v <= n) graf1[u].pb(v);
        else if(u > n) graf2[u-n].pb(v-n);
        else pro.pb({u, v-n});
    }
    if(n == 1 || pro.empty()){
        cout<<'*'<<endl;
        return;
    }

    for(pii e : pro){
        int u = e.fi, v = e.se;
        vector<vb> dp(n+1, vb(n+1));
        vector<vii> pa(n+1, vii(n+1));
        if(!go(1, v, u, n, dp, pa)) continue;

        vi st = {1}, en = {v};
        pii cur = {1, v}, goal = {u, n};
        while(cur != goal){
            pii aux = cur;
            cur.fi = pa[aux.fi][aux.se].fi;
            cur.se = pa[aux.fi][aux.se].se;

            if(cur.fi == aux.fi) en.pb(cur.se);
            else st.pb(cur.fi);
        }

        cout<<sz(st) + sz(en)<<endl;
        for(int x : st) cout<<x<<' ';
        for(int x : en) cout<<x+n<<' ';
        cout<<endl;
        return;
    }

    cout<<'*'<<endl;
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
