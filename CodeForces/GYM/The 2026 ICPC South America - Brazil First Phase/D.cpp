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

void rotate(vs& b){
    int n = sz(b), m = sz(b[0]);
    vs c(m);
    for0(i,m){
        for0(j,n){
            c[i] += ' ';
        }
    }

    for0(i,n){
        for0(j,m){
            c[j][n-i-1] = b[i][j];
        }
    }

    b = c;
}

vs flip(vs& b){
    int n = sz(b), m = sz(b[0]);
    vs c(n);
    for0(i,n){
        for0(j,m){
            c[i] += ' ';
        }
    }

    for0(i,n){
        for0(j,m){
            c[i][j] = b[i][m-j-1];
        }
    }

    return c;   
}

void solver(){
    int n, m; cin>>n>>m;
    vs a(n), b(n);
    for0(i,n){
        cin>>a[i];
        b[i] = a[i];
    }

    int ans = 0;
    for0(i,4){
        rotate(b);
        if(sz(b) == sz(a) && sz(a[0]) == sz(b[0])){
            if(b == a) ans++;
            vs c = flip(b);
            if(c == a) ans++;
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
