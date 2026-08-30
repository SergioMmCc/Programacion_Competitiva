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

/*
- Complejidad: O(v²*sqrt(e)) o (v³)
*/

const int maxn = 505;

template <int SZ> struct HLPP {
	typedef ll F; // flow type
	struct Edge { int to, rev; F f; };
	const F INF = numeric_limits<F>::max();
	
	int N,s,t;
	vector<Edge> adj[SZ];
	void ae(int u, int v, F cap){
		assert(cap >= 0); // don't try smth dumb
		Edge a{v, sz(adj[v]), cap}, b{u, sz(adj[u]), 0};
		adj[u].pb(a), adj[v].pb(b);
	}

	vi lst[SZ], gap[SZ];
	F excess[SZ];
	int highest, height[SZ], cnt[SZ], work;
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
		if(excess[e.to] == 0) lst[height[e.to]].pb(e.to);
		F df = min(excess[v], e.f);
		e.f -= df, adj[e.to][e.rev].f += df;
		excess[v] -= df, excess[e.to] += df;
	}
	void discharge(int v){
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
	F maxFlow(int _N, int _s, int _t){
		N = _N, s = _s, t = _t; if(s == t) return -1;
		for0(i,N) excess[i] = 0;
		excess[s] = INF, excess[t] = -INF;
		globalRelabel();
		for(auto & e : adj[s]) push(s,e);
		for(; highest >= 0; highest--){
			while(sz(lst[highest])){
				int v = lst[highest].back();
				lst[highest].pop_back();
				discharge(v);
				if(work > 4*N) globalRelabel();
			}
        }
		return excess[t]+INF;
	}
};
HLPP<maxn> graph; // Inicializar (el tamaño debe ser una constante)

void solver(){
    int n, m; cin>>n>>m;
    for0(i,m){
        int u, v; ll c; cin>>u>>v>>c;
        graph.ae(u, v, c); // Agregar arista dirigida u -> v con capacidad c
    }

    ll flow = graph.maxFlow(n, 1, n); // Si s == t, retorna -1
    cout<<flow<<endl;
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