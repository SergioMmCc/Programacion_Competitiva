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
typedef pair<int, pii> piii;
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

const int maxn = 3e5 + 1, LOG_N = 19;
vector<vi> tree(maxn), up(LOG_N, vi(maxn));
vi pa(maxn), depth(maxn);

piii BFS(int s){
    vb vis(maxn); vis[s] = 1;
    vi dis(maxn);
    queue<int> q; q.push(s);
    int xt = s;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(vis[v]) continue;
            vis[v] = 1;
            dis[v] = dis[u] + 1;
            if(dis[v] > dis[xt]) xt = v;
            q.push(v);
        }
    }

    for1(i,maxn - 1) vis[i] = 0;
    vis[xt] = 1;
    pa[xt] = 0;
    q.push(xt);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(vis[v]) continue;
            vis[v] = 1;
            depth[v] = depth[u] + 1;
            pa[v] = u;
            if(depth[v] > depth[xt]) xt = v;
            q.push(v);
        }
    }

    int dia = depth[xt];
    for0(i,dia/2) xt = pa[xt];
    pii ans = {xt, 0};
    if(dia & 1) ans.se = pa[xt];

    return {dia, ans};
}

void calc(){
    for1(i,maxn -1) up[0][i] = pa[i];
    for1(bit,LOG_N-1){
        for1(i,maxn - 1){
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

int kStep(int s, int k){
    if(depth[s] < k) return -1; // Si s tiene menos profundidad que la cantidad de pasos que me piden
    for0(bit,LOG_N){
        if(k & (1 << bit)) s = up[bit][s];
    }

    return s;
}

void solver(){
    int n; cin>>n;
    int s;
    for0(i,n-1){
        int u, v; cin>>u>>v; u++; v++;
        s = u;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    piii aux = BFS(s);

    calc();

    int dia = aux.fi; pii cen = aux.se;
    cout<<dia<<endl;
    int q; cin>>q;
    while(q--){
        int x, y; cin>>x>>y; x++; y++;
        pa[x] = y;
        depth[x] = depth[y] + 1;
        up[0][x] = y;
        for1(bit,LOG_N-1) up[bit][x] = up[bit-1][up[bit-1][x]];
        
        if(dia & 1){
            int dis1 = depth[x] + depth[cen.fi] - 2*depth[LCA(x, cen.fi)];
            int dis2 = depth[x] + depth[cen.se] - 2*depth[LCA(x, cen.se)];
            if(min(dis1, dis2) <= dia/2){
                cout<<dia<<endl;
                continue;
            }

            if(dis1 > dis2) swap(cen.fi, cen.se);
            cen.se = -1;
            dia++;
        }
        else{
            int lc = LCA(x, cen.fi);
            int dis = depth[x] + depth[cen.fi] - 2*depth[lc];
            if(dis <= dia / 2){
                cout<<dia<<endl;
                continue;
            }

            if(lc != cen.fi) cen = {cen.fi, up[0][cen.fi]};
            else cen = {cen.fi, kStep(x, dia/2)};
            dia++;
        }

        cout<<dia<<endl;
    }
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
