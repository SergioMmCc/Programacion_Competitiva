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
const ll MOD = 1e9 + 7;

vl pot2(1e5 + 1);
void calc(){
    pot2[0] = 1;
    for1(i, 1e5) pot2[i] = (pot2[i-1] * 2LL) % MOD;
}

const int limite = 1001;

vb esPrimo(limite + 1, 1);
vi primos;

void sieve(){
    esPrimo[0] = esPrimo[1] = 0;
    for(ll p = 2; p*p <= limite; p++){
        if(esPrimo[p]){
            for(ll i = p * p; i <= limite; i += p)
                esPrimo[i] = 0;
        }
    }

    forlr(i,2, limite) if(esPrimo[i]) primos.pb(i);
}

int change(int num){
    int p = 0;
    int aux = 1;
    while(p < sz(primos) && primos[p] * primos[p] <= num){
        if(num % primos[p] == 0){
            aux *= primos[p];
            while(num % primos[p] == 0) num /= primos[p];
        }
        p++;
    }
    if(num > 1) aux *= num;

    return aux;
}

void solver(){
    int n; cin>>n;
    vi cnt(1e6 + 1);
    for0(i,n){
        int num; cin>>num;
        if(num == 1) continue;
        num = change(num);

        cnt[num]++;
        for(int r = 2; r * r < num; r++){
            if(num % r == 0){
                cnt[r]++;
                cnt[num/r]++;
            }
        }
        int r = sqrt(num);
        if(r * r == num) cnt[r]++;
    }

    forlr(i,2,1e6){
        if(!cnt[i]) continue;
        int p = 0;
        int num = i;
        int aux = 0;
        while(p < sz(primos) && primos[p] * primos[p] <= num){
            if(num % primos[p] == 0){
                aux++;
                num /= primos[p];
            }
            p++;
        }
        if(num > 1) aux++;

        if(!(aux & 1)) cnt[i] *= -1;

        // cout<<"i -> "<<i<<" cnt -> "<<cnt[i]<<endl;
    }

    int q; cin>>q;
    while(q--){
        int num; cin>>num;
        if(num == 1){
            cout<<pot2[n]<<endl;
            continue;
        }
        num = change(num);
        int m = cnt[num];
        for(int r = 2; r*r < num; r++){
            if(num % r == 0){
                m += cnt[r];
                m += cnt[num/r];
            }
        }
        int r = sqrt(n);
        if(r*r == num) m += cnt[r];

        cout<<pot2[n-m]<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calc();
    sieve();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
