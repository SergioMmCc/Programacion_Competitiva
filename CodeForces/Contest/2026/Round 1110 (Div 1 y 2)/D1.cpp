#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
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
typedef vector<piii> viii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void topoSort(int n, vi& orden, vi& inDegree, vector<vi>& graph){
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!inDegree[i]){ 
            // Si el nodo no tiene ningun inDegree, quiere decir que puede ir al incio del topoSort
            q.push(i);
            orden.pb(i);
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            inDegree[v]--; // Quitamos un inDegree a cada vertice que puede ser visitado desde otro ya procesado
            if(!inDegree[v]){ 
                // Si su inDegree ahora es 0, quiere decir que ya fueron procesados todos los nodos que lo 
                // anteceden, por ende ahora puede ser agregado al topoSort, y lo metemos a la cola
                q.push(v);
                orden.pb(v);
            }
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    vb a(n+1);
    viii save(m);
    for(int i = 0; i < m; i++){
        int o, u, v; cin>>o>>u>>v;
        save[i] = {o & 1, {u, v}};
        if(u == v) a[u] = o & 1;
    }

    vector<vi> graph(n+1);
    vi inDegree(n+1);
    for(int i = 0; i < m; i++){
        int u = save[i].se.fi, v = save[i].se.se;
        bool o = save[i].fi;
        if(u == v) continue;

        if(a[u] == a[v]){
            if((a[u] && !o) || (!a[u] && o)){
                cout<<"NO"<<endl;
                return;
            }
            continue;
        }

        if(a[u] == o){
            graph[v].pb(u);
            inDegree[u]++;
        }
        else{
            graph[u].pb(v);
            inDegree[v]++;
        }
    }

    vi orden;
    topoSort(n, orden, inDegree, graph);
    if(sz(orden) < n){
        cout<<"NO"<<endl;
        return;
    }
    // cout<<sz(orden)<<endl;
    vi ans(n+1);
    for(int i = 0; i < n; i++){
        ans[orden[i]] = i+1;
        if(!a[orden[i]]) ans[orden[i]] *= -1;
    }

    cout<<"YES"<<endl;
    for(int i = 1; i <= n; i++) cout<<ans[i]<<' ';
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
