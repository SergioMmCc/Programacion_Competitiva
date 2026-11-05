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

struct line {
    ll m, b;
    ll eval(ll x) const { return m * x + b; }
    ld inter(const line &l) const { return (ld)(b - l.b) / (l.m - m); }
};

struct cht {
    vector<line> lines;
    vector<ld> inter;
    int n;
    bool ok(const line &a, const line &b, const line &c) const {
        return a.inter(c) > a.inter(b);
    }
    void add(const line &l){
        n = sz(lines);
        if(n && lines.back().m == l.m && lines.back().b >= l.b) return;
        if(n == 1 && lines.back().m == l.m && lines.back().b < l.b) lines.pop_back(), n--;
        while(n >= 2 && !ok(lines[n-2], lines[n-1], l)){
            --n;
            lines.pop_back(); inter.pop_back();
        }
        lines.pb(l); n++;
        if(n >= 2) inter.pb(lines[n-2].inter(lines[n-1]));
    }
    ll get_max(ld x){
        if(lines.empty()) return LLONG_MIN;
        if(sz(lines) == 1) return lines[0].eval(x);
        int pos = lb(all(inter), x) - inter.begin();
        return lines[pos].eval(x);
    }
};

void solver(){
    int n, m, p; cin>>n>>m>>p;
    vl pos(n);
    for1(i,n-1){
        ll num; cin>>num;
        pos[i] = pos[i-1] + num;
    }

    ll minn = INF;
    vl a(m);
    for0(i,m){
        int h, t; cin>>h>>t; h--;
        a[i] = (ll)t - pos[h];
        minn = min(minn, a[i]);
    }
    if(p >= m){
        cout<<0<<endl;
        return;
    }
    for0(i,m) a[i] -= minn;
    a.pb(0);
    sort(all(a));
    vl ps(m+1);
    for1(i,m) ps[i] = ps[i-1] + a[i];

    if(p == 1){
        cout<<a[m] * (ll)m - ps[m]<<endl;
        return;
    }

    vector<cht> h(p-1);

    for0(j,p-1) h[j].add({1, ps[1]});
    forlr(i,2,m-1){
        forn1(j,p-2){
            ll aux = a[i]*(ll)i - ps[i] - h[j-1].get_max(a[i]);
            h[j].add({i, -(aux + ps[i])});
        }
        ll aux = a[i] * (ll)i - ps[i];
        h[0].add({i, -(aux + ps[i])});
    }

    cout<<a[m]*(ll)m - ps[m] - h[p-2].get_max(a[m]);
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
