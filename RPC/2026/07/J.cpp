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
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pll> vll;
typedef vector<plll> vlll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void solver(){
    int n; cin>>n; n *= 2;
    vector<vlll> city(1e6 + 1);
    for0(i,n){
        ll a, d; int c; cin>>a>>d>>c;
        city[c].pb({a-d, {a, d}});
    }

    pqueue<ll> pqa, pqd;
    ll ans = 0;
    for1(i,1e6){
        sort(all(city[i]));
        if(city[i].empty()) continue;

        int m = sz(city[i]) / 2;
        if(sz(city[i]) % 2){
            vlll aux;
            for0(j,sz(city[i])){
                if(j == m) city[0].pb(city[i][j]);
                else aux.pb(city[i][j]);
            }
            city[i] = aux;
        }
        
        ans += (ll)m*(ll)i;
        for0(j,sz(city[i])){
            if(j < m){
                ans += city[i][j].se.se;
                pqd.push(city[i][j].se.fi - city[i][j].se.se - (ll)i);
            }
            else{
                ans += city[i][j].se.fi;
                pqa.push(city[i][j].se.se - city[i][j].se.fi - (ll)i);
            }
        }
    }

    // Procesar ciudad 0
    sort(all(city[0]));
    for0(j,sz(city[0])){
        if(j < sz(city[0]) / 2){
            ans += city[0][j].se.se;
            pqd.push(city[0][j].se.fi - city[0][j].se.se);
        }
        else{
            ans += city[0][j].se.fi;
            pqa.push(city[0][j].se.se - city[0][j].se.fi);
        }
    }
    while(!pqa.empty()){
        if(pqa.top() + pqd.top() > 0){
            ans += pqa.top() + pqd.top();
            pqa.pop();
            pqd.pop();
        }
        else break;
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
