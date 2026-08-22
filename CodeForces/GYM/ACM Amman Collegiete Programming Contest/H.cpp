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

const int maxn = 1e5 + 5;
vector<vector<int>> graph(maxn);
vector<bool> visited(maxn), is(maxn);
vector<int> dp(maxn), sons[maxn], father(maxn), depth(maxn);
vii rama(maxn);

void DFS(int u, int prev){
    visited[u] = 1;
    for(int v : graph[u]){
        if(v == prev) continue;
        if(visited[v]){ // Back-edge
            // Revisar que la arista vaya de abajo hacia arriba
            // para no considerarla 2 veces
            if(depth[v] > depth[u]) continue;
            dp[u]++;
            dp[v]--;
            continue;
        }
        sons[u].pb(v); // Span-edge
        father[v] = u;
        depth[v] = depth[u] + 1;
        DFS(v, u);
    }
}

int calc(int u){
    for(int v : sons[u]) dp[u] += calc(v);
    return dp[u];
}

int cnt = 0, ans = maxn;
void calcA(int u, int pa){
    for(int v : sons[u]){
        if(v == pa) continue;
        calcA(v, u);
        int aux = rama[v].fi + (is[v] ? 1 : 0);
        // cout<<"u -> "<<u<<" v -> "<<v<<" aux -> "<<aux<<endl;
        if(aux > rama[u].fi){
            rama[u].se = rama[u].fi;
            rama[u].fi = aux;
        }
        else if(aux > rama[u].se) rama[u].se = aux;
    }
    // cout<<"u -> "<<u<<" .fi -> "<<rama[u].fi<<" .se -> "<<rama[u].se<<endl;
    ans = min(ans, cnt - rama[u].fi - rama[u].se);
}

void solver(){
    ans = maxn; cnt = 0;
    int n, m; cin>>n>>m;
    for1(i,n){
        graph[i].clear();
        dp[i] = 0;
        sons[i].clear();
        visited[i] = 0;
        father[i] = 0;
        depth[i] = 0;
        is[i] = 0;
        rama[i] = {0,0};
    }

    for0(i,m){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    DFS(1, -1); // Crear DFS tree
    calc(1); // Calcular el dp
    // for1(i,n){
    //     cout<<"i -> "<<i<<": ";
    //     for(int x : sons[i]) cout<<" "<<x; cout<<endl;
    // }

    for(int i = 2; i <= n; i++){
        // Si dp[i] == 0, la arista que conecta i y su padre son un puente
        if(!dp[i]){
            cnt++;
            is[i] = 1;
        }
    }
    // db(cnt);

    calcA(1,-1);
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
