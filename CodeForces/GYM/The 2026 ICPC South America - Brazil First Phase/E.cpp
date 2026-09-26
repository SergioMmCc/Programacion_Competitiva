#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
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

int ckmin(int &a, int b) { return a > b ? ((a = b), true) : false; }

/**
 * return the jobs of each worker in the optimal assignment,
 * or -1 if the worker is not assigned
 */
template <class T> vi hungarian(const vector<vector<T>> &C){
	int J = C.size();
	int W = C[0].size();
	assert(J <= W); // Verifica que el lado izquierdo (W) sea mayor o igual al lado derecho (J)

	// job[w] = job assigned to w-th worker, or -1 if no job assigned
	// note: a W-th worker was added for convenience
	vi job(W + 1, -1);
	vector<T> h(W);  // Johnson potentials

	const T inf = numeric_limits<T>::max();
	// assign j_cur-th job using Dijkstra with potentials
	for0(j_cur,J){
		int w_cur = W;  // unvisited worker with minimum distance
		job[w_cur] = j_cur;

		vector<T> dist(W + 1, inf);  // Johnson-reduced distances
		dist[W] = 0;
		vb vis(W + 1);     // whether visited yet
		vi prv(W + 1, -1);  // previous worker on shortest path
		while(job[w_cur] != -1){   // Dijkstra step: pop min worker from heap
			T min_dist = inf;
			vis[w_cur] = 1;
			int w_next = -1;  // next unvisited worker with minimum distance

			// consider extending shortest path by w_cur -> job[w_cur] -> w
			for0(w,W){
				if(!vis[w]){
					// sum of reduced edge weights w_cur -> job[w_cur] -> w
					T edge = C[job[w_cur]][w] - h[w];
					if(w_cur != W){
						edge -= C[job[w_cur]][w_cur] - h[w_cur];
						assert(edge >= 0);
					}
					if(ckmin(dist[w], dist[w_cur] + edge)) { prv[w] = w_cur; }
					if(ckmin(min_dist, dist[w])) { w_next = w; }
				}
			}
			w_cur = w_next;
		}

		for(int w = 0; w < W; w++){  // update potentials
			ckmin(dist[w], dist[w_cur]);
			h[w] += dist[w];
		}

		while(w_cur != W){  // update job assignment
			job[w_cur] = job[prv[w_cur]];
			w_cur = prv[w_cur];
		}
	}

	return job; // Retorna la mejor asignacion encontrada
}

void solver(){
    int n, m1, m2; cin>>n>>m1>>m2;
    set<pii> a, b;
    for0(i,m1){
        int u, v; cin>>u>>v; if(u > v) swap(u, v);
        a.insert({u, v});
    }
    for0(i,m2){
        int u, v; cin>>u>>v; if(u > v) swap(u, v);
        if(a.find({u, v}) != a.end()) a.erase({u, v});
        else b.insert({u, v});
    }
    
    if(m1 != m2){
        cout<<-1<<endl;
        return;
    }

    if(a.empty()){
        cout<<0<<endl;
        return;
    }
    n = sz(a);

    vii d, e;
    for(pii x : a) d.pb(x);
    for(pii x : b) e.pb(x);

    vector<vi> c(n, vi(n, 100000));
    for0(i,n){
        for0(j,n){
            int cost = 2;
            // assert(x.fi != y.fi || x.se != y.se);
            if(d[i].fi == e[j].fi || d[i].se == e[j].se || d[i].fi == e[j].se || d[i].se == e[j].fi) cost--;
            c[j][i] = cost;
        }
    }

    vi mat = hungarian(c);

    int ans = 0;
	for0(i,n) ans += c[mat[i]][i];
	cout<<ans<<endl;
}

signed main(){
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
