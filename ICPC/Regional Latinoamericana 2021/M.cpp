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
typedef pair<pll, int> plli;
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
    int n; cin>>n;
    vector<plli> a(n);
    for0(i,n){
        cin>>a[i].fi.se>>a[i].fi.fi;
        a[i].se = i;
    }

    sort(all(a));
    ll sum = 0;
    for0(i,n){
        sum += a[i].fi.se;
        if(sum > a[i].fi.fi){
            cout<<'*'<<endl;
            return;
        }

        a[i].fi.fi -= sum;
    }

    vi ans;
    for0(j,n){
        int idx = 0;
        ll mini = INFL;
        for0(i,sz(a)){
            if(a[i].fi.se <= mini && a[i].se < a[idx].se) idx = i;
            mini = min(mini, a[i].fi.fi);
        }

        ans.pb(a[idx].se + 1);
        for0(i,idx) a[i].fi.fi -= a[idx].fi.se;
        a.erase(a.begin() + idx);
    }

    for(int x : ans) cout<<x<<' ';
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
