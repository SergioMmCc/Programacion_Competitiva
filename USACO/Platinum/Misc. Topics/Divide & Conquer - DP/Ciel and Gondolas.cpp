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

const int maxn = 4e3 + 1, maxk = 800 + 1;
int C[maxn][maxn]; // se quita si se puede hallar facil para cada m,j
int dp[maxk][maxn];

int a[maxn][maxn];
int s[maxn][maxn];

void calc(int n){
    for1(i,n){
        for1(j,n){
            cin>>a[i][j];
            s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        }
    }
}

void compute(int k, int l, int r, int optl, int optr){
    if(l > r) return;
    int mid = (l+r) >> 1, opt = -1, best = INF;
    for(int m = optl; m <= min(mid, optr); m++){
        int aux = dp[k-1][m-1] + C[m][mid];
        if(aux < best){
            best = aux;
            opt = m;
        }
    }
    dp[k][mid] = best;
    compute(k, l,     mid-1, optl, opt);  // j menores: opt a la izquierda
    compute(k, mid+1, r,     opt,  optr); // j mayores: opt a la derecha
}

void solver(){
    int n, k; cin>>n>>k;
    calc(n);
    for1(m,n) forlr(j,m,n) C[m][j] = (s[j][j] - 2*s[m-1][j] + s[m-1][m-1]) >> 1;

    for0(j,n+1) dp[0][j] = INF; // No se pueden partir en 0 grupos
    dp[0][0] = 0; // 0 elementos si se pueden partir en 0 grupos
    for1(i,k){ // Hallar el dp para 'i' grupos
        for0(j,n+1) dp[i][j] = INF; // Inicializar en INF
        compute(i, i, n, i, n);
    }
    
    cout<<dp[k][n]<<endl;
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