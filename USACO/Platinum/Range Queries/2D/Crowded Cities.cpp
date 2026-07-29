#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
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

struct vertex{ // Change
    ll val; int idx;
};

struct build{
    int l, w, h, idx; ll val;

    bool operator<(const build& otro) const{
        if(h != otro.h) return h < otro.h;
        if(l != otro.l) return l < otro.l;
        if(w != otro.w) return w < otro.w;
        return idx < otro.idx;
    }

    bool operator>(const build& otro) const{
        if(h != otro.h) return h > otro.h;
        if(l != otro.l) return l > otro.l;
        if(w != otro.w) return w > otro.w;
        return idx > otro.idx;
    }
};

const int SZ = 1 << 13; // Techo del log2 del maximo indice

template<class T>
T neutro(){
    return {0, -1}; // Change
}

template<class T>
T oper(T a, T b){
    if(a.val == neutro<T>().val) return b;
    if(b.val == neutro<T>().val) return a;
    T ans;
    if(a.val == b.val) ans = a.idx < b.idx ? a : b;
    else ans = a.val > b.val ? a : b;
    return ans;
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
    int n; cin>>n;

    vector<build> a(n);
    for(int i = 0; i < n; i++){
        cin>>a[i].l>>a[i].w>>a[i].h>>a[i].val;
        if(a[i].l < a[i].w) swap(a[i].l, a[i].w);
        a[i].idx = i;
    }
    sort(all(a), greater<build>());
    vi change(n);
    for(int i = 0; i < n; i++) change[a[i].idx] = i;

    Node<vertex> st;

    vi where(n, -1);

    for(build b : a){
        int y = b.w, x = b.l, idx = b.idx; ll add = b.val;
        vertex best = st.calc(y, 5000, x, 5000);
        add += best.val;
        where[idx] = best.idx;

        st.upd(y, x, {add, idx});
    }

    vertex ans = st.calc(0, 5000, 0, 5000);
    cout<<ans.val<<endl;

    vi b;
    int u = ans.idx;
    while(u != -1){
        b.pb(u);
        u = where[u];
    }

    reverse(all(b));
    cout<<sz(b)<<endl;
    for(int aux : b) cout<<aux + 1<<' ';
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}