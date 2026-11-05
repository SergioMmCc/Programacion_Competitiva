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

/*
DP con optimizacion de Knuth, pasa de O(n^3) a O(n^2).
- Es un caso especial de DP en rangos, se aplica en 
  transiciones de la forma:
  * dp[l][r] = C[l][r] + min(dp[l][i] + dp[i+1][r]), 
  * con l <= i < r.
  * 'C' es una funcion de costos.
CONDICION:
- Sea opt[l][r] el menor valor de 'i' que minimiza 
  dp[l][r], se debe cumplir que: 
  opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
- Dicha condicion se cumple cuando la funcion de costo
  'C' satisface que para todo a <= b <= c <= d:
  * C[b][c] <= C[a][d].
  * C[a][c] + C[b][d] <= C[a][d] + C[b][c].
- Sin embargo usualmente no se hace la demostracion 
  sino que se intuye o compara contra una solucion 
  O(n^3) en un caso pequeño.
  
- 0-index.
MAXIMIZAR
- Para toda la tabla C hacer C[i][j] *= -1. Esta tabla 
  'C' negada es la que debe cumplir las condiciones.
- Al resultado final tambien hacerle *= -1.
*/

const int maxn = 1e3 + 5;
ll dp[maxn][maxn], C[maxn][maxn];
int opt[maxn][maxn];

void solver(int n, int m){
    vi p(m+2);
    for1(i,m) cin>>p[i];
    p[m+1] = n;
    m++;
    
    for0(l,m){
        forlr(r,l,m-1){
            C[l][r] = p[r+1] - p[l];
        }
        for0(r,m) dp[l][r] = INFL, opt[l][r] = 0;
    }
    
    for0(i,m) dp[i][i] = 0, opt[i][i] = i; // Para rango 'i' unico
    
    forlr(len,2,m){
        forlr(l,0,m-len){
            int r = l+len-1;
            dp[l][r] = INFL;
            int lo = opt[l][r-1], hi = min(opt[l+1][r], r-1);
            forlr(i,lo,hi){
                ll cur = dp[l][i] + dp[i+1][r];
                if(cur < dp[l][r]){
                    dp[l][r] = cur;
                    opt[l][r] = i;
                }
            }
            dp[l][r] += C[l][r];
        }
    }
    cout<<dp[0][m-1]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    int n, m;
    while(cin>>n>>m){
        solver(n, m);
    }

    return 0;
}