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

vector<ld> area(maxn);
vector<vi> tree(maxn);
vi deg(maxn);
vector<vector<ld>> dp(2, vector<ld>(maxn));
map<pair<pll, pll>, int> add;

void DFS(int u, int pa){
    for(int v : tree[u]){
        if(v == pa) continue;
        DFS(v, u);

        dp[0][u] += dp[1][v];
        dp[1][u] += min(dp[0][v], dp[1][v]);
    }

    if(deg[u] != 3) dp[0][u] = 1'000'000'000'000'000'000.0;
    dp[1][u] += area[u];
}

void solver(){
    int n; cin>>n;
    for1(i,n){
        ll x1, y1, x2, y2, x3, y3; cin>>x1>>y1>>x2>>y2>>x3>>y3;
        pll a1 = {x1, y1}, a2 = {x2, y2}, a3 = {x3, y3};
        if(a1 > a2) swap(a1, a2);
        if(a2 > a3) swap(a2, a3);
        if(a1 > a2) swap(a1, a2);
        if(add.find({a1, a2}) != add.end()){
            int v = add[{a1, a2}];
            tree[i].pb(v);
            tree[v].pb(i);
            deg[i]++;
            deg[v]++;
        }
        else{
            add[{a1, a2}] = i;
        }
        if(add.find({a1, a3}) != add.end()){
            int v = add[{a1, a3}];
            tree[i].pb(v);
            tree[v].pb(i);
            deg[i]++;
            deg[v]++;
        }
        else{
            add[{a1, a3}] = i;
        }
        if(add.find({a2, a3}) != add.end()){
            int v = add[{a2, a3}];
            tree[i].pb(v);
            tree[v].pb(i);
            deg[i]++;
            deg[v]++;
        }
        else{
            add[{a2, a3}] = i;
        }

        area[i] = abs((ld)(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
        // cout<<"i -> "<<area[i]<<endl;
    }

    DFS(1, 0);
    cout<<fixed<<setprecision(1)<<min(dp[0][1], dp[1][1])<<endl;
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
