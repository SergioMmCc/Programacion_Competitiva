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
typedef pair<int, pii> piii;
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
    int n, x; cin>>n>>x;
    vi m(n+1);
    vector<vi> a(n+1), b(n+1), p(n+1), ml(n+1), cl(n+1);
    vector<vb> si(n+1);
    pqueue<piii, vector<piii>, greater<piii>> pq;
    for1(i,n){
        cin>>m[i];
        a[i].pb(0); b[i].pb(0); p[i].pb(0); ml[i].pb(0); cl[i].pb(0); si[i].pb(0);
        for1(j,m[i]){
            int num; cin>>num;
            a[i].pb(num);
        }
        for1(j,m[i]){
            int num; cin>>num;
            b[i].pb(num);
            p[i].pb(b[i][j] - a[i][j]);
            cl[i].pb(a[i][j] + cl[i][j-1] - b[i][j-1]);
            ml[i].pb(max(ml[i][j-1], max(a[i][j], cl[i][j])));
            si[i].pb(0);
            if(!si[i][j-1]){
                p[i][j] += p[i][j-1];
            }
            if(p[i][j] >= 0){
                si[i][j] = 1;
                pq.push({ml[i][j], {i, j}});
            }
        }
    }
    vi wh(n+1,1);
    while(!pq.empty()){
        int need = pq.top().fi, i = pq.top().se.fi, j = pq.top().se.se; pq.pop();
        if(need > x) break;
        x += p[i][j];
        wh[i] = j+1;
    }

    pii ans = {0,1};
    forn1(i,n){
        if(wh[i]-1 >= ans.fi) ans = {wh[i]-1,i};
        ll take = 0;
        forlr(j,wh[i],m[i]){
            take += a[i][j];
            if(take <= x){
                if(j >= ans.fi){ ans = {j,i};}
                take -= b[i][j];
            }
            else{ break;}
        }
    }

    cout<<ans.fi<<' '<<ans.se<<endl;
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
