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
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

vi dy = {1, -1, 0, 0};
vi dx = {0, 0, 1, -1};

pii BFS(int sy, int sx, int n, int m, vs& a){
    // db(sy); db(sx);
    vector<vi> dis(n, vi(m));
    vector<vb> vis(n, vb(m));
    vis[sy][sx] = 1;
    queue<pii> q; q.push({sy, sx});
    piii bigg = {0, {sy, sx}};
    while(!q.empty()){
        int uy = q.front().fi, ux = q.front().se; q.pop();
        for0(i,4){
            int vy = uy + dy[i], vx = ux + dx[i];
            if(vy < 0 || vy >= n || vx < 0 || vx >= m || vis[vy][vx] || a[vy][vx] == '#') continue;
            vis[vy][vx] = 1;
            dis[vy][vx] = dis[uy][ux] + 1;
            bigg = max(bigg, {dis[vy][vx], {vy, vx}});
            q.push({vy, vx});
        }
    }

    sy = bigg.se.fi, sx = bigg.se.se;
    // db(sy); db(sx);
    for0(i,n){
        for0(j,m){
            dis[i][j] = 0;
            vis[i][j] = 0;
        }
    }
    vector<vii> pa(n, vii(m, {-1,-1}));
    vis[sy][sx] = 1;
    q.push({sy, sx});
    bigg = {0, {sy, sx}};
    while(!q.empty()){
        int uy = q.front().fi, ux = q.front().se; q.pop();
        for0(i,4){
            int vy = uy + dy[i], vx = ux + dx[i];
            if(vy < 0 || vy >= n || vx < 0 || vx >= m || vis[vy][vx] || a[vy][vx] == '#') continue;
            vis[vy][vx] = 1;
            pa[vy][vx] = {uy, ux};
            dis[vy][vx] = dis[uy][ux] + 1;
            bigg = max(bigg, {dis[vy][vx], {vy, vx}});
            q.push({vy, vx});
        }
    }

    int dia = bigg.fi;
    int uy = bigg.se.fi, ux = bigg.se.se;
    for0(i,dia/2){
        int aux = uy;
        uy = pa[uy][ux].fi;
        ux = pa[aux][ux].se;
    }

    if(dia % 2 == 0) return {uy, ux};
    int vy = pa[uy][ux].fi, vx = pa[uy][ux].se;

    if(ux < vx) return {uy, ux};
    if(ux > vx) return {vy, vx};
    if(uy <= vy) return {uy, ux};
    return {vy, vx};


    return {1, 1};
}

pii solver(){
    int n, m; cin>>n>>m;
    vs a(n);
    for0(i,n){
        cin>>a[i];
    }

    int sy = 0, sx = 0;
    for0(i,n){
        for0(j,m){
            if(a[i][j] == '.'){
                sy = i; sx = j;
                break;
            }
        }
    }

    pii ans = BFS(sy, sx, n, m, a);
    ans.fi++;
    ans.se++;
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    cin>>t;
    for1(i,t){
        pii ans = solver();
        cout<<"Case "<<i<<": "<<ans.fi<<' '<<ans.se<<endl;
    }

    return 0;
}
