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

void pos(vi& a){

}

void solver(){
    int n, k; cin>>n>>k;

    vi ans(8e7);
    int idx = 1;
    vector<vi> mac(1);
    while(n--){
        char op; cin>>op;
        if(op == 'C'){
            int m; cin>>m;
            vi cre(8);
            for0(i,m){
                int num; cin>>num;
                cre[num-1]++;
            }
            mac.pb(cre);
            
            int num = 0;
            for0(i0,cre[0]+1){
                num += i0;
                for0(i1,cre[1]+1){
                    num += 10 * i1;
                    for0(i2,cre[2]+1){
                        num += 100 * i2;
                        for0(i3, cre[3]+1){
                            num += 1000 * i3;
                            for0(i4,cre[4]+1){
                                num += 10000 * i4;
                                for0(i5,cre[5]+1){
                                    num += 100000 * i5;
                                    for0(i6,cre[6]+1){
                                        num += 1000000 * i6;
                                        for0(i7,cre[7]+1){
                                            num += 10000000 * i7;
                                            ans[num]++;
                                            num -= 10000000 * i7;
                                        }
                                        num -= 1000000 * i6;
                                    }
                                    num -= 100000 * i5;
                                }
                                num -= 10000 * i4;
                            }
                            num -= 1000 * i3;
                        }
                        num -= 100 * i2;
                    }
                    num -= 10 * i1;
                }
                num -= i0;
            }

            idx++;
        }
        else if(op == 'D'){
            int jdx; cin>>jdx;
            vi cre = mac[jdx];
            int num = 0;
            for0(i0,cre[0]+1){
                num += i0;
                for0(i1,cre[1]+1){
                    num += 10 * i1;
                    for0(i2,cre[2]+1){
                        num += 100 * i2;
                        for0(i3, cre[3]+1){
                            num += 1000 * i3;
                            for0(i4,cre[4]+1){
                                num += 10000 * i4;
                                for0(i5,cre[5]+1){
                                    num += 100000 * i5;
                                    for0(i6,cre[6]+1){
                                        num += 1000000 * i6;
                                        for0(i7,cre[7]+1){
                                            num += 10000000 * i7;
                                            ans[num]--;
                                            num -= 10000000 * i7;
                                        }
                                        num -= 1000000 * i6;
                                    }
                                    num -= 100000 * i5;
                                }
                                num -= 10000 * i4;
                            }
                            num -= 1000 * i3;
                        }
                        num -= 100 * i2;
                    }
                    num -= 10 * i1;
                }
                num -= i0;
            }
        }
        else{
            int m; cin>>m;
            vi cre(8);
            for0(i,m){
                int num; cin>>num;
                cre[num-1]++;
            }

            int num = cre[0] + 10*cre[1] + 100*cre[2] + 1000*cre[3] + 10000*cre[4] + 100000*cre[5] + 1000000*cre[6] + 10000000*cre[7];

            cout<<ans[num]<<endl;
        }
    }
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
