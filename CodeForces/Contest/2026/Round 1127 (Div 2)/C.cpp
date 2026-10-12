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

bool check(int m, int n, vi& a){
    int idx = 1;
    forn1(i,m){
        int x = m / i;
        for0(j,x){
            for0(k,i){
                a.pb(idx);
                if(sz(a) == n) return 1;
            }
            idx++;
            if(idx > n) return 0;
        }
    }

    return 0;
}

void solver(){
    int n; cin>>n;
    if(n == 1){
        cout<<1<<endl<<1<<endl;
        return;
    }
    if(n == 2){
        cout<<2<<endl<<"1 2"<<endl;
        return;
    }
    
    int l = 1, r = n;
    vi ans;
    while(l < r){
        int m = (l+r) / 2;
        vi a;
        if(check(m, n, a)){
            r = m;
            ans = a;
        }
        else l = m+1;
    }

    cout<<l<<endl;
    for(int x : ans) cout<<x<<' ';
    cout<<endl;
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
