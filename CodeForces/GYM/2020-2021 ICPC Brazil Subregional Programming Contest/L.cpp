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

void solver(){
    int n, m; cin>>n>>m;
    vs a(n);
    for0(i,n) cin>>a[i];

    vector<vi> esp(n, vi(m));
    int q; cin>>q;
    while(q--){
        string s; cin>>s;
        vi anag(26);
        int len = sz(s);
        for0(i,len) anag[s[i] - 'A']++;
        vector<vb> add(n, vb(m));

        for0(i,n){
            for0(j,m){
                int r = i, c = j;
                
                // A la derecha
                if(c + len <= m){
                    vi aux(26);
                    forlr(x,c,c+len-1) aux[a[i][x] - 'A']++;
                    if(aux == anag) forlr(x,c,c+len-1) add[i][x] = 1;
                }

                // Abajo
                if(r + len <= n){
                    vi aux(26);
                    forlr(y,r,r+len-1) aux[a[y][j] - 'A']++;
                    if(aux == anag) forlr(y,r,r+len-1) add[y][c] = 1;
                }

                // Abajo y a la derecha
                if(r + len <= n && c + len <= m){
                    vi aux(26);
                    for(int y = r, x = c; y < r+len && x < c+len; y++, x++) aux[a[y][x] - 'A']++;
                    if(aux == anag) for(int y = r, x = c; y < r+len && x < c+len; y++, x++) add[y][x] = 1;
                }

                // Arriba y a la deerecha
                if(r - len + 1 >= 0 && c + len <= m){
                    vi aux(26);
                    for(int y = r, x = c; y > r-len && x < c+len; y--, x++) aux[a[y][x] - 'A']++;
                    if(aux == anag) for(int y = r, x = c; y > r-len && x < c+len; y--, x++) add[y][x] = 1;
                }
            }
        }

        for0(i,n){
            for0(j,m){
                if(add[i][j]){
                    esp[i][j]++;
                }
            }
        }
    }

    int ans = 0;
    for0(i,n){
        for0(j,m){
            if(esp[i][j] >= 2){
                ans++;
            }
        }
    }

    cout<<ans<<endl;
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
