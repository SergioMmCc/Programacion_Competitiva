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

const int maxn = 7000;
vector<vi> indegree(2, vi(maxn)), mov(2);
vector<vb> win(2, vb(maxn)), lose(2, vb(maxn)), vis(2, vb(maxn));
int n;
void DFS(int u, int t){
    vis[t][u] = 1;
    for(int x : mov[t ^ 1]){
        int v = (u - x + n) % n;
        if(vis[t ^ 1][v]) continue;
        if(lose[t][u]) win[t ^ 1][v] = 1;
        else if(--indegree[t ^ 1][v] == 0) lose[t ^ 1][v] = 1;
        else continue;
        DFS(v, t ^ 1);
    }
}

void solver(){
    cin>>n;
    int k;
    cin>>k;
    for0(i,k){
        int num; cin>>num;
        mov[0].pb(num);
    }
    cin>>k;
    for0(i,k){
        int num; cin>>num;
        mov[1].pb(num);
    }

    for0(i,2){
        for1(j,n-1){
            indegree[i][j] = sz(mov[i]);
        }
    }

    lose[0][0] = lose[1][0] = 1;
    DFS(0, 0);
    DFS(0, 1);

    for0(i,2){
        for1(j,n-1){
            if(win[i][j]) cout<<"Win ";
            else if(lose[i][j]) cout<<"Lose ";
            else cout<<"Loop ";
        }
        cout<<endl;
    }
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
