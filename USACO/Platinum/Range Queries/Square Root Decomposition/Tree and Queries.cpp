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

const int maxn = 1e5;
vector<vi> tree(maxn);

void DFS(vii& ran, int u, int pa, int &cnt){
    ran[u].fi = cnt;
    cnt++;
    for(int v : tree[u]){
        if(v == pa) continue;
        DFS(ran, v, u, cnt); // Se visita el subarbol que tiene u como raiz
    }

    ran[u].se = cnt - 1;
}

struct query {
    int l, r, idx, maxi;
};
int blen; // blen = sqrt(n)
bool cmp(query u, query v){
    int x = u.l / blen;
    if(x != v.l / blen) return x < v.l / blen;
    return x&1 ? u.r > v.r : u.r < v.r; // Bloque impar r decreciente, par r creciente
}

vi aux(1e5 + 1), pri(1e5 + 1);
void add(int idx, vi& a){
    aux[a[idx]]++;
    pri[aux[a[idx]]]++;
}
void del(int idx, vi& a){
    pri[aux[a[idx]]]--;
    aux[a[idx]]--;
}

void solver(){
    int n, q; cin>>n>>q;
    vi a(n+1);
    for1(i,n) cin>>a[i];
    for1(i,n-1){
        int u,v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    vii ran(n+1);
    int cnt = 1;
    DFS(ran, 1, -1, cnt);
    vi orden(n+1);
    for1(i,n) orden[ran[i].fi] = i;

    blen = sqrt(n); // Raiz del tamaño del arreglo
    vector<query> qs(q);
    for0(i,q){
        int u, x; cin>>u>>x;
        qs[i] = {ran[u].fi, ran[u].se, i, x};
    }
    sort(all(qs), cmp);

    int l = 1, r = 0;
    vi ans(q);
    for0(i,q){
        while(r < qs[i].r) add(orden[++r], a);
        while(l > qs[i].l) add(orden[--l], a);
        while(r > qs[i].r) del(orden[r--], a);
        while(l < qs[i].l) del(orden[l++], a);
        ans[qs[i].idx] = pri[qs[i].maxi];
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
