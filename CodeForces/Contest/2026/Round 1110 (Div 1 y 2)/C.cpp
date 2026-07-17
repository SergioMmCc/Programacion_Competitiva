#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
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

vi pot2(20);
void calcPot2(){
    pot2[0] = 1;
    for(int i = 1; i < 20; i++) pot2[i] = pot2[i-1] * 2;
}

void solver(){
    int n, k; cin>>n>>k;

    int idx = 0;
    while(n >= pot2[idx]){
        if(n == pot2[idx]){
            if(n > k){
                cout<<"NO"<<endl;
                return;
            }
        }
        idx++;
    }
    int lim = pot2[idx] - 1;
    // db(lim)<<endl;
    if(k > lim){
        cout<<"NO"<<endl;
        return;
    }

    int x = n ^ k;
    vb skip(n);
    for(int i = 0; i < 20; i++){
        if((1 << i) >= n) break;
        skip[1 << i] = (1 << i) & x;
    }
    skip[0] = 1;

    cout<<"YES"<<endl;
    int aux = n;
    for(int i = 0; i < n; i++) if(!skip[i]) cout<<i<<' ';
    for(int i = 0; i < n; i++){
        if(skip[i]){
            cout<<i<<' ';
            aux ^= i;
        }
    }
    assert(aux == k);
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calcPot2();
    // for(int i = 0; i < 20; i++) db(pot2[i]);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
