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
typedef pair<ll, ll> pll;
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using indexed_set = tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ld, int> pdi;
typedef pair<pdi, pii> pdiii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

struct comparator {
    bool operator () (piii a, piii b){
        int n1 = a.se.fi, d1 = a.fi, n2 = b.se.fi, d2 = b.fi;
        if(n1 * d2 == n2 * d1) return a.se.fi < b.se.fi;
        return n1 * d2 < n2 * d1;
    }
};

void solver(){
    int n, s, k; cin>>n>>s>>k;
    vector<piii> a(n);
    for0(i,n){
        ll h; int l, u; cin>>h>>l>>u;
        a[i] = {h, {l, u}};
    }
    sort(all(a), comparator());

    pqueue<piii, vector<piii>, comparator> pq;
    int cnt = 0, idx = 0;
    indexed_set save;
    int kdx = -1;
    ll ans1 = INFL, ans2 = 1;
    int put = 0, sum = 0;
    while(idx < n){
        while(!pq.empty()){
            int jdx = pq.top().se.se;
            if(pq.top().fi * a[idx].fi < a[idx].se.fi * pq.top().se.fi){ // Quitar elemento
                // cout<<"idx -> "<<idx<<" jdx -> "<<jdx<<endl;
                ll h = a[jdx].fi;
                cnt -= k / h;
                pq.pop();

                int where = save.order_of_key({h, jdx});
                if(where > kdx) continue;
                else{
                    put -= k / h;
                    sum -= h * (k / h);
                    save.erase({h, jdx});
                    while(kdx < sz(save)){
                        ll h2 = (*save.find_by_order(kdx)).fi;
                        ll add = k / h2;
                        if(put + add > s) break;
                        put += add;
                        sum += h2 * add;
                        kdx++;
                    }
                    kdx--;
                }
            }
            else break;
        }

        ll h = a[idx].fi;
        cnt += k / h;
        pq.push({a[idx].se.se, {h, idx}}); // LA COLA ESTABA MAL DESDE EL PRINCIPIO

        // Meterlo al indexed_set
        save.insert({h, idx});
        int where = save.order_of_key({h, idx});
        if(where <= kdx || (where == kdx +1 && put + k / h <= s)){
            // cout<<"here: "<<idx<<endl;
            ll add = k / h;
            put += add;
            sum += h * add;
            kdx++;
            while(kdx >= 0 && put > s){
                auto it = save.find_by_order(kdx);
                ll h2 = (*it).fi;
                ll take = k / h2;
                put -= take;
                sum -= h2 * take;
                kdx--;
            }
        }

        if(cnt < s){
            idx++;
            continue;
        }

        ll falta = 0;
        if(put < s) falta = (*save.find_by_order(kdx+1)).fi * (s - put);
        // cout<<"idx -> "<<idx<<" l -> "<<a[idx].se.fi<<" falta -> "<<falta<<" put -> "<<put<<" sum -> "<<sum<<" h -> "<<h<<endl;
        ll num = a[idx].se.fi * (falta + sum), den = h;
        if((ld)num / (ld)den < (ld)ans1 / (ld)ans2) ans1 = num, ans2 = den;

        idx++;
    }

    if(ans1 == INFL){
        cout<<'*'<<endl;
        return;
    }

    ll gc = gcd(ans1, ans2);
    // cout<<ans1<<' '<<ans2<<endl;
    ans1 /= gc; ans2 /= gc;
    cout<<ans1<<' '<<ans2<<endl;
}

signed main(){
    // ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
