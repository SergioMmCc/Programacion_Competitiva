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

const int SZ = 1 << 17; // Techo del log2 del maximo indice

template<class T>
T neutro(){
    return 0; // Change
}

template<class T>
T oper(T a, T b){
    if(a == neutro<T>()) return b;
    if(b == neutro<T>()) return a;
    return a + b; // Change
}

template<class T> struct node {
	T val = neutro<T>(); 
    node<T>* c[2];
	node() { c[0] = c[1] = NULL; }

	void upd(int ind, T v, int L = 0, int R = SZ-1){ // asignar v
		if(L == ind && R == ind){ 
            val = v; 
            return; 
        }
		int M = (L+R) / 2;
		if(ind <= M){
			if(!c[0]) c[0] = new node();
			c[0]->upd(ind,v,L,M);
		} 
        else{
			if(!c[1]) c[1] = new node();
			c[1]->upd(ind,v,M+1,R);
		}
        T lv = c[0] ? c[0]->val : neutro<T>();
        T rv = c[1] ? c[1]->val : neutro<T>();
		val = oper(lv, rv);
	}

    // [lo, hi]
	T calc(int lo, int hi, int L = 0, int R = SZ-1){
		if(hi < L || R < lo) return neutro<T>();
		if(lo <= L && R <= hi) return val;
		
		int M = (L+R) / 2;
        T lv = c[0] ? c[0]->calc(lo, hi, L, M) : neutro<T>();
        T rv = c[1] ? c[1]->calc(lo, hi, M+1, R) : neutro<T>();
		return oper(lv, rv);
	}

    // for 2D segtree
	void UPD(int ind, node* c0, node* c1, int L = 0, int R = SZ-1){ 
		if(L != R){
			int M = (L+R) / 2;
			if(ind <= M){
				if(!c[0]) c[0] = new node();
				c[0]->UPD(ind, c0 ? c0->c[0] : NULL, c1 ? c1->c[0] : NULL, L, M);
			} 
            else{
				if(!c[1]) c[1] = new node();
				c[1]->UPD(ind, c0 ? c0->c[1] : NULL, c1 ? c1->c[1] : NULL, M+1, R);
			}
		} 
		val = oper((c0 ? c0->val : neutro<T>()), (c1 ? c1->val : neutro<T>()));
	}
};

template<class T> struct Node {
	node<T> seg; 
    Node* c[2];
	Node() { c[0] = c[1] = NULL; }

	void upd(int x, int y, T v, int L = 0, int R = SZ-1){ // Asigna v en (x,y)
		if(L == x && R == x){ 
            seg.upd(y,v); 
            return; 
        }
		int M = (L+R) / 2;
		if(x <= M){
			if(!c[0]) c[0] = new Node();
			c[0]->upd(x,y,v,L,M);
		} 
        else{
			if (!c[1]) c[1] = new Node();
			c[1]->upd(x,y,v,M+1,R);
		}
		seg.UPD(y, c[0] ? &c[0]->seg : NULL, c[1] ? &c[1]->seg : NULL);
	}

    // Query rectangle [(x1, y1), (x2, y2)]
	T calc(int x1, int x2, int y1, int y2, int L = 0, int R = SZ-1){
		if(x1 <= L && R <= x2) return seg.calc(y1,y2);
		if(x2 < L || R < x1) return neutro<T>();
		
        int M = (L+R) / 2; 
        T lv = c[0] ? c[0]->calc(x1, x2, y1, y2, L, M) : neutro<T>();
        T rv = c[1] ? c[1]->calc(x1, x2, y1, y2, M+1, R) : neutro<T>();
		return oper(lv, rv);
	}
};

void solver(){
    Node<int> stx, sty;
    int n, t; cin>>n>>t;

    vii rd(n);
    vi cx, cy;
    for0(i,n){
        cin>>rd[i].fi>>rd[i].se;
        cx.pb(rd[i].fi);
        cy.pb(rd[i].se);
    }
    sort(all(cx));
    sort(all(cy));

    int idx = 1, idy = 1;
    map<int, int> cox, coy;
    for(int z : cx){
        if(cox.find(z) == cox.end()){
            cox[z] = idx;
            idx++;
        }
    }
    for(int z : cy){
        if(coy.find(z) == coy.end()){
            coy[z] = idy;
            idy++;
        }
    }

    for0(i,n) rd[i] = {cox[rd[i].fi], coy[rd[i].se]};

    int x = rd[0].fi, y = rd[0].se;

    map<pii, int> xval, yval;
    ll ans = 0;
    vector<pair<pii, pii>> a(1);
    forlr(i,1,n-1){
        if(i > t){
            int idx = i - t;
            if(a[idx].fi.fi == a[idx].se.fi){
                xval[{a[idx].fi.fi, a[idx].fi.se - 1}]++;
                stx.upd(a[idx].fi.fi, a[idx].fi.se - 1, xval[{a[idx].fi.fi, a[idx].fi.se - 1}]);
                xval[{a[idx].se.fi, a[idx].se.se}]--;
                stx.upd(a[idx].se.fi, a[idx].se.se, xval[{a[idx].se.fi, a[idx].se.se}]);
            }
            else{
                yval[{a[idx].fi.fi - 1, a[idx].fi.se}]++;
                sty.upd(a[idx].fi.fi - 1, a[idx].fi.se, yval[{a[idx].fi.fi - 1, a[idx].fi.se}]);
                yval[{a[idx].se.fi, a[idx].se.se}]--;
                sty.upd(a[idx].se.fi, a[idx].se.se, yval[{a[idx].se.fi, a[idx].se.se}]);
            }
        }

        int u = rd[i].fi, v = rd[i].se;
        if(u == x){
            a.pb({{x, y}, {u, v}});
            if(v > y) swap(a.back().fi, a.back().se);

            ans += (ll)sty.calc(x, 1e9, min(v, y) + 1, max(v, y) - 1);
        }
        else{
            a.pb({{x, y}, {u, v}});
            if(u > x) swap(a.back().fi, a.back().se);

            ans += (ll)stx.calc(min(u, x) + 1, max(u, x) - 1, y, 1e9);
        }

        x = u;
        y = v;
    }

    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    freopen("mowing.in", "r", stdin);
	freopen("mowing.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
