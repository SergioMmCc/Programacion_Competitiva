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

bool check(ll m, ll k, vl& a, vl& b, vl& c, int n){
    for0(i,n){
        if(a[i] + b[i] + c[i] >= m) continue;
        
        ll al = a[i], bl = b[i], cl = c[i];

        if(bl >= al && cl >= bl){
            if(bl - al <= cl - bl){
                k -= bl - al + 1;
                bl = al-1;
            }
            else{
                k -= cl - bl + 1;
                cl = bl-1;
            }
        }

        ll sum = al + bl + cl;
        if(k < m - sum) return 0;
        k -= m - sum;
    }

    return 1;
}

void solver(){
    int n; ll k; cin>>n>>k;
    vl a(n), b(n), c(n);

    ll ans = 2e18;
    for0(i,n){
        cin>>a[i]>>b[i]>>c[i];
        if(a[i] == b[i] && a[i] == c[i]) ans = min(ans, a[i] + b[i] + c[i]);
    }

    ll l = -2e18, r = ans;
    while(l < r){
        ll m = l + (r - l + 1) / 2;
        if(check(m, k, a, b, c, n)) l = m;
        else r = m-1;
    }

    cout<<l<<endl;
}

int main(){
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