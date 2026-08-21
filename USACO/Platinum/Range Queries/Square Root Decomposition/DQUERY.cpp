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

struct query {
    int l, r, idx;
};
int blen; // blen = sqrt(n)
bool cmp(query u, query v){
    int x = u.l / blen;
    if(x != v.l / blen) return x < v.l / blen;
    return x&1 ? u.r > v.r : u.r < v.r; // Bloque impar r decreciente, par r creciente
}

vi a(3e4);
vi cnt(1e6+1);
int save = 0;
void add(int idx){
    if(!cnt[a[idx]]) save++;
    cnt[a[idx]]++;
}
void del(int idx){
    if(cnt[a[idx]] == 1) save--;
    cnt[a[idx]]--;
}

void solver(){
    int n; cin>>n;
    for0(i,n) cin>>a[i];
    blen = sqrt(n);

    int q; cin>>q;
    vector<query> qs(q);
    for0(i,q){
        cin>>qs[i].l>>qs[i].r; qs[i].l--; qs[i].r--;
        qs[i].idx = i;
    }
    sort(all(qs), cmp);

    // Procesar
    vi ans(q);
    int l = 0, r = -1;
    for0(i,q){
        while(r < qs[i].r) add(++r);
        while(l > qs[i].l) add(--l);
        while(r > qs[i].r) del(r--);
        while(l < qs[i].l) del(l++);
        ans[qs[i].idx] = save;
    }

    for0(i,q) cout<<ans[i]<<endl;
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
