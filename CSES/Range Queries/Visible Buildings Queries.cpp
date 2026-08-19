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

void solver(){
    int n, q; cin>>n>>q;
    vi a(n+1);
    for1(i,n) cin>>a[i];

    stack<pii> st;
    vi bigi(n+1);
    forn1(i,n){
        while(!st.empty() && st.top().fi <= a[i]){
            bigi[st.top().se] = i;
            st.pop();
        }
        st.push({a[i],i});
    }

    blen = sqrt(n); // Raiz del tamaño del arreglo
    vector<query> qs(q);
    for0(i,q){
        cin>>qs[i].l>>qs[i].r;
        qs[i].idx = i;
    }
    sort(all(qs), cmp);

    vi cnt(n+1);
    int ans = 0;
    vi pri(q);
    int l = 0, r = -1;
    for0(i,q){
        while(r < qs[i].r){
            ++r;
            cnt[bigi[r]]++;
            if(bigi[r] < l) ans++;
        }
        while(l > qs[i].l){
            --l;
            ans -= cnt[l];
            ans++;
            cnt[bigi[l]]++;
        }
        while(r > qs[i].r){
            cnt[bigi[r]]--;
            if(bigi[r] < l) ans--;
            r--;
        }
        while(l < qs[i].l){
            ans += cnt[l];
            ans--;
            cnt[bigi[l]]--;
            l++;
        }
        pri[qs[i].idx] = ans;
    }

    for0(i,q) cout<<pri[i]<<endl;

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
