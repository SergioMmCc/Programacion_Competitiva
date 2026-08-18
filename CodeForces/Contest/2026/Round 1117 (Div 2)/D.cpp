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

void solver(){
    ll s; int q; cin>>s>>q;

    ll r = sqrt(s);
    while(s % r) r--;

    vl a(r+1); a[0] = INFL;
    ll val = s / r;
    a[r] = val;
    for(ll i = r-1; i > 0; i--){
        if(s % i == 0) val = s/i;
        a[i] = val;
    }

    vl ps(r+1); ps[1] = a[1];
    forlr(i,2,r) ps[i] = a[i] + ps[i-1];

    while(q--){
        ll x, y; cin>>x>>y;
        ll ans = - (min(r, min(x,y)) * min(r, min(x,y)));

        ll lo = 0, hi = min(min(x,y),r);
        while(lo < hi){
            ll m = (lo + hi + 1) / 2;
            if(a[m] >= x) lo = m;
            else hi = m-1;
        }
        ans += ps[min(r,min(x,y))] - ps[lo] + lo*x;

        swap(x,y);
        lo = 0, hi = min(min(x,y),r);
        while(lo < hi){
            ll m = (lo + hi + 1) / 2;
            if(a[m] >= x) lo = m;
            else hi = m-1;
        }
        ans += ps[min(r,min(x,y))] - ps[lo] + lo*x;

        cout<<ans<<endl;
    }
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
