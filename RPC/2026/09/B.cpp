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

vi dy = {1, -1, 0, 0};
vi dx = {0, 0, 1, -1};

void solver(int n, int m){
    vs a(n);
    for0(i,n) cin>>a[i];

    int sy, sx;
    for0(i,n){
        for0(j,m){
            if(a[i][j] == '*'){
                sy = i;
                sx = j;
            }
        }
    }

    int cnt = 1;
    vector<vb> vis(n, vb(m)); vis[sy][sx] = 1;
    queue<pii> q; q.push({sy, sx});
    while(!q.empty()){
        int uy = q.front().fi, ux = q.front().se; q.pop();
        for0(i, 4){
            int vy = uy + dy[i], vx = ux + dx[i];
            if(vy < 0 || vy >= n || vx < 0 || vx >= m || vis[vy][vx] || a[vy][vx] == '#') continue;
            cnt++;
            vis[vy][vx] = 1;
            q.push({vy, vx});
        }
    }

    cout<<cnt<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int n, m; 
    while(1){
        cin>>n>>m;
        if(!n) break;
        solver(n, m);
    }

    return 0;
}
