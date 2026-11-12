#include<bits/stdc++.h>
using namespace std;
// #define endl '\n'
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
    vi a(n+2);
    if(n % 4 != 2){
        for(int i = 4; i <= n; i += 4){
            a[i] = 2;
            a[i-1] = 2;
            a[i-2] = 1;
            a[i-3] = 1;
        }
        if(n % 4 == 1) a[n] = 1;
        else if(n % 4 == 3){
            a[n-2] = 1;
            a[n-1] = 1;
            a[n] = 2;
        }
    }
    else{
        a[1] = 1;
        a[n] = 2;
        for(int i = 5; i < n; i+= 4){
            a[i] = 1;
            a[i-1] = 1;
            a[i-2] = 2;
            a[i-3] = 2;
        }
    }

    cout<<2;
    for1(i,n) cout<<' '<<a[i]; cout<<endl;


    int q; cin>>q;
    while(q--){
        int m; cin>>m;
        vi seq(m);
        int maxx = 1, step = 1;
        bool dir = 1;
        for0(i,m){
            cin>>seq[i];
            if(i > 1){
                if(seq[i] == seq[i-2]){
                    if(dir){
                        dir = 0;
                        step--;
                    }
                    else{
                        dir = 1;
                        step++;
                        maxx = max(maxx, step);
                    }
                }
                else{
                    if(dir){
                        step++;
                        maxx = max(maxx, step);
                    }
                    else step--;
                }
            }
        }

        int ri = n - maxx, le = maxx + 1;
        vi ans;
        if(a[ri] == seq[0] && a[ri+1] == seq[1]) ans.pb(ri);
        else ans.pb(le);
        for1(i,m-1){
            if(seq[i] == a[ans.back() - 1]) ans.pb(ans.back() - 1);
            else ans.pb(ans.back() + 1);
        }
        for0(i, m){
            if(i) cout<<' ';
            cout<<ans[i];
        }
        cout<<endl;
    }
}

int main(){
    //  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}