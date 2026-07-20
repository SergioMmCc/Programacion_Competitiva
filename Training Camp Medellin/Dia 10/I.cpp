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
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<piii> viii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void solver(){
    int n; cin>>n;
    vl a(n), ra(n);
    for0(i,n){
        cin>>a[i];
        ra[n-i-1] = -a[i];
    }

    vl d(n+1, INF), rd(n+1, INF); d[0] = -INF; rd[0] = -INF;
    vi rv(n);
    
    // Procesar ra
    int LIS = 0;
    for0(i,n){
        auto it = lb(all(rd), ra[i]);
        int idx = distance(rd.begin(), it);
        rv[n-i-1] = idx;
        LIS = max(LIS, idx);
        rd[idx] = ra[i];
    }

    // Procesar a
    vector<vi> indices(n+1);
    vi ans(n+1);
    for0(i,n){
        auto it = lb(all(d), a[i]);
        int idx = distance(d.begin(), it);

        if(idx + rv[i] <= LIS) ans[i] = 1;
        else indices[idx].pb(i);

        d[idx] = a[i];
    }

    // Mirar si esta en todos o solo algunos
    for1(i,n){
        if(sz(indices[i]) == 1) ans[indices[i].back()] = 3;
        else for(int x : indices[i]) ans[x] = 2;
    }

    for0(i,n) cout<<ans[i];
    cout<<endl;
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
