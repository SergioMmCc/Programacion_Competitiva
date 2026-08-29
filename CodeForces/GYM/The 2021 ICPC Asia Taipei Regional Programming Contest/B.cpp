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

piii comp(int cnt, int l, int r, int n, piii ans, vi& ps){
    if(l) cnt += ps[l-1];
    cnt += ps[n-1] - ps[r];
    int take1 = r-l, take2 = ans.se.se - ans.se.fi;
    if(cnt > ans.fi || (cnt == ans.fi && (take1 < take2 || (take1 == take2 && l < ans.se.fi)))) return {cnt, {l, r}};
    return ans;
}

void solver(){
    int n; string s1, s2; cin>>n>>s1>>s2;
    vi ps(n);
    if(s1[0] == s2[0]) ps[0] = 1;
    for1(i,n-1){
        ps[i] = ps[i-1];
        if(s1[i] == s2[i]){
            ps[i]++;
        }
    }

    piii ans = {0, {0, 0}};
    for0(i,n){
        int aux = 0;
        if(s1[i] == s2[i]) aux++;
        ans = comp(aux, i, i, n, ans, ps);
        int l = i-1, r = i+1;
        while(l >= 0 && r < n){
            if(s1[l] == s2[r]) aux++;
            if(s1[r] == s2[l]) aux++;
            ans = comp(aux, l, r, n, ans, ps);
            l--; r++;
        }
    }
    for0(i,n-1){
        int aux = 0;
        if(s1[i] == s2[i+1]) aux++;
        if(s1[i+1] == s2[i]) aux++;
        ans = comp(aux, i, i+1, n, ans, ps);
        int l = i-1, r = i+2;
        while(l >= 0 && r < n){
            if(s1[l] == s2[r]) aux++;
            if(s1[r] == s2[l]) aux++;
            ans = comp(aux, l, r, n, ans, ps);
            l--; r++;
        }
    }

    cout<<ps[n-1]<<' '<<ans.fi<<' '<<ans.se.fi+1<<' '<<ans.se.se+1<<endl;
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
