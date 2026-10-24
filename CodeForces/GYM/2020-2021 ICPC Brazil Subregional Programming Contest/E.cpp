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
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using indexed_set = tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

int LOG_N = 17; // techo del log2 de n

vector<vii> qs(1e5 + 1);
vi ans(1e5 + 1), val(1e5+1);
indexed_set nums;
vector<vi> up(LOG_N, vi(1e5 + 1));

void calc(int n){
    for1(bit,LOG_N-1){
        for1(i,n){
            up[bit][i] = up[bit-1][up[bit-1][i]];
        }
    }
}

vector<vi> graf(1e5 + 1);

void DFS(int u){
    for(pii x : qs[u]) nums.insert(x);
    
    ans[u] = nums.order_of_key({val[u], 2e5});

    for(int v : graf[u]) DFS(v);

    for(pii x : qs[u]) nums.erase(x);
}

void solver(){
    int n, q; cin>>n>>q;    
    for1(i,n){
        cin>>val[i]>>up[0][i];
        if(i > 1) graf[up[0][i]].pb(i);
    }
    up[0][1] = 0;
    calc(n);

    while(q--){
        int u, l, r; cin>>u>>l>>r;

        forn0(x,LOG_N){
            int aux = up[x][u];
            if(aux && val[aux] <= r) u = aux;
        }

        qs[u].pb({l, q});
    }

    DFS(1);
    for1(i,n) cout<<ans[i]<<' ';
    cout<<endl;
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
