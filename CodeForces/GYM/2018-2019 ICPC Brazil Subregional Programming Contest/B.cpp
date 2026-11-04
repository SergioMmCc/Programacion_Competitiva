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

vector<vi> save(101, vi(101));
void calc(){
    for1(i,100){
        for1(j,100){
            if(i == j) continue;
            vb mex(302);

            for1(k,i-1) if(k != j) mex[save[k][j]] = 1;
            for1(k,j-1) if(k != i) mex[save[i][k]] = 1;
            for1(k,min(i,j)-1) mex[save[i-k][j-k]] = 1;

            for0(k,302){
                if(!mex[k]){
                    save[i][j] = k;
                    break;
                }
            }
        }
    }
}

void solver(){
    int n; cin>>n;
    int ans = 0;
    bool cond = 0;
    for0(i,n){
        int x, y; cin>>x>>y;
        ans ^= save[x][y];
        if(x == y) cond = 1;
    }
    cout<<(ans || cond ? 'Y' : 'N')<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calc();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
