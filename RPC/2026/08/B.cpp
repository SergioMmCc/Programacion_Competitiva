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
typedef pair<int, ll> pil;
typedef pair<pil, pil> pilil;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pilil> vilil;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
const ll mod = 9302023;

pil calc(vi& a){
    int len = -sz(a) + 1;
    for0(i,sz(a)) len += a[i];
    // db(len);
    vilil dp(sz(a)); dp[0] = {{a[0], 1}, {1, 1}};
    for1(i,sz(a)-1){
        if(dp[i-1].fi.fi - 1 == dp[i-1].se.fi - 1) dp[i].fi = {dp[i-1].fi.fi + a[i] - 1, (dp[i-1].fi.se + dp[i-1].se.se) % mod};
        else{
            pil aux1 = {dp[i-1].fi.fi - 1 + a[i], dp[i-1].fi.se}, aux2 = {dp[i-1].se.fi - 1 + a[i], dp[i-1].se.se};
            dp[i].fi = min(aux1, aux2);
        }
        dp[i].se = dp[i-1].fi;
    }

    int aux = sz(a) - 1;
    // cout<<dp[aux].fi.fi<<' '<<dp[aux].fi.se<<' '<<dp[aux].se.fi<<' '<<dp[aux].se.se<<endl;
    if(dp[aux].fi.fi == dp[aux].se.fi) return {len - dp[aux].fi.fi, (dp[aux].fi.se + dp[aux].se.se) % mod};
    dp[aux].fi.fi = len - dp[aux].fi.fi; dp[aux].se.fi = len - dp[aux].se.fi;
    return max(dp[aux].fi, dp[aux].se);
}

vs words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void solver(){
    string s; cin>>s;
    vii segs;
    for(string w : words){
        for0(i, sz(s) - sz(w) + 1){
            string aux = "";
            forlr(j, i, i+sz(w)-1) aux += s[j];
            if(aux == w) segs.pb({i, i + sz(w)-1});
        }
    }

    int ans = sz(s);
    ll cnt = 1;
    sort(all(segs));
    for0(i, sz(segs)){
        vi a; a.pb(segs[i].se - segs[i].fi + 1);
        int last = segs[i].se;
        int j = i+1;
        while(j < sz(segs) && segs[j].fi == last){
            a.pb(segs[j].se - segs[j].fi + 1);
            last = segs[j].se;
            j++;
        }
        pil aux = calc(a);
        ans -= aux.fi;
        cnt = (cnt * aux.se) % mod;

        i = j-1;
    }

    cout<<ans<<endl<<cnt<<endl;
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
