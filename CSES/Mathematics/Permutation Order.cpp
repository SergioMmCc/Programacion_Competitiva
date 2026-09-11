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
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

vl fact(21);
void calcFact(){
    fact[0] = 1;
    for1(i,20) fact[i] = fact[i-1] * (ll)i;
}

void solver(){
    int op, n; cin>>op>>n;
    indexed_set nums;
    for1(i,n) nums.insert(i);
    if(op == 1){
        ll f = fact[n-1];
        ll idx; cin>>idx;
        vi ans;
        while(n){
            int take = (idx - 1) / f;
            idx -= (ll)take * f;
            ans.pb(*nums.find_by_order(take));
            nums.erase(ans.back());
            n--;
            if(n) f /= n;
        }

        for(int x : ans) cout<<x<<' ';
        cout<<endl;
    }
    else{
        vi a(n);
        for0(i,n) cin>>a[i];
        ll idx = 1, f = fact[n-1]; 
        int len = n;
        for0(i,n){
            int jdx = nums.order_of_key(a[i]);
            idx += f * (ll)jdx;
            len--;
            if(len) f /= (ll)len;
            nums.erase(nums.find_by_order(jdx));
        }

        cout<<idx<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calcFact();
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
