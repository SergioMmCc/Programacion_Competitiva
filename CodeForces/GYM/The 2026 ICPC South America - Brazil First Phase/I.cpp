#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
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
typedef pair<char, pii> pcii;
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

const int maxn = 1e6;
int components;
vi leader(maxn), st(maxn), go(maxn);
vl cnt(maxn);
vb pos(maxn);
vector<int> sets[maxn];

void initDSU(int n){
    components = n;
    for0(i,n){
        leader[i] = i;
        sets[i].push_back(i);
    }
}

void join(int u, int v){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        if(sets[leaderV].size() > sets[leaderU].size())
            swap(leaderU, leaderV);
        
        for(int i = 0; i < sets[leaderV].size(); i++){
            int v = sets[leaderV][i];
            leader[v] = leaderU;
            sets[leaderU].push_back(v);
        }
        cnt[leaderU] += cnt[leaderV];
        if(pos[leaderV] || pos[leaderU]){
            // cout<<"u -> "<<u<<" leaderU -> "<<leaderU<<" v -> "<<v<<" leaderV -> "<<leaderV<<" stV -> "<<st[leaderV]<<" goV -> "<<go[leaderV]<<endl;
            pos[leaderU] = 1;
            st[leaderU] = max(st[leaderU], st[leaderV]);
            go[leaderU] = max(go[leaderU], go[leaderV]);
        }
        sets[leaderV].clear();
        components--;
    }
}

void solver(){
    int f, n; cin>>f>>n;
    vi comp, comp2;
    vii inv(n);
    for0(i,n){
        cin>>inv[i].fi>>inv[i].se;
        comp.pb(inv[i].fi);
    }

    vector<pcii> ac(n);
    for0(i,n){
        cin>>ac[i].fi;
        if(ac[i].fi == 'A'){
            cin>>ac[i].se.fi>>ac[i].se.se; ac[i].se.se += ac[i].se.fi;
            comp2.pb(ac[i].se.fi);
            comp2.pb(ac[i].se.se);
        }
        else if(ac[i].fi == 'T'){
            cin>>ac[i].se.fi;
            comp.pb(ac[i].se.fi);
        }
    }

    // Comprimir
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    for0(i,n){
        inv[i].fi = lb(all(comp), inv[i].fi) - comp.begin();
        if(ac[i].fi == 'T') ac[i].se.fi = lb(all(comp), ac[i].se.fi) - comp.begin();
    }
    if(comp2.empty()){
        cout<<0<<endl;
        return;
    }
    sort(all(comp2));
    comp2.erase(unique(all(comp2)), comp2.end());
    for0(i,n){
        if(ac[i].fi == 'A'){
            ac[i].se.fi = lb(all(comp2), ac[i].se.fi) - comp2.begin();
            ac[i].se.se = lb(all(comp2), ac[i].se.se) - comp2.begin();
        }
    }

    // cout<<"here"<<endl;
    f = sz(comp);
    initDSU(f);

    for0(i,n) cnt[inv[i].fi] += (ll)inv[i].se;
    for0(i,n){
        if(ac[i].fi == 'A'){
            pos[inv[i].fi] = 1;
            st[inv[i].fi] = ac[i].se.fi;
            go[inv[i].fi] = ac[i].se.se;
            // cout<<"inv[i] -> "<<inv[i].fi<<" st -> "<<st[inv[i].fi]<<" go -> "<<go[inv[i].fi]<<endl;
        }
    }
    for0(i,n){
        if(ac[i].fi == 'T'){
            join(inv[i].fi, ac[i].se.fi);
            // cout<<"i -> "<<i<<" inv[i].fi -> "<<inv[i].fi<<" ac[i].se.fi -> "<<ac[i].se.fi<<endl;
        }
    }

    vl sum(sz(comp2));
    for0(i,f){
        // cout<<"i -> "<<i<<" leader -> "<<leader[i]<<" cnt -> "<<cnt[i]<<" st -> "<<st[leader[i]]<<" go -> "<<go[leader[i]]<<endl;
        if(i != leader[i] || !pos[i]) continue;
        sum[st[i]] += cnt[i];
        sum[go[i]] -= cnt[i];
    }

    ll ans = 0;
    for0(i, sz(comp2)){
        if(i) sum[i] += sum[i-1];
        ans = max(ans, sum[i]);
    }

    cout<<ans<<endl;
}

signed main(){
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
