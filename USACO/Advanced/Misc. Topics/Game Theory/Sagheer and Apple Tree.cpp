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

const int maxn = 1e5 + 1;
vector<vi> tree(maxn);
vi depth(maxn);
int DFS(int u){
    int ans = depth[u];
    for(int v : tree[u]){
        depth[v] = depth[u] + 1;
        ans = max(ans, DFS(v));
    }

    return ans;
}

void solver(){
    int n; cin>>n;
    vi a(n+1);
    for1(i,n) cin>>a[i];
    forlr(i,2,n){
        int p; cin>>p;
        tree[p].pb(i);
    }

    int maxd = DFS(1);
    map<int, int> freq;
    int aux = 0;
    ll cnt = 0;
    for1(i,n){
        if((depth[i] & 1) == (maxd & 1)){
            aux ^= a[i];
            cnt++;
        }
        else freq[a[i]]++;
    }

    ll ans = 0;
    if(!aux) ans += ((cnt) * (cnt - 1)) / 2 + (((ll)n - cnt) * ((ll)n - cnt - 1)) / 2;
    for1(i,n){
        if((depth[i] & 1) != (maxd & 1)) continue;
        if(freq.find(aux ^ a[i]) != freq.end()) ans += (ll)freq[aux ^ a[i]];
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
