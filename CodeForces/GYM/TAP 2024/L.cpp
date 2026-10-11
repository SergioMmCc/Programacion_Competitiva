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

set<ll> pot2;
void calc(){
    ll num = 2;
    while(num <= 10000){
        pot2.insert(num);
        num *= 2;
    }
}

void solver(){
    int n, q; cin>>n>>q;
    vl a(n+1);
    for1(i,n) cin>>a[i];
    vl p2(n+1), imp(n+1), c1(n+1);
    for1(i,n){
        p2[i] = p2[i-1];
        c1[i] = c1[i-1];
        imp[i] = imp[i-1];
        if(a[i] == 1) c1[i]++;
        else if(a[i] & 1) imp[i] += a[i];
        else if(pot2.find(a[i]) != pot2.end()) p2[i] += a[i];
    }

    while(q--){
        int l, r; cin>>l>>r;
        ll sa = p2[r] - p2[l-1] + (c1[r] - c1[l-1] + 1) / 2, sb = imp[r] - imp[l-1] + (c1[r] - c1[l-1]) / 2;
        if(sa > sb) cout<<'A'<<endl;
        else if(sa < sb) cout<<'B'<<endl;
        else cout<<'E'<<endl;
    }
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
