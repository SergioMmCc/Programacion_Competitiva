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
// #include<ext/pb_ds/assoc_container.hpp> // Poner arriba de #define int long long si lo hay
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

bool toposort(vi& use, vector<vi>& graf, vi& inDegree){
    int cnt = 0;
    queue<int> q;
    for(int u : use){
        if(!inDegree[u]){
            q.push(u);
            cnt++;
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graf[u]){
            inDegree[v]--;
            if(!inDegree[v]){
                cnt++;
                q.push(v);
            }
        }
    }

    return cnt != sz(use);
}

void solver(){
    int n, m; cin>>n>>m;
    vector<vi> graf(2*n + 1), graf2(n+1), graf3(2*n + 1);
    vi inDegree(2*n + 1);
    for1(i,m){
        int u, v, c; cin>>u>>v>>c; c %= 2;
        if(c){
            graf[u].pb(v+n);
            graf[v].pb(u+n);
            inDegree[u+n]++;
            inDegree[v+n]++;
        }
        else{
            graf[u+n].pb(v);
            graf[v+n].pb(u);
            inDegree[u]++;
            inDegree[v]++;
        }
        graf2[u].pb(v);
        graf2[v].pb(u);

        graf3[u].pb(v+n);
        graf3[v+n].pb(u);
        graf3[v].pb(u+n);
        graf3[u+n].pb(v);
    }

    vb vis(2*n + 1);
    vb val(2*n + 1);
    for1(i,2*n){
        if(vis[i]) continue;
        vis[i] = 1;
        queue<int> q; q.push(i);
        vi use = {i};
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : graf3[u]){
                if(vis[v]) continue;
                vis[v] = 1;
                q.push(v);
                use.pb(v);
            }
        }

        bool cond = toposort(use, graf, inDegree);
        if(cond) for(int u : use) val[u] = 1;
        // cout<<"cond -> "<<(cond ? 1 : 0)<<endl;
        // for(int u : use) cout<<u<<' '; cout<<endl;
    }

    int ans = 0;
    vb vis2(n+1);
    for1(i,n){
        if(vis2[i]) continue;
        vis2[i] = 1;
        bool cond = val[i] || val[i+n];
        queue<int> q; q.push(i);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : graf2[u]){
                if(vis2[v]) continue;
                vis2[v] = 1;
                q.push(v);
                if(val[v] || val[v+n]) cond = 1;
            }
        }

        if(cond) ans++;
    }

    cout<<ans<<endl;
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
