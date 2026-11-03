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
const ll MOD = 1e9 + 7;

void topoSort(int n, vi& cnt, vi& inDegree, vector<vi>& graph){
    queue<int> q;
    for1(i,n){
        if(!inDegree[i]){ // Agregar si no tiene aristas de entrada
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            inDegree[v]--;
            cnt[v] = (cnt[v] + cnt[u]) % MOD;
            if(!inDegree[v]){ // Agregar si ya se visitaron todos sus predecesores
                q.push(v);
            }
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;

    vector<vi> aux(n+1);
    for1(i,m){
        int c; cin>>c;
        for0(j,c){
            int u; cin>>u;
            aux[i].pb(u);
        }
    }

    vb can(n+1); can[1] = 1;
    queue<int> q; q.push(1);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : aux[u]){
            if(can[v]) continue;
            can[v] = 1;
            q.push(v);
        }
    }

    vector<vi> graf(n+1);
    vi cnt(n+1); cnt[1] = 1;
    vi inDegree(n+1);
    for1(i,n){
        if(!can[i]) continue;
        for(int v : aux[i]){
            graf[i].pb(v);
            inDegree[v]++;
        }
    }

    topoSort(n, cnt, inDegree, graf);

    int ans1 = 0, ans2 = 0;
    forlr(i,m+1,n){
        if(can[i]){
            ans1 = (ans1 + cnt[i]) % MOD;
            ans2++;
        }
    }

    cout<<ans1<<' '<<ans2<<endl;
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
