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

bool isdif(string aux){
    if(aux[0] != aux[1] && aux[0] != aux[2] && aux[1] != aux[2]) return 1;
    return 0;
}

void solver(){
    string s; cin>>s;
    int n = sz(s);
    vector<vb> dp(n, vb(n));
    for0(i,n-2){
        string aux = "";
        aux += s[i];
        aux += s[i+1];
        aux += s[i+2];
        dp[i][i+2] = isdif(aux);
    }

    for(int len = 6; len <= n; len += 3){
        for(int i = 0; i + len <= n; i++){
            int j = i + len - 1;
            string aux = "";
            aux += s[i]; aux += s[i+1]; aux += s[j];
            if(isdif(aux) && dp[i+2][j-1]){
                dp[i][j] = 1;
                continue;
            }
            aux = "";
            aux += s[i]; aux += s[j-1]; aux += s[j];
            if(isdif(aux) && dp[i+1][j-2]){
                dp[i][j] = 1;
                continue;
            }

            for(int k = i+3; k < j; k += 3){
                if(dp[i][k-1] && dp[k][j]){
                    dp[i][j] = 1;
                    break;
                }
            }
            if(dp[i][j] || len == 6) continue;

            aux = "";
            aux += s[i]; aux += s[j];
            for(int k = i+4; k < j; k += 3){
                aux += s[k];
                if(dp[i+1][k-1] && dp[k+1][j-1] && isdif(aux)){
                    dp[i][j] = 1;
                    break;
                }
                aux.pop_back();
            }
        }
    }

    cout<<(dp[0][n-1] ? 'S' : 'N')<<endl;
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
