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

void topoSort(int n, vi& inDegree, vector<vi>& graph, vi& val){
    queue<int> q;
    for0(i,n){
        if(!inDegree[i]){ // Agregar si no tiene aristas de entrada
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            inDegree[v]--;
            val[v] = min(val[v], val[u]);
            if(!inDegree[v]){ // Agregar si ya se visitaron todos sus predecesores
                q.push(v);
            }
        }
    }
}

void tarjan(int u, vector<vi>& graph, vi&d, vi& low, vi& scc, vi& reps, vb& stacked, stack<int>& s, int& ticks, int& current_scc){
    d[u] = low[u] = ticks++;
    s.push(u);
    stacked[u] = 1;
    const vi &out = graph[u];
    for(int k=0, m=sz(out); k<m; ++k){
        const int &v = out[k];
        if(d[v] == -1){
            tarjan(v, graph, d, low, scc, reps, stacked, s, ticks, current_scc);
            low[u] = min(low[u], low[v]);
        }
        else if(stacked[v]) low[u] = min(low[u], low[v]);
    }
    if(d[u] == low[u]){
        int v;
        do{
            v = s.top();
            s.pop();
            stacked[v] = 0;
            scc[v] = current_scc;
        }while (u != v);
        current_scc++;
    }
}

int trans(int n){
    // cout<<"n -> "<<n;
    int ans = 0;
    while(n > 0){
        ans += (n % 10) * (n % 10);
        n /= 10;
    }

    // cout<<" ans -> "<<ans<<endl;
    assert(ans <= 1e6);
    return ans;
}

void solver(){
    int a, b; cin>>a>>b;
    int n = 1e6;
    vector<vi> graph(n+1);
    vi d(n+1, -1), low(n+1), scc(n+1), reps(n+1, 0);
    vb stacked(n+1);
    stack<int> s;
    int ticks = 0, current_scc = 0;

    for1(i,n){
        int v = trans(i);
        if(v == i || v > n) continue;
        graph[i].pb(v);
    }

    // Hallar los SCC
    for(int i = 1; i <= n; i++){ // 1-index, se puede cambiar a 0-index
        if(d[i] == -1) 
            tarjan(i, graph, d, low, scc, reps, stacked, s, ticks, current_scc);
    }

    vi val(current_scc);
    forn1(i,n) val[scc[i]] = i;

    vector<vi> graph2(current_scc);
    vi inDegree(current_scc);
    for1(i,n){
        for(int v : graph[i]){
            // cout<<"i -> "<<i<<" v -> "<<v<<" scci -> "<<scc[i]<<" sccv -> "<<scc[v]<<endl;
            if(scc[v] != scc[i]){ // Verificar que la arista vaya a otro SCC
                graph2[scc[v]].pb(scc[i]);
                inDegree[scc[i]]++;
            }
        }
    }

    topoSort(current_scc, inDegree, graph2, val);

    ll ans = 0;
    forlr(i,a,b) ans += (ll)val[scc[i]];
    cout<<ans<<endl;
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
