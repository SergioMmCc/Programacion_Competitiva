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

void printarr(vi& a){
    for(int x : a) cout<<x<<' ';cout<<endl;
}

void solver(){
    int n, q; cin>>n>>q;
    vi a(n);
    int maxx = 0;
    bool cond = 0;
    vi ans;
    for0(i,n){
        cin>>a[i];
        if(a[i]) cond = 1;
    }
    if(cond){
        sort(all(a));
        maxx++;
        ans.pb(a[n-1] - a[0]);
    }

    while(cond){
        cond = 0;
        vi aux;
        for0(j,n-1){
            forlr(k,j+1,n-1){
                aux.pb(a[j] ^ a[k]);
            }
        }
        sort(all(aux));
        for0(j,n){
            a[j] = aux[j];
            if(a[j]) cond = 1;
        }
        if(cond){
            maxx++;
            ans.pb(a[n-1] - a[0]);
        }
    }

    while(q--){
        int idx; cin>>idx;
        if(idx >= maxx) cout<<0<<endl;
        else{
            cout<<ans[idx]<<endl;
        }
    }
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
