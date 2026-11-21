#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
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

ll cmp(ll a, ll b, ll c){
    return max(a, max(b, c));
}

void solver(){
    int n; cin>>n;
    vl a(n+1);
    for1(i,n) cin>>a[i];
    vl ps(n+1), ss(n+2);
    for1(i,n) ps[i] = ps[i-1] + a[i];
    forn1(i,n) ss[i] = ss[i+1] + a[i];
    // for1(i,n) cout<<ps[i]<<' '; cout<<endl;
    // for1(i,n) cout<<ss[i]<<' '; cout<<endl;

    if(n == 2){
        cout<<ps[n]<<endl;
        return;
    }

    ll ans = cmp(a[1] + a[n], ps[n-1], ss[2]);
    if(ans == a[1] + a[n]){
        cout<<ans<<endl;
        return;
    }
    // cout<<"primer ans -> "<<ans<<endl;
    for1(l,n-1){
        // if(ps[l] + a[n] >= max(ss[l+1], ps[n-1])){
        //     ans = min(ans, cmp(ps[l] + a[n], ss[l+1], ps[n-1]));
        //     // break;
        // }
        int lo = l+1, hi = n;
        while(lo < hi){
            int r = (lo + hi) / 2;
            if(ps[l] + ss[r] >= max(ps[r-1], ss[l+1])) lo = r+1;
            else hi = r;
        }

        ans = min(ans, cmp(ps[l] + ss[lo], ps[lo-1], ss[l+1]));
        lo--;
        if(lo > l) ans = min(ans, cmp(ps[l] + ss[lo], ps[lo-1], ss[l+1]));
        // cout<<"l -> "<<l<<" ans -> "<<ans<<" lo -> "<<lo<<endl;
    }
    cout<<ans<<endl;
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
