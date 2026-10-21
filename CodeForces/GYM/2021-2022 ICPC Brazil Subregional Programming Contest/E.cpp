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
    int n; cin>>n;
    int ans = 0;
    vii a(n);
    for0(i,n) cin>>a[i].fi>>a[i].se;
    if(a[0].se) for0(i,n) a[i].se ^= 1;

    int t = a[0].fi;
    while(!a.empty()){
        // cout<<"t -> "<<t<<endl;
        bool cond = 0;
        int idx = 0;
        while(idx < sz(a) && a[idx].fi <= t + 10){
            // cout<<"t -> "<<t<<" a -> "<<a[idx].fi<<", "<<a[idx].se<<endl;
            if(!a[idx].se) t = a[idx].fi;
            else cond = 1;
            idx++;
        }
        t += 10;
        // cout<<"exit"<<endl;

        reverse(all(a));

        int cnt = 0;
        while(cnt < idx){
            a.pop_back();
            cnt++;
        }

        if(cond) a.pb({t, 1});
        reverse(all(a));

        if(a.empty()) break;

        for0(i,sz(a)) a[i].fi = max(a[i].fi, t);
        if(a[0].se) for0(i,sz(a)) a[i].se ^= 1;

        // for0(i,sz(a)) cout<<"   i -> "<<i<<" a[i].fi -> "<<a[i].fi<<" a[i].se -> "<<a[i].se<<endl;

        if(a[0].fi > t) t = a[0].fi;
    }

    cout<<t<<endl;
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
