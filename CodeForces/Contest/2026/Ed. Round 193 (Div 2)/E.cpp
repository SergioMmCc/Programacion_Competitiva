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

pii dia(int s, int n, vi& pa, vector<vi>& tree){
    vb vis(n+1); vis[s] = 1;
    vi dis(n+1);
    queue<int> q; q.push(s);
    pii maxx = {0, s};
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(vis[v]) continue;
            vis[v] = 1;
            dis[v] = dis[u] + 1;
            q.push(v);
            pa[v] = u;
            maxx = max(maxx, {dis[v], v});
        }
    }

    return maxx;
}

void DFS(int u, int pa, vector<vi>& tree, vi& depth, int d, vi& dp, set<int>& ans){
    for(int v : tree[u]){
        if(v == pa) continue;
        depth[v] = depth[u] + 1;
        DFS(v, u, tree, depth, d, dp, ans);
        dp[u] = max(dp[v], dp[u]);
    }

    int cnt = 0;
    for(int v : tree[u]) if(v != pa && dp[v] == d) cnt++;

    if(cnt >= 2) ans.insert(d - depth[u]);
    dp[u] = max(dp[u], depth[u]);
}

set<int> calc(int x, int y, int n, vector<vi>& tree, int d){
    vi depth(n+1), dp(n+1);
    set<int> ans1 = {0}, ans2 = {0};
    DFS(x, y, tree, depth, d >> 1, dp, ans1);
    DFS(y, x, tree, depth, d >> 1, dp, ans2);
    
    set<int> ans;
    for(int a : ans1){
        for(int b : ans2){
            ans.insert(d - a - b);
        }
    }

    return ans;
}

void solver(){
    int n; cin>>n;
    vector<vi> tree(n+1);
    for0(i,n-1){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    vi pa(n+1);
    int u = dia(1, n, pa, tree).se;
    pii aux = dia(u, n, pa, tree);
    int d = aux.fi, v = aux.se;

    int x = v;
    for0(i,d/2) x = pa[x];
    int y = pa[x];

    set<int> ans = calc(x, y, n, tree, d);
    cout<<sz(ans);
    for(int a : ans) cout<<' '<<a;
    cout<<endl;
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
