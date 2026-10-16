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

vi dy = {1, -1, -2, -2};
vi dx = {-2, -2, 1, -1};

const int maxn = 15;
int f[maxn][maxn];

void calc(){
    for0(i,29){
        int y = 0, x = i;
        if(x > 14){
            y = x-14;
            x = 14;
        }
        while(y < 15 && x >= 0){
            vb mex(5);
            for0(j,4){
                int u = y + dy[j], v = x + dx[j];
                if(u < 0 || u > 14 || v < 0 || v > 14) continue;
                mex[f[u][v]] = 1;
            }

            for0(j,5){
                if(!mex[j]){
                    f[y][x] = j;
                    break;
                }
            }

            y++;
            x--;
        }
    }
}

void solver(){
    int k; cin>>k;
    int ans = 0;
    for0(i,k){
        int y, x; cin>>y>>x; y--; x--;
        ans ^= f[y][x];
    }

    cout<<(ans ? "First" : "Second")<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calc();
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
