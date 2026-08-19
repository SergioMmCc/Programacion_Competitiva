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

ll lim = 0;
vi cnt;

int num(char c){
    return c - '0';
}

bool sig(char c){
    return c == '+' || c == '*';
}

void calc(int n, int m, vs& maze){

    for0(i,n){
        for0(j,m){
            if(!sig(maze[i][j])){
                int aux = num(maze[i][j]);
                if((ll)aux <= lim) cnt[aux]++;
            }
        }
    }

    // Filas
    for0(i,n){ // Fila i
        for0(j,m){ // Empezando en la columna j
            if(sig(maze[i][j])) continue;
            ll last = 1, cur = num(maze[i][j]), sum = 0;
            forlr(k,j+1,m-1){ // Terminando en la columna k
                if(sig(maze[i][k]) && (k == m-1 || sig(maze[i][k+1]))) break;
                if(maze[i][k] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[i][k] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[i][k]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }
        }
    }

    for0(i,n){
        forn0(j,m){
            if(sig(maze[i][j])) continue;
            ll last = 1, cur = num(maze[i][j]), sum = 0;
            forrl(k,0,j-1){
                if(sig(maze[i][k]) && (k == 0 || sig(maze[i][k-1]))) break;
                if(maze[i][k] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[i][k] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[i][k]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }
        }
    }

    // Columnas
    for0(j,m){
        for0(i,n){
            if(sig(maze[i][j])) continue;
            ll last = 1, cur = num(maze[i][j]), sum = 0;
            forlr(k,i+1,n-1){
                if(sig(maze[k][j]) && (k == n-1 || sig(maze[k+1][j]))) break;
                if(maze[k][j] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[k][j] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[k][j]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }
        }
    }

    for0(j,m){
        for0(i,n){
            if(sig(maze[i][j])) continue;
            ll last = 1, cur = num(maze[i][j]), sum = 0;
            forrl(k,0,i-1){
                if(sig(maze[k][j]) && (k == 0 || sig(maze[k-1][j]))) break;
                if(maze[k][j] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[k][j] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[k][j]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }
        }
    }


    // Diagonales
    for0(i,n){
        for0(j,m){
            // ++
            if(sig(maze[i][j])) continue;
            ll last = 1, cur = num(maze[i][j]), sum = 0;
            for(int k = i+1, l = j+1; k < n && l < m; k++, l++){
                if(sig(maze[k][l]) && (k == n-1 || l == m-1 || sig(maze[k+1][l+1]))) break;
                if(maze[k][l] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[k][l] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[k][l]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }


            // +-
            last = 1, cur = num(maze[i][j]), sum = 0;
            for(int k = i+1, l = j-1; k < n && l >= 0; k++, l--){
                if(sig(maze[k][l]) && (k == n-1 || l == 0 || sig(maze[k+1][l-1]))) break;
                if(maze[k][l] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[k][l] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[k][l]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }


            // -+
            last = 1, cur = num(maze[i][j]), sum = 0;
            for(int k = i-1, l = j+1; k >= 0 && l < m; k--, l++){
                if(sig(maze[k][l]) && (k == 0 || l == m-1 || sig(maze[k-1][l+1]))) break;
                if(maze[k][l] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[k][l] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[k][l]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }


            // --
            last = 1, cur = num(maze[i][j]), sum = 0;
            for(int k = i-1, l = j-1; k >= 0 && l >= 0; k--, l--){
                if(sig(maze[k][l]) && (k == 0 || l == 0 || sig(maze[k-1][l-1]))) break;
                if(maze[k][l] == '+'){
                    sum += cur*last;
                    cur = 0;
                    last = 1;
                    continue;
                }
                if(maze[k][l] == '*'){
                    last *= cur;
                    cur = 0;
                    continue;
                }

                ll add = num(maze[k][l]);
                cur *= 10;
                cur += add;
                if(sum + cur*last > lim) break;
                cnt[sum + cur*last]++;
            }
        }
    }
}

void solver(){
    int n, m, q; cin>>n>>m>>q;
    vs a(n);
    for0(i,n) cin>>a[i];

    vi b(q);
    for0(i,q){
        cin>>b[i];
        lim = max(lim, (ll)b[i]);
    }
    cnt.resize(lim + 1);
    
    calc(n, m, a);
    for0(i, q) cout<<cnt[b[i]]<<endl;
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
