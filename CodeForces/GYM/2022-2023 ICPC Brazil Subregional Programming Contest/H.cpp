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

void tarjan(int u, vector<vi>& graph, vi&d, vi& low, vi& scc, vi& reps, vb& stacked, stack<int>& s, int& ticks, int& current_scc){
    d[u] = low[u] = ticks++;
    s.push(u);
    stacked[u] = true;
    const vi &out = graph[u];
    for(int k=0, m=out.size(); k<m; ++k){
        const int &v = out[k];
        if(d[v] == -1){
            tarjan(v, graph, d, low, scc, reps, stacked, s, ticks, current_scc);
            low[u] = min(low[u], low[v]);
        }
        else if(stacked[v])
            low[u] = min(low[u], low[v]);
    }
    if(d[u] == low[u]){
        int v;
        do{
            v = s.top();
            s.pop();
            stacked[v] = false;
            scc[v] = current_scc;
        }while (u != v);
        current_scc++;
    }
}

void solver(){
    int n, m; cin>>n>>m;

    vector<vi> graph(n+1);
    vi d(n+1, -1), low(n+1), scc(n+1), reps(n+1, 0);
    vb stacked(n+1);
    stack<int> s;
    int ticks = 0, current_scc = 0;

    for(int i = 1; i <= m; i++){
        int u, v;cin>>u>>v;
        graph[u].pb(v);
    }

    // Hallar los SCC
    for(int i = 1; i <= n; i++){
        if(d[i] == -1) 
            tarjan(i, graph, d, low, scc, reps, stacked, s, ticks, current_scc);
    }

    if(current_scc == 1){
        cout<<0<<endl;
        return;
    }

    int cnt1 = current_scc, cnt2 = current_scc;
    vector<vi> graph2(current_scc+1);
    vi inDegree(current_scc+1);
    for(int i = 1; i <= n; i++){
        for(int v : graph[i]){ // Buscar en las aristas del grafo original
            if(scc[v] != scc[i]){ // Verificar que la arista vaya a otro SCC
                if(graph2[scc[i]+1].empty()) cnt1--;
                graph2[scc[i]+1].pb(scc[v]+1);
                if(!inDegree[scc[v]+1]) cnt2--;
                inDegree[scc[v]+1]++;
            }
        }
    }

    cout<<max(cnt1, cnt2)<<endl;
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
