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
    int n, x; cin>>n>>x;
    vl cnt(x);
    vii a;
    for0(i,n){
        int st, en; cin>>st>>en; en += st;
        if(st <= 480 && en > 480){
            a.pb({st, 480});
            a.pb({481, en});
        }
        else a.pb({st, en});
    }

    sort(all(a));
    while(!a.empty() && a.back().fi > 480){
        int st = a.back().fi % x, en = a.back().se % x, dic = (a.back().se - a.back().fi + x) / x, dif = (a.back().se - a.back().fi + 1) / x;
        if(en >= st){
            forlr(i,st,en) cnt[i] += (ll)dic;
            forlr(i,en+1,x-1) cnt[i] += (ll)dif;
            for0(i,st) cnt[i] += (ll)dif;
        }
        else{
            forlr(i,st,x-1) cnt[i] += (ll)dic;
            for0(i,en+1) cnt[i] += (ll)dic;
            forlr(i,en+1, st-1) cnt[i] += (ll)dif;
        }
        a.pop_back();
    }

    pair<ll, int> ans = {INFL, 481};
    forn0(i,481){
        for(pii aux : a) if(aux.fi <= i && aux.se >= i) cnt[i % x]++;
        pair<ll, int> cmp = {cnt[i % x], i};
        ans = min(ans, cmp);
    }

    cout<<ans.se<<' '<<ans.fi<<endl;
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
