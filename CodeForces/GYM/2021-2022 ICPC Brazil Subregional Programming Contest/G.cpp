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

const ll maxn = 1e15;
vl fibo;
void calc(){
    fibo.pb(1); fibo.pb(1);
    while(fibo.back() <= maxn){
        fibo.pb(fibo.back() + fibo[sz(fibo) - 2]);
    }
    fibo.pop_back();
}

set<ll> cant;
bool can(ll n, vi& a){
    auto it = ub(all(fibo), n);
    --it;

    int idx = distance(fibo.begin(), it);

    if(fibo[idx] == n){
        a.pb(idx);
        return 1;
    }

    forrl(i,2,idx){
        if(n % fibo[i] == 0 && cant.find(n / fibo[i]) == cant.end()){
            a.pb(i);
            if(can(n / fibo[i], a)) return 1;
            a.pop_back();
        }
    }

    cant.insert(n);
    return 0;
}

void solver(){
    ll n; cin>>n;
    
    vi ans;
    bool cond = can(n, ans);
    if(!cond){
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }

    for(int &x : ans){
        for0(i,x-1) cout<<'A';
        cout<<'B';
    }
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calc();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
