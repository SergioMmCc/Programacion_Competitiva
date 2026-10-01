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

const ll INFL = 1'000'000'000'000'000'001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

const int maxn = 752;
ll d[maxn][maxn]; // d[i][j] = Longitud de la ruta mas corta desde i hasta j
ll upd[maxn][maxn];

void solver(){
    // cout<<INFL<<endl;
    int n; cin>>n;
    for1(i,n){
        for1(j,n){
            cin>>d[i][j];
            if(d[i][j] == -1) d[i][j] = INFL;
        }
    }

    int q; cin>>q;
    while(q--){
        int i, j, x, y; ll k; cin>>i>>j>>x>>y>>k;
        if(x < i) swap(i, x);
        if(y < j) swap(j, y);
        forlr(idx,i,x){
            upd[idx][j] += k;
            upd[idx][y+1] -= k;
        }
    }

    for1(i,n){
        for1(j,n){
            upd[i][j] += upd[i][j-1];
            if(d[i][j] && d[i][j] != INFL) d[i][j] += upd[i][j];
        }
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    cin>>q;
    while(q--){
        int a, b; cin>>a>>b;
        if(d[a][b] == INFL) cout<<-1<<endl;
        else cout<<d[a][b]<<endl;
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
