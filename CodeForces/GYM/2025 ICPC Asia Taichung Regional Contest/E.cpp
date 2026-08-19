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

vector<vector<vi>> perms(3);
void preCalc(){
    // Solo 1
    vi perm = {1, 2};
    do{
        perms[0].pb(perm);
    } while(next_permutation(all(perm)));
    
    perm = {1, 2, 3};
    do{
        perms[1].pb(perm);
    } while(next_permutation(all(perm)));

    perm = {1, 2, 3, 4};
    do{
        perms[2].pb(perm);
    } while(next_permutation(all(perm)));
}

void solver(){
    int n, i, j; cin>>n>>i>>j; i--; j--;
    if(n == 12) n = 0;
    else if(n == 123) n = 1;
    else n = 2;

    int c1 = 0;
    for0(k,n+2) if(perms[n][i][k] == perms[n][j][k]) c1++;

    cout<<c1<<'A'<<n-c1+2<<'B'<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    preCalc();
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
