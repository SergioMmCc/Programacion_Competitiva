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
typedef pair<string, string> pss;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pss> vss;
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

bool check(pss a, pss b, pss c){
    if((((a.fi[0] == b.fi[0] && a.fi[0] == c.fi[0]) || (a.fi[0] != b.fi[0] && a.fi[0] != c.fi[0] && b.fi[0] != c.fi[0])) &&
       ((a.fi[1] == b.fi[1] && a.fi[1] == c.fi[1]) || (a.fi[1] != b.fi[1] && a.fi[1] != c.fi[1] && b.fi[1] != c.fi[1])) &&
       ((a.fi[2] == b.fi[2] && a.fi[2] == c.fi[2]) || (a.fi[2] != b.fi[2] && a.fi[2] != c.fi[2] && b.fi[2] != c.fi[2])) &&
       ((a.fi[3] == b.fi[3] && a.fi[3] == c.fi[3]) || (a.fi[3] != b.fi[3] && a.fi[3] != c.fi[3] && b.fi[3] != c.fi[3]))) &&
      
      (((a.se[0] == b.se[0] && a.se[0] == c.se[0]) || (a.se[0] != b.se[0] && a.se[0] != c.se[0] && b.se[0] != c.se[0])) &&
       ((a.se[1] == b.se[1] && a.se[1] == c.se[1]) || (a.se[1] != b.se[1] && a.se[1] != c.se[1] && b.se[1] != c.se[1])) &&
       ((a.se[2] == b.se[2] && a.se[2] == c.se[2]) || (a.se[2] != b.se[2] && a.se[2] != c.se[2] && b.se[2] != c.se[2])) &&
       ((a.se[3] == b.se[3] && a.se[3] == c.se[3]) || (a.se[3] != b.se[3] && a.se[3] != c.se[3] && b.se[3] != c.se[3])))) return 1;
    return 0;
}

void solver(){
    int n; cin>>n;
    vss a(n);
    for0(i,n) cin>>a[i].fi>>a[i].se;

    int ans = 0;
    for0(i,n-2){
        forlr(j,i+1,n-2){
            forlr(k,j+1,n-1){
                if(check(a[i], a[j], a[k])){
                    ans++;
                    continue;
                }
                swap(a[i].fi, a[i].se);
                if(check(a[i], a[j], a[k])){
                    swap(a[i].fi, a[i].se);
                    ans++;
                    continue;
                }
                swap(a[i].fi, a[i].se);
                swap(a[j].fi, a[j].se);

                if(check(a[i], a[j], a[k])){
                    swap(a[j].fi, a[j].se);
                    ans++;
                    continue;
                }
                swap(a[j].fi, a[j].se);
                swap(a[k].fi, a[k].se);

                if(check(a[i], a[j], a[k])){
                    swap(a[k].fi, a[k].se);
                    ans++;
                    continue;
                }
                swap(a[k].fi, a[k].se);
            }
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
