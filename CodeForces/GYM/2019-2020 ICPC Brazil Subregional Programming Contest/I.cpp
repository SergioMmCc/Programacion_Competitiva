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
typedef pair<pii, pii> piiii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<piiii> viiii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

vector<vi> dis(401, vi(401, INF)), graf(401, vi(401, INF));

void solver(){
    int n, m; cin>>n>>m;
    for1(i,n) graf[i][i] = dis[i][i] = 0;
    vii a(n);
    for0(i,n){
        cin>>a[i].fi;
        a[i].se = i+1;
    }

    sort(all(a));


    for0(i,m){
        int u, v, d; cin>>u>>v>>d;
        graf[u][v] = graf[v][u] = dis[u][v] = dis[v][u] = d;
    }

    int q; cin>>q;
    viiii qord, qrev;
    for0(i,q){
        int u, v, k, t; cin>>u>>v>>k>>t;
        if(!t) qord.pb({{k, i}, {u, v}});
        else qrev.pb({{k, i}, {u, v}});
    }
    
    vi ans(q);
    int add = 0, jdx = 0;

    sort(all(qord));
    for(auto x : qord){
        int k = x.fi.fi, idx = x.fi.se, u = x.se.fi, v = x.se.se;
        while(add < k && jdx < n){
            int node = a[jdx].se;

            for1(i,n){
                for1(j,n){
                    dis[i][j] = min(dis[i][j], dis[i][node] + dis[node][j]);
                }
            }

            if(jdx < n-1 && a[jdx].fi != a[jdx+1].fi) add++;
            jdx++;
        }

        if(dis[u][v] == INF) ans[idx] = -1;
        else ans[idx] = dis[u][v];
    }

    // Limpiar distancias, y add
    for1(i,n){
        for1(j,n){
            dis[i][j] = graf[i][j];
        }
        dis[i][i] = 0;
    }
    add = 0; jdx = 0;

    reverse(all(a));
    swap(qord,qrev);
    
    sort(all(qord));
    for(auto x : qord){
        int k = x.fi.fi, idx = x.fi.se, u = x.se.fi, v = x.se.se;
        while(add < k && jdx < n){
            int node = a[jdx].se;

            for1(i,n){
                for1(j,n){
                    dis[i][j] = min(dis[i][j], dis[i][node] + dis[node][j]);
                }
            }
            
            if(jdx < n-1 && a[jdx].fi != a[jdx+1].fi) add++;
            jdx++;
        }

        if(dis[u][v] == INF) ans[idx] = -1;
        else ans[idx] = dis[u][v];
    }

    for0(i,q) cout<<ans[i]<<endl;
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
