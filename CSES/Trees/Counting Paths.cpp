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

int LOG_N = 18; // techo del log2 de n

// Para cada nodo se calcula a donde llega tras realizar 2^x pasos. 
// Se necesita para hallar el LCA y para la funcion kStep.
// Complejidad: O(n * log(k))
void calc(int n, vi& pa, vector<vi>& up){
    for1(i,n) up[0][i] = pa[i];
    for1(bit,LOG_N-1){
        for1(i,n){
            up[bit][i] = up[bit-1][up[bit-1][i]];
        }
    }
}

int LCA(int a, int b, vi& depth, vector<vi>& up){
    if(depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];

    // Este ciclo pone a y b en el mismo nivel
    forn0(j,LOG_N) if(k & (1 << j)) a = up[j][a];

    if(a == b) return a;

    forn0(j,LOG_N){
        if(up[j][a] != up[j][b]){
            a = up[j][a];
            b = up[j][b];
        }
    }
    return up[0][a];
}

const int maxn = 2e5 + 1;
vi pre(maxn), post(maxn), ans(maxn);

void DFS1(int u, int p, vi& depth, vi& pa, vector<vi>& tree){
    for(int v : tree[u]){
        if(v == p) continue;
        pa[v] = u;
        depth[v] = depth[u] + 1;
        DFS1(v, u, depth, pa, tree);
    }
}

void DFS2(int u, int p, vector<vi>& tree){
    for(int v : tree[u]){
        if(v == p) continue;
        DFS2(v, u, tree);
        pre[u] += pre[v] + post[v];
    }

    ans[u] = pre[u];
}

void solver(){
    int n, m; cin>>n>>m;
    vector<vi> tree(n+1);
    for1(i,n-1){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    vi depth(n+1), pa(n+1);
    DFS1(1, -1, depth, pa, tree);
    
    // Precalcular la matriz up
    vector<vi> up(LOG_N, vi(n+1));
    calc(n, pa, up);

    for0(i,m){
        int u, v; cin>>u>>v;
        pre[u]++; pre[v]++;
        int lc = LCA(u, v, depth, up);
        pre[lc]--; post[lc]--;
    }

    DFS2(1, -1, tree);
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
