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
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using indexed_set = tree<pli, null_type, greater<pli>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

void solver(){
    int n; cin>>n;
    vl a(n), b(n);
    for0(i,n) cin>>a[i];
    for0(i,n) cin>>b[i];
    int k, l; cin>>k>>l;

    if(k == l){
        ll sum = 0;
        for0(i,k) sum += a[i] + b[i];
        ll ans = sum;
        int left = k-1, right = n;
        while(left >= 0){
            right--;
            sum += a[right] + b[right];
            sum -= a[left] + b[left];
            ans = max(ans, sum);
            left--;
        }

        cout<<ans<<endl;

        return;
    }

    ll sum1 = 0, sum2 = 0;
    indexed_set win;
    for0(i,k){
        sum1 += a[i];
        win.insert({b[i], i});
        if(sz(win) <= l){
            sum2 += b[i];
            continue;
        }

        int idx = win.order_of_key({b[i], i});
        if(idx >= l) continue;
        auto it = win.find_by_order(l);
        sum2 -= (*it).fi;

        sum2 += b[i];
    }

    ll ans = sum1 + sum2;
    if(k == n){
        cout<<ans<<endl;
        return;
    }

    int left = k-1, right = n;
    while(left >= 0){
        sum1 += a[right-1] - a[left];

        int idx = win.order_of_key({b[left], left});
        if(idx < l){
            sum2 -= b[left];
            sum2 += (*win.find_by_order(l)).fi;
        }
        win.erase({b[left], left});

        right--;
        win.insert({b[right], right});
        idx = win.order_of_key({b[right], right});

        if(idx >= l){
            ans = max(ans, sum1 + sum2);
            left--;
            continue;
        }
        auto it = win.find_by_order(l);
        sum2 -= (*it).fi;

        sum2 += b[right];
        left--;

        ans = max(ans, sum1 + sum2);
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
