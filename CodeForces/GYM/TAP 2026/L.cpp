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

vector<vi> graph(2e5 + 10);

int BFS01(int d, int n, vector<vi>& app){
    vector<vi> dis(2, vi(n, INF));
    deque<pii> q;
    for(int u : app[0]){
        dis[0][u] = dis[1][u] = 1;
        q.push_front({u, 0});
        q.push_front({u, 1});
    }

    while(!q.empty()){
        int u = q.front().fi, donde = q.front().se; q.pop_front();
        for(int v : graph[u]){
            int add = 0, go;
            if(v > u){
                go = 0;
                if(donde) add = 1;
            }
            else{
                go = 1;
                if(!donde) add = 1;
            }

            if(!add){
                if(dis[go][v] > dis[donde][u]){
                    dis[go][v] = dis[donde][u];
                    q.push_front({v, go});
                }
            }

            if(dis[0][v] > dis[donde][u] + 1){
                dis[0][v] = dis[donde][u] + 1;
                q.push_back({v, 0});
            }
            if(dis[1][v] > dis[donde][u] + 1){
                dis[1][v] = dis[donde][u] + 1;
                q.push_back({v, 1});
            }
        }
    }

    int ans = INF;
    for(int x : app[d]) ans = min(ans, min(dis[0][x], dis[1][x]));
    return ans;
}

void compressArr(vi& a){
    vi comp = a;
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    for0(i,sz(a)) a[i] = lb(all(comp), a[i]) - comp.begin();
}

void solver(){
    int n, m; cin>>n>>m;
    vi a(n);
    for0(i,n) cin>>a[i];
    compressArr(a);

    vector<vi> app(m+10);
    int maxx = 0;
    for0(i,n){
        app[a[i]].pb(i);
        maxx = max(a[i], maxx);
    }

    if(maxx == 0){
        cout<<1<<' '<<1<<endl;
        return;
    }

    for0(i,n){
        int num = a[i];
        if(num == maxx) continue;
        auto it = ub(all(app[num+1]), i);
        if(it != app[num+1].end()) graph[i].pb(*it);
        if(it != app[num+1].begin()){
            --it;
            graph[i].pb(*it);
        }

        if(app[num+1].back() > i) graph[i].pb(app[num+1].back());
        if(!app[num+1].empty() && app[num+1][0] < i) graph[i].pb(app[num+1][0]);
    }

    int ans = 0;
    ans = BFS01(maxx, n, app);
    cout<<maxx+1<<' '<<ans<<endl;
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
