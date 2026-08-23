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

const int maxn = 200005;
int components;
vector<int> leader(maxn);
vector<int> sets[maxn];
vector<vi> graph(maxn);
vi color(maxn);

struct edge {
    int u, v, w;

    // Ordenar las aristas por el menor peso
    bool operator<(const edge& that) const {
        return w > that.w; // Cambiar '<' por '>' para hallar el Maximal Spanning Tree
    }
};

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sets[i].push_back(i);
    }
}

void join(int u, int v){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        if(sets[leaderV].size() > sets[leaderU].size())
            swap(leaderU, leaderV);
        
        for(int i = 0; i < sets[leaderV].size(); i++){
            int v = sets[leaderV][i];
            leader[v] = leaderU;
            sets[leaderU].push_back(v);
        }
        sets[leaderV].clear();
        components--;
    }
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    vector<edge> edj;
    for0(i,m){
        int u, v, w; cin>>u>>v>>w;
        edj.pb({u,v,w});
    }
    sort(all(edj));

    int ans = 0;
    for0(i,m){
        int w = edj[i].w;
        int j = i;
        vi vs;
        vector<edge> pro;
        while(j < m && edj[j].w == w){
            int u = leader[edj[j].u], v = leader[edj[j].v];
            if(u == v){
                cout<<"impossible"<<endl;
                return;
            }
            pro.pb({u,v,w});
            vs.pb(u); vs.pb(v);
            graph[u].pb(v);
            graph[v].pb(u);
            j++;
        }
        i=j-1;

        for(int x : vs){
            if(color[x]) continue;
            int s1 = 0, s2 = 0;
            queue<int> q; q.push(x);
            color[x] = 1;
            s1 += sz(sets[x]);
            while(!q.empty()){
                int u = q.front(); q.pop();
                for(int v : graph[u]){
                    if(color[v]){
                        if(color[u] == color[v]){
                            cout<<"impossible"<<endl;
                            return;
                        }
                        continue;
                    }
                    if(color[u] == 1){
                        color[v] = 2;
                        s2 += sz(sets[v]);
                    }
                    else{
                        color[v] = 1;
                        s1 += sz(sets[v]);
                    }
                    q.push(v);
                }
            }

            ans += min(s1, s2);
        }

        for(auto e : pro) join(e.u, e.v);
        for(int x : vs){
            graph[x].clear();
            color[x] = 0;
        }
        
    }

    cout<<"possible"<<endl<<ans<<endl;
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
