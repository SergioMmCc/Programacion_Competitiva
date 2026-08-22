#include<bits/stdc++.h>
using namespace std;
#define int long long
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
typedef int ll;
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
    string s; cin>>s;
    int n = sz(s);
    vi a(n);
    for0(i,n) a[i] = s[i] - '0';
    // for0(i,n) cout<<a[i]<<' '; cout<<endl;

    forrl(k,2,n-1){
        for0(i,10){
            int aux = a[0] + i; aux %= 10;
            vi c = a;
            c[0] = aux;
            int sum = i; vi sumarr(n); sumarr[0] = i;
            for(int l = 1; l + k - 1 < n; l++){
                c[l] = (c[l] + sum + 10 - (l >= k ? sumarr[l-k] : 0)) % 10;
                int mv = (aux - c[l] + 10) % 10;
                sum = (sum + mv + 10) % 10;
                sumarr[l] = sum;
                c[l] = (c[l] + mv) % 10;
            }
            bool cond = 1;
            for(int j = n-1; j >= n-k+1; j--){
                // if(j-k < 0){
                //     cout<<"j -> "<<j<<" k -> "<<k<<endl;
                //     return;
                // }
                // assert(j-k >= 0);
                if(aux != (c[j] + sum - (j >= k ? sumarr[j-k] : 0) + 10) % 10){
                    // cout<<"j -> "<<j<<" c[j] -> "<<c[j]<<endl;
                    cond = 0;
                    break;
                }
            }
            if(cond){
                cout<<k<<endl;
                return;
            }
        }
    }
    cout<<1<<endl;
}

signed main(){
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
