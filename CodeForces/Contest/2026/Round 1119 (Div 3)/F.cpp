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
    vi a(n);
    int cnt0 = 0, cnt1 = 0;
    for0(i,n){
        cin>>a[i];
        if(a[i]) cnt1++;
        else cnt0++;
    }
    deque<int> d0, d1;
    ll cnt = 0;
    int take0 = 0;
    vl ans(n+1);
    for0(i,n){
        int j = i, aux = 0;
        while(j < n && a[i] == a[j]){
            aux++;
            if(a[j]) cnt += cnt0 - take0;
            else take0++;
            j++;
        }
        if(a[i]) d1.pb(aux);
        else d0.pb(aux);
        i = j-1;
    }
    if(a[0]) d0.push_front(0);
    if(!a[n-1]) d1.pb(0);
    ans[0] = cnt;

    string s; cin>>s;
    int idx = 0;
    while(cnt){
        assert(cnt > 0);

        if(s[idx] == '0'){
            cnt -= cnt1 - d1.back();
            d0.back()--;
            d0.front()++;
            if(!d0.back()){
                d0.pop_back();
                int aux = d1.back(); d1.pop_back();
                d1.back() += aux;
            }
        }
        else{
            cnt -= cnt0 - d0.front();
            d1.front()--;
            d1.back()++;
            if(!d1.front()){
                d1.pop_front();
                int aux = d0.front(); d0.pop_front();
                d0.front() += aux;
            }
        }

        ans[idx+1] = cnt;
        idx++;
    }

    for0(i,n+1) cout<<ans[i]<<' ';
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
