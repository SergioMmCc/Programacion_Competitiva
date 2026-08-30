#include<bits/stdc++.h>
using namespace std;
#define int long long
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
typedef pair<pii, pii> piiii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<piiii> viiii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void compressArr(vi& y, viiii& a){
    sort(all(y));
    y.erase(unique(all(y)), y.end());
    for0(i,sz(a)){
        a[i].fi.se = lb(all(y), a[i].fi.se) - y.begin();
        a[i].se.se = lb(all(y), a[i].se.se) - y.begin();
    }
}

void solver(){
    int n; cin>>n;
    viiii a(n);
    vi col(n), y;
    vii x;
    for0(i,n){
        int x1, x2, y1, y2, c; cin>>x1>>y2>>x2>>y1>>c;
        a[i] = {{x1, y1}, {x2, y2}};
        col[i] = c;
        x.pb({x1, i}); x.pb({x2, i});
        y.pb(y1); y.pb(y2);
    }

    compressArr(y, a);
    sort(all(x));

    vb ans(n+1);
    vb is(n);
    set<int> aux;
    for0(i,sz(y)){
        for0(j,sz(x)){
            if(a[x[j].se].fi.se > i || a[x[j].se].se.se <= i) continue;
            int coord = x[j].fi;
            int k = j;
            while(k < sz(x) && x[k].fi == coord){
                int idx = x[k].se;
                if(a[idx].fi.se > i || a[idx].se.se <= i){
                    k++;
                    continue;  
                }
                if(is[idx]){
                    is[idx] = 0;
                    aux.erase(idx);
                }
                else{
                    is[idx] = 1;
                    aux.insert(idx);
                }
                k++;
            }
            j = k-1;

            if(!aux.empty()) ans[col[*aux.rbegin()]] = 1;
        }
    }

    int cnt = 0;
    for1(i,n) if(ans[i]) cnt++;
    cout<<cnt<<endl;
}

signed main(){
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
