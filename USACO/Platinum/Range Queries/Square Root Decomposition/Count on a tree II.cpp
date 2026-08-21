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

struct query {
    int l, r, idx, lc;
};
int blen; // blen = sqrt(n)
bool cmp(query u, query v){
    int x = u.l / blen;
    if(x != v.l / blen) return x < v.l / blen;
    return x&1 ? u.r > v.r : u.r < v.r; // Bloque impar r decreciente, par r creciente
}

const int maxn = 4e4;
vector<vi> tree(maxn);

void DFS(vii& ran, int u, int pa, int &cnt, vi& arr, vi& p, vi& depth){
    // Se dice que el rango de u inicia en cnt. Ademas ese sera su indice en el array que se contruira.
    ran[u].fi = cnt;
    arr.pb(u);
    cnt++; // Se suma 1 para guardar que se ha visitado un nuevo nodo
    for(int v : tree[u]){
        if(v == pa) continue;
        p[v] = u;
        depth[v] = depth[u] + 1;
        DFS(ran, v, u, cnt, arr, p, depth); // Se visita el subarbol que tiene u como raiz
    }

    arr.pb(u);
    ran[u].se = cnt;
    cnt++;
}

int LOG_N = 16; // techo del log2 de n

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

vi aux(4e4 + 1);
int pri = 0;
void add(int idx, vl& a){
    if(!aux[a[idx]]) pri++;
    aux[a[idx]]++;
}
void del(int idx, vl& a){
    aux[a[idx]]--;
    if(!aux[a[idx]]) pri--;
}

void compressArr(vl& a){
    vl comp = a;
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    for0(i,sz(a)) a[i] = lb(all(comp), a[i]) - comp.begin();
}

void solver(){
    int n, q; cin>>n>>q;
    vl a(n+1);
    for1(i,n) cin>>a[i];
    compressArr(a);
    for1(i,n-1){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    vii ran(n+1);
    vi arr(1), p(n+1), depth(n+1);
    int cnt = 1;
    DFS(ran, 1, -1, cnt, arr, p, depth);
    vector<vi> up(LOG_N, vi(n+1));
    calc(n, p, up);

    blen = sqrt(sz(arr)); // Raiz del tamaño del arreglo
    vector<query> qs(q);
    for0(i,q){
        int u, v; cin>>u>>v;
        if(ran[u].fi > ran[v].fi) swap(u, v);
        int lc = LCA(u, v, depth, up);
        // cout<<"u -> "<<u<<" v -> "<<v<<" lc -> "<<lc<<endl;
        if(lc == u) qs[i] = {ran[u].fi, ran[v].fi, i, lc};
        else qs[i] = {ran[u].se, ran[v].fi, i, lc};
    }
    sort(all(qs), cmp);

    vi ans(q);
    int l = 1, r = 0;
    vi steps(n+1);
    for0(i,q){
        while(r < qs[i].r){
            steps[arr[++r]]++;
            if(steps[arr[r]] % 2 == 1) add(arr[r], a);
            else del(arr[r], a);
        }
        while(l > qs[i].l){
            steps[arr[--l]]++;
            if(steps[arr[l]] % 2 == 1) add(arr[l], a);
            else del(arr[l], a);
        }
        while(r > qs[i].r){
            steps[arr[r]]--;
            if(steps[arr[r]] % 2 == 1) add(arr[r], a);
            else del(arr[r], a);
            r--;
        }
        while(l < qs[i].l){
            steps[arr[l]]--;
            if(steps[arr[l]] % 2 == 1) add(arr[l], a);
            else del(arr[l], a);
            l++;
        }

        if(qs[i].lc != arr[l] && !aux[a[qs[i].lc]]) ans[qs[i].idx] = pri+1;
        else ans[qs[i].idx] = pri;
    }

    for0(i,q) cout<<ans[i]<<endl;
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
