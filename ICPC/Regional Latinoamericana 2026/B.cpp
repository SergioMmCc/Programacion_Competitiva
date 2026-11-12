#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forrl(i,l,r) for(int i = (int)r; i >= (int)l; i--)
#define forlr(i,l,r) for(int i = (int)l; i <= (int)r; i++)
#define pb push_back
#define sz(a) ((int)a.size())

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pil> vil;
typedef vector<pll> vll;

struct segTree{
    int n; ll neutro = 0;
    vl tree;
    inline ll op(ll a, ll b) { return a + b;}

    void init(int _n){
        n = _n;
        tree.assign(2*n, neutro);
    }

    void build(vl& a){
        for0(i,n) tree[n+i] = a[i];
        forrl(i, 1, n-1) tree[i] = op(tree[i<<1], tree[i<<1|1]); // OJO
    }
    ll calc(int l, int r){
        ll resL = neutro, resR = neutro;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) resL = op(resL, tree[l++]);
            if(r & 1) resR = op(resR, tree[--r]);
        }
        return op(resL, resR);
    }
    void update(int p, ll val){
        for(tree[p += n] = val; p > 1; p >>= 1) tree[p>>1] = op(tree[p], tree[p ^ 1]);
    }
};

struct P{
    ll x, y, w, id;
};

ld dist(P p){
    return sqrt(p.x*p.x + p.y*p.y);
}

ld cross(P a, P b){
    return (a.x*b.y - a.y*b.x);
}
int angle_half(P p){return p.y==0 && p.x >=0 ? 0 : 1;}
bool check(P a, P b){
    int x=angle_half(a), y=angle_half(b);
    if(x!=y) return x < y;
    ll z = cross(a, b);
    if(z!= 0) return z >0;
    return a.x != b.x ? a.x < b.x : a.y<b.y;
}

void solver(){
    int n, D;
    cin>>n>>D;

    vector<P> ptsA(n);
    for(int i=0; i<n; i++){
        cin>>ptsA[i].x>>ptsA[i].y>>ptsA[i].w;
        ptsA[i].id = i+1;
    }

    vector<P> ptsB = ptsA;
    for(int i=0; i<n; i++){
        ptsB[i].x = -(ptsB[i].x - D);
    }

    P cm = {0, 1};
    sort(ptsA.begin(), ptsA.end(), [&](P a, P b){
        return check(a, b);
    });
    sort(ptsB.begin(), ptsB.end(), [&](P a, P b){
        return check(a, b);
    });

    vi a(1), b(1);
    vl we(1);
    for(auto [i, j, w, id] : ptsA){
        a.pb(id);
        we.pb(w);
    }
    for(auto [i, j, w, id] : ptsB) b.pb(id);
    vi pos(n+1);
    for1(i,n) pos[a[i]] = i;

    segTree st; st.init(n+1); 
    st.build(we);

    ll ans = 0;
    for1(j,n){
        int i = b[j];
        ll aux = st.calc(0, pos[i]);
        ans += aux * we[pos[i]];
        st.update(pos[i], 0);
    }

    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t=1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}