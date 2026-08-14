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

ll f(int n, int m, vl& a, vl& b, int c1, int c2){
    vb used(n+m+1);
    ll ans = 0;
    int cnt = 0;
    for0(i,c1){
        ans += a[i];
        if(a[i]) used[a[i]] = 1;
    }
    for0(i, c2){
        if(used[b[i]]){
            cnt++;
            continue;
        }

        ans += b[i];
        if(b[i]) used[b[i]] = 1;
    }

    int idx = c1, jdx = c2;
    while(cnt){
        while(used[a[idx]]) idx++;
        while(used[b[jdx]]) jdx++;

        cnt--;
        ll maxi = max(a[idx], b[jdx]);
        ans += maxi;
        if(maxi) used[maxi] = 1;
    }

    return ans;
}

void solver(){
    int n, m, x, y; cin>>n>>m>>x>>y;
    vl a(x), b(y);
    for0(i,x) cin>>a[i];
    for0(i,y) cin>>b[i];

    reverse(all(a));
    while(sz(a) < m+n) a.pb(0);
    reverse(all(b));
    while(sz(b) < m+n) b.pb(0);

    ll ans = max(f(n, m, a, b, n-1, m), f(n, m, a, b, n, m-1));
    cout<<ans<<endl;
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
