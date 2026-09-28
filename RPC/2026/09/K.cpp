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
typedef pair<int, ll> pil;
typedef pair<pii, ll> piil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

const int maxn = 1e5 + 1;
const ll inf = 1e15;
vector<multiset<pil>> graph(maxn);

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int s, int d, int n, int k){
    for1(i,k){
        vl dis(n+1, inf); vector<pil> pa(n+1);
        dis[s] = 0;
        priority_queue<pil, vector<pil>, comp> pq;
        pq.push({s, 0});
        while(!pq.empty()){
            int u = pq.top().fi; ll w1 = pq.top().se;
            pq.pop();
            if(dis[u] < w1) continue;
            for(pil e : graph[u]){
                int v = e.fi; ll w2 = e.se;
                if(dis[v] > w1 + w2){
                    dis[v] = w1 + w2;
                    pa[v] = {u, w2};
                    pq.push({v, dis[v]});
                }
            }
        }

        vector<piil> edj;
        int a = d;
        while(pa[a].fi){
            edj.pb({{a, pa[a].fi}, pa[a].se});
            a = pa[a].fi;
        }

        if(i < k){
            for(piil e : edj){
                int u = e.fi.fi, v = e.fi.se; ll w = e.se;
                graph[u].erase(graph[u].find({v, w}));
                graph[v].erase(graph[v].find({u, w}));
            }
        }
        else{
            cout<<dis[d]<<endl;
            cout<<s;
            reverse(all(edj));
            for(piil e : edj){
                cout<<" - "<<e.fi.fi;
            }
            cout<<endl;
        }
    }
}

void solver(){
    int n, m, k, s, d; cin>>n>>m>>k>>s>>d;
    for0(i,m){
        int u, v; ll w; cin>>u>>v>>w;
        graph[u].insert({v, w});
        graph[v].insert({u, w});
    }

    dijkstra(s, d, n, k);
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
