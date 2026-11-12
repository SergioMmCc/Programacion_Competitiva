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

int LOG_N = 19, maxn = 5e5 + 1; // techo del log2 de n
vi ord, depth(maxn), pa(maxn);
vector<vi> tree(maxn), up(LOG_N, vi(maxn));

struct DSU {
    vi p; // p es el lider de cada nodo
    DSU(int n) : p(n) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b){
        if((a = find(a)) == (b = find(b))) return 0;
        p[b] = a;
        return 1;
    }
};

// Para cada nodo se calcula a donde llega tras realizar 2^x pasos. 
// Se necesita para hallar el LCA y para la funcion kStep.
// Complejidad: O(n * log(k))
void calc(int n){
    for1(bit,LOG_N-1){
        for1(i,n){
            up[bit][i] = up[bit-1][up[bit-1][i]];
        }
    }
}

int LCA(int a, int b){
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

void DFS(int u){
    depth[u] = depth[pa[u]] + 1;
    if(tree[u].empty()){
        ord.pb(u);
        return;
    }

    for(int v : tree[u]) DFS(v);
}

void solver(){
    int n; cin>>n;
    forlr(i,2,n){
        int u; cin>>u;
        pa[i] = u;
        tree[u].pb(i);
        up[0][i] = u;
    }
    DFS(1);
    calc(n);
    DSU uf(n+1);
    vi ans(n+1);

    for(int i = 0; i < sz(ord) - 1; i++){
        int u = ord[i], v = ord[i+1];
        int lc = LCA(u, v);
        int lid = uf.find(lc);
        if(!lid){
            cout<<'*'<<endl;
            return;
        }
        ans[u] = lid;
        uf.join(pa[lid], lid);
    }

    if(uf.find(1) != 1){
        cout<<'*'<<endl;
        return;
    }
    ans[ord.back()] = 1;
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