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

vi dx = {1, -1, 0, 0, 0};
vi dy = {0, 0, 1, -1, 0};

void solver(){
    int m, n; cin>>m>>n;
    vector<vi> maze(n, vi(m));
    for0(i,n){
        for0(j,m){
            cin>>maze[i][j];
        }
    }

    vector<vector<vb>> vis(n, vector<vb>(m, vb(840)));
    int stx, sty; cin>>stx>>sty;
    vis[sty][stx][0] = 1;
    queue<pair<pii, int>> q; q.push({{sty, stx}, 0});

    int g; cin>>g;
    vector<vector<vii>> wh(n, vector<vii>(m));
    for0(i,g){
        int len; cin>>len;
        for0(j,len){
            int x, y; cin>>x>>y;
            wh[y][x].pb({len, j});
        }
    }

    while(!q.empty()){
        int i = q.front().fi.fi, j = q.front().fi.se, k = q.front().se; q.pop();
        for0(d, 5){
            int y = i + dy[d], x = j + dx[d];
            if(y < 0 || x < 0 || y >= n || x >= m || maze[y][x] > maze[i][j] || vis[y][x][(k+1) % 840]) continue;
            bool can = 1;
            for(pii &gu : wh[y][x]){
                if((k+1) % gu.fi == gu.se || k % gu.fi == gu.se){
                    can = 0;
                    break;
                }
            }
            if(can){
                if(!maze[y][x]){
                    cout<<k+1<<endl;
                    return;
                }
                vis[y][x][(k+1)%840] = 1;
                q.push({{y, x}, k+1});
            }
        }
    }

    cout<<-1<<endl;
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
