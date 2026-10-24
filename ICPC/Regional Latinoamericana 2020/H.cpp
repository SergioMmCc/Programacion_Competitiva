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

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0){
		adj[a].pb({b, sz(adj[b]), c, c});
		adj[b].pb({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f){
		if(v == t || !f) return f;
		for(int& i = ptr[v]; i < sz(adj[v]); i++){
			Edge& e = adj[v][i];
			if(lvl[e.to] == lvl[v] + 1)
				if(ll p = dfs(e.to, t, min(f, e.c))){
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t){
		ll flow = 0; q[0] = s;
		for(ll L = 0; L < 31; L++) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int> (sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while(qi < qe && !lvl[t]){
				int v = q[qi++];
				for(Edge e : adj[v])
					if(!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while(ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while(lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; } // 1 si es parte del lado de source
};

int strToInt(string s){
    int ans = 0;
    for0(i,sz(s)){
        ans *= 10;
        ans += s[i] - '0';
    }

    return ans;
}

void solver(){
    int n; cin>>n;
    Dinic graph(n+1);

    for1(i,n){
        string m; cin>>m;
        if(m == "*"){
            int u; cin>>u;
            if(i == 1 && u == 1){
                cout<<'*'<<endl;
                return;
            }
            if(i == u) continue;
            graph.addEdge(i == 1 ? 0 : i, u, 1e4 + 1);
        }
        else{
            int mint = strToInt(m);
            for0(j,mint){
                int u; cin>>u;
                if(i == 1) graph.addEdge(0, u, 1);
                if(i == 1 || i == u) continue;
                graph.addEdge(i, u, 1);
            }
        }
    }

    int ans = graph.calc(0,1);
    if(ans > 1e4) cout<<'*'<<endl;
    else cout<<1 + ans<<endl;
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
