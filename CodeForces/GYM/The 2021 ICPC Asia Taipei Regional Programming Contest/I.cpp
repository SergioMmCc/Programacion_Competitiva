#include<bits/stdc++.h>
using namespace std;
#define int long long
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

const int maxn = 5055;
bitset<maxn> dpa[101][101], dpb[101][101];

void calc(vi& baga, int maxa, vi& bagb, int maxb){
    int n = sz(baga) - 1;
    dpa[0][0][0] = 1;
    for1(i,n){
        dpa[i][0][0] = 1;
        for1(j,i){
            for1(k, maxa){
                dpa[i][j][k] = dpa[i-1][j][k];
                if(k >= baga[i] && dpa[i-1][j-1][k - baga[i]]) dpa[i][j][k] = 1;
            }
        }
    }

    int m = sz(bagb) - 1;
    dpb[0][0][0] = 1;
    for1(i,m){
        dpb[i][0][0] = 1;
        for1(j,i){
            for1(k, maxb){
                dpb[i][j][k] = dpb[i-1][j][k];
                if(k >= bagb[i] && dpb[i-1][j-1][k - bagb[i]]) dpb[i][j][k] = 1;
            }
        }
    }
}

void solver(){
    int n; cin>>n;
    vi a(n+1), b(n+1), ba(1), bb(1);
    int sa = 0, sb = 0, maxa = 0, maxb = 0;
    for1(i,n){
        cin>>a[i];
        sa += i * a[i];
        if(a[i] == 1){
            ba.pb(i);
            maxa += i;
        }
    }
    for1(i,n){
        cin>>b[i];
        sb += i*b[i];
        if(b[i] == 2){
            bb.pb(i);
            maxb += i;
        }
    }

    int dif = sb - sa;
    if(dif < 0 || dif > maxa + maxb){
        cout<<-1<<endl;
        return;
    }
    if(!dif){
        cout<<0<<endl;
        return;
    }

    // CLEANNNNN
    for0(i, n+1){
        for0(j, n+1){
            for0(k, maxn){
                dpa[i][j][k] = 0;
                dpb[i][j][k] = 0;
            }
        }
    }

    calc(ba, maxa, bb, maxb);

    for1(i,n){
        for0(j, dif+1){
            int k = dif - j;
            if(k >= maxn || j >= maxn) continue;
            if(dpa[sz(ba)-1][i][j] && dpb[sz(bb)-1][i][k]){
                cout<<i<<endl;
                return;
            }
        }
    }

    cout<<-1<<endl;
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
