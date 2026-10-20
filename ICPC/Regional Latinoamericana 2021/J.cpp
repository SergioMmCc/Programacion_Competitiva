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
typedef pair<pii, int> piii;
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

int w, h;
struct comparator {
    bool operator () (piii a, piii b){
        // Primero los superiores
        if(a.fi.se == h && b.fi.se == h) return a.fi.fi < b.fi.fi;
        if(a.fi.se == h || b.fi.se == h) return a.fi.se > b.fi.se;

        // Lado derecho
        if(a.fi.fi == w && b.fi.fi == w) return a.fi.se > b.fi.se;
        if(a.fi.fi == w || b.fi.fi == w) return a.fi.fi > b.fi.fi;

        // Abajo
        if(a.fi.se == 0 && b.fi.se == 0) return a.fi.fi > b.fi.fi;
        if(a.fi.se == 0 || b.fi.se == 0) return a.fi.se < b.fi.se;

        // Lado izquierdo
        if(a.fi.fi == 0 && b.fi.fi == 0) return a.fi.se < b.fi.se;
        return a.fi.fi < b.fi.fi;
    }
};

void solver(){
    int n; cin>>w>>h>>n;
    vector<piii> a;
    for0(i,n){
        int x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;
        if((x1 != w && y1 != h && x1 && y1) || (x2 != w && y2 != h && x2 && y2)) continue;
        a.pb({{x1, y1}, i});
        a.pb({{x2, y2}, i});
    }

    sort(all(a), comparator());
    vb used(n);
    stack<int> st;
    for0(i,sz(a)){
        // cout<<"i -> "<<i<<" x -> "<<a[i].fi.fi<<" y -> "<<a[i].fi.se<<" idx -> "<<a[i].se<<endl;

        if(!used[a[i].se]){
            used[a[i].se] = 1;
            st.push(a[i].se);
        }
        else{
            if(st.top() != a[i].se){
                cout<<'N'<<endl;
                return;
            }
            st.pop();
        }
    }

    cout<<'Y'<<endl;
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
