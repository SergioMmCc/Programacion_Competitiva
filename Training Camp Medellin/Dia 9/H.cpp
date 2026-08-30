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

const int limite = 200010;

vb esPrimo(limite + 1, 1);
vi primos;

void sieve(){
    esPrimo[0] = esPrimo[1] = 0;
    for(ll p = 2; p * p <= limite; p++){
        if(esPrimo[p]){
            for(ll i = p * p; i <= limite; i += p) esPrimo[i] = 0;
        }
    }

    for(int i = 2; i < limite; i++)
        if(esPrimo[i]) primos.pb(i); 
}

struct HLPP {
    typedef ll F; // flow type
    struct Edge { int to, rev; F f; };
    const F INF = numeric_limits<F>::max();

    int N, s, t;
    vector<vector<Edge>> adj;
    vector<vi> lst, gap;
    vector<F> excess;
    vi height, cnt;
    int highest, work;

    HLPP(int n) : N(n), s(0), t(0), adj(n), lst(n), gap(n),
                  excess(n), height(n), cnt(n), highest(0), work(0) {}

    void ae(int u, int v, F cap){
        assert(cap >= 0);
        Edge a{v, sz(adj[v]), cap}, b{u, sz(adj[u]), 0};
        adj[u].pb(a), adj[v].pb(b);
    }
    void updHeight(int v, int nh){
        work++;
        if(height[v] != N) cnt[height[v]]--;
        height[v] = nh;
        if(nh == N) return;
        cnt[nh]++, highest = nh;
        gap[nh].pb(v);
        if(excess[v] > 0) lst[nh].pb(v);
    }
    void globalRelabel(){
        work = 0;
        for0(i,N) height[i] = N, cnt[i] = 0;
        for0(i,highest) lst[i].clear(), gap[i].clear();
        height[t] = 0;
        queue<int> q({t});
        while(sz(q)){
            int v = q.front(); q.pop();
            for(auto &e : adj[v]){
                if(e.to != s && height[e.to] == N && adj[e.to][e.rev].f > 0){
                    q.push(e.to), updHeight(e.to, height[v] + 1);
                }
            }
            highest = height[v];
        }
    }
    void push(int v, Edge& e){
        if(excess[e.to] == 0 && height[e.to] < N) lst[height[e.to]].pb(e.to);
        F df = min(excess[v], e.f);
        e.f -= df, adj[e.to][e.rev].f += df;
        excess[v] -= df, excess[e.to] += df;
    }
    void discharge(int v){
        if(height[v] >= N) return;
        int nh = N;
        for(auto &e : adj[v]){
            if(e.f > 0){
                if(height[v] == height[e.to] + 1){
                    push(v, e);
                    if(excess[v] <= 0) return;
                } else nh = min(nh, height[e.to]+1);
            }
        }
        if(cnt[height[v]] > 1) updHeight(v, nh);
        else{
            forlr(i,height[v],highest) {
                for(auto &j : gap[i]) updHeight(j, N);
                gap[i].clear();
            }
        }
    }
    F maxFlow(int _s, int _t){
        s = _s, t = _t; if(s == t) return -1;
        for0(i,N) excess[i] = 0;
        excess[s] = INF, excess[t] = -INF;
        globalRelabel();
        for(auto &e : adj[s]) push(s,e);
        for(; highest >= 0; highest--){
            while(sz(lst[highest])){
                int v = lst[highest].back();
                lst[highest].pop_back();
                discharge(v);
                if(work > 4*N) globalRelabel();
            }
        }
        return excess[t] + INF;
    }
};

struct Edge{
    int p, c, l;
};

struct comp{
    bool operator() (Edge a, Edge b){
        return a.l < b.l;
    }
};

bool check(int n, int k, vector<Edge>& edges, int m){
    vi par, impar;
    int ans = 0;
    pii max1 = {0, 0};
    HLPP graph(n + 2); //Crear un grafo para usar Dinic
    for(int i = 0; i < sz(edges); i++){
        Edge e = edges[i];
        if(e.l > m) break;
        if(e.c == 1){
            max1 = max(max1, {e.p, i});
            continue;
        }
        ans += e.p;
        if(e.c & 1){
            graph.ae(n, i, e.p);
            impar.pb(i);
        }
        else{
            graph.ae(i, n+1, e.p);
            par.pb(i);
        }
    }

    if(max1.fi){
        ans += edges[max1.se].p;
        graph.ae(n, max1.se, max1.fi);
        impar.pb(max1.se);
    }

    for(int x : impar){
        for(int y : par){
            if(esPrimo[edges[x].c + edges[y].c]) graph.ae(x, y, INF);
        }
    }

    ans -= graph.maxFlow(n, n+1);
    return ans >= k;
}

void solver(){
    int n, k; cin>>n>>k;
    vector<Edge> edges(n);
    for(int i = 0; i < n; i++) cin>>edges[i].p>>edges[i].c>>edges[i].l;
    sort(all(edges), comp());

    int l = 1, r = n+1;
    while(l < r){
        int m = (l + r) / 2;
        if(check(n, k, edges, m)) r = m;
        else l = m+1;
    }

    cout<<(l <= n ? l : -1)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    sieve();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}