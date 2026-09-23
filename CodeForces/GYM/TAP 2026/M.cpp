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

struct sqrtDecomp{
    int n, blen;
    vl a, b, cap, bCap;
    vb isFull, isEmpty;
    sqrtDecomp(){}
    sqrtDecomp(vl& arr, vl& c): n(sz(arr)), blen(sqrt(n)+1), a(arr), b(blen), cap(c), bCap(blen), isFull(blen), isEmpty(blen){
        for0(i,n){
            b[i/blen] += a[i];
            bCap[i/blen] += c[i];
        }
    }

    void update(int pos, ll val){
        int bloque = pos/blen;
        int idx = pos;
        if((idx+1)/blen == bloque){
            if(isEmpty[bloque]){
                int aux = bloque * blen;
                forlr(i, aux, aux+blen-1) a[i] = 0;
                isEmpty[bloque] = 0;
            }
            while(!isFull[bloque] && idx >= 0 && val && idx/blen == bloque){
                if(val + a[idx] <= cap[idx]){
                    a[idx] += val;
                    b[bloque] += val;
                    val = 0;
                }
                else{
                    b[bloque] += cap[idx] - a[idx];
                    val -= cap[idx] - a[idx];
                    a[idx] = cap[idx];
                    idx--;
                }
            }
            bloque--;
        }

        while(val && bloque >= 0){
            if(isFull[bloque]){
                bloque--;
                continue;
            }
            if(bCap[bloque] - b[bloque] < val){
                val -= bCap[bloque] - b[bloque];
                b[bloque] = bCap[bloque];
                isFull[bloque] = 1;
                isEmpty[bloque] = 0;
                bloque--;
            }
            else{
                if(isEmpty[bloque]){
                    int aux = bloque * blen;
                    forlr(i, aux, aux+blen-1) a[i] = 0;
                    isEmpty[bloque] = 0;
                }
                idx = (bloque + 1) * blen - 1;
                while(val){
                    if(val + a[idx] <= cap[idx]){
                        a[idx] += val;
                        b[bloque] += val;
                        val = 0;
                    }
                    else{
                        b[bloque] += cap[idx] - a[idx];
                        val -= cap[idx] - a[idx];
                        a[idx] = cap[idx];
                        idx--;
                    }
                }
            }
        }
    }

    ll calc(int l, int r){ // [l, r]
        ll sum = 0;
        int bl = l/blen, br = r/blen;
        if(bl == br){
            if(isEmpty[bl]) return 0;
            forlr(i, blen*bl, blen*(bl + 1) - 1){
                if(i < l || i > r){
                    if(isFull[bl]) a[i] = cap[i];
                    continue;
                }
                if(isFull[bl]){
                    sum += cap[i];
                    b[bl] -= cap[i];
                    a[i] = 0;
                }
                else{
                    sum += a[i];
                    b[bl] -= a[i];
                    a[i] = 0;
                }
            }
            isFull[bl] = 0;
        }
        else{
            forlr(i, blen*bl, blen*(bl+1)-1){
                if(isEmpty[bl]) break;
                if(i < l){
                    if(isFull[bl]) a[i] = cap[i];
                    continue;
                }
                if(isFull[bl]){
                    sum += cap[i];
                    b[bl] -= cap[i];
                    a[i] = 0;
                }
                else{
                    sum += a[i];
                    b[bl] -= a[i];
                    a[i] = 0;
                }
            }
            forlr(i, blen*br, blen*(br+1) - 1){
                if(isEmpty[br]) break;
                if(i > r){
                    if(isFull[br]) a[i] = cap[i];
                    continue;
                }
                if(isFull[br]){
                    sum += cap[i];
                    b[br] -= cap[i];
                    a[i] = 0;
                }
                else{
                    sum += a[i];
                    b[br] -= a[i];
                    a[i] = 0;
                }
            }
            isFull[bl] = isFull[br] = 0;
            forlr(i, bl+1, br-1){
                if(isEmpty[i]) continue;
                sum += b[i]; // Bloques centrales
                isEmpty[i] = 1;
                isFull[i] = 0;
                b[i] = 0;
            }
        }
        return sum;
    }
};

void solver(){
    int n, q; cin>>n>>q;
    vl a(n), cap(n);
    for0(i,n) cin>>cap[i];

    sqrtDecomp sq(a, cap);

    while(q--){
        int op; cin>>op;
        if(op == 1){
            int idx; ll val; cin>>idx>>val; idx--;
            sq.update(idx, val);
        }
        else{
            int l, r; cin>>l>>r; l--; r--;
            cout<<sq.calc(l, r)<<endl;
        }
    }
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
