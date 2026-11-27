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
// #include<ext/pb_ds/assoc_container.hpp> // Poner arriba de #define int long long si lo hay
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

pll op(pll a, pll b){
    if(a.fi < b.fi) return a;
    if(a.fi > b.fi) return b;
    if(a.se >= b.se) return a;
    return b;
}

void solver(int n){
    vi freq(26);
    string s; getline(cin,s);
    for0(i,sz(s)) if(s[i] != ' ') freq[s[i] - 'a']++;

    vector<vll> dp(n+2, vll(27, {INFL, -1}));
    for1(i,n+1){
        dp[i][0] = {0, -1};
        for1(j,26){
            for0(k,j){
                ll sum = dp[i-1][k].fi;
                forlr(l,k,j-1) sum += (ll)(l-k+1)*freq[l];
                pll aux = {sum, k};
                dp[i][j] = op(dp[i][j], aux);
            }
        }
    }

    vi put;
    int last = 26;
    int cnt = n + 1;
    while(cnt > 2){
        last = dp[cnt][last].se;
        put.pb(last);
        cnt--;
    }

    reverse(all(put));
    int idx = 0;
    for0(i,26){
        if(idx < sz(put) && put[idx] == i){
            cout<<'|';
            idx++;
        }
        cout<<(char)(i + 'a');
    }
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    while(1){
        string aux; getline(cin, aux);
        int n = 0;
        if(sz(aux) == 2) n = (aux[1] - '0') + 10*(aux[0] - '0');
        else n = aux[0] - '0';
        if(!n) break;
        solver(n);
    }

    return 0;
}
