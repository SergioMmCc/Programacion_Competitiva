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

vl mul(vl& a, vl& b){
    vl ans(sz(a) + 1);
    for0(i,sz(a)) ans[i] = a[i] * b[0];
    for0(i,sz(a)) ans[i+1] += a[i] * b[1];
    return ans;
}

void solver(){
    string s; cin>>s;
    int n = sz(s);
    vector<vl> pols;
    for1(i,n-1) if(s[i] != s[i-1]) pols.pb({-2*i - 1, 1});

    if(pols.empty()){
        cout<<0<<endl<<(s[0] == 'H' ? 1 : -1)<<endl;
        return;
    }

    vl ans = pols[0];
    if(s[n-1] == 'A') ans[0] *= -1, ans[1] *= -1;
    for1(i,sz(pols)-1){
        ans = mul(ans, pols[i]);
    }

    cout<<sz(pols)<<endl;
    reverse(all(ans));
    for0(i, sz(ans)){
        if(i) cout<<' ';
        cout<<ans[i];
    }
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
