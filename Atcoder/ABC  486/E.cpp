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
typedef pair<ll, pii> plii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<plii> vlii;
// #include<ext/pb_ds/assoc_container.hpp> // Poner arriba de #define int long long si lo hay
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void solver(){
    int n, m; cin>>n>>m;
    map<ll, vii> edj;
    for0(i,m){
        int u, v; ll w; cin>>u>>v>>w;
        edj[w].pb({u, v});
    }

    ll ans = 0;
    vl best(n+1);
    for(const auto& par : edj){
        ll w = par.fi;

        vll upd;
        for(pii e : par.se){
            int u = e.fi, v = e.se;
            ll aux1 = w + best[v];
            ans = max(ans, aux1);
            upd.pb({u, aux1});

            ll aux2 = w + best[u];
            ans = max(ans, aux2);
            upd.pb({v, aux2});
        }

        for(pll x : upd) best[x.fi] = max(best[x.fi], x.se);
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
