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

void rotate(int n, vector<vi>& a){
    vector<vi> aux = a;
    for0(i,n){
        for0(j,n){
            aux[j][n-i-1] = a[i][j];
        }
    }
    a = aux;
}

void solver(){
    int n; cin>>n;
    vector<vi> a(n, vi(n));
    for0(i,n){
        for0(j,n){
            cin>>a[i][j];
        }
    }

    int cnt = 0;
    while(cnt <= 3){
        // for0(i,n){
        //     for0(j,n){
        //         cout<<a[i][j]<<' ';
        //     }
        //     cout<<endl;
        // }
        bool cond = 1;
        for0(i,n){
            for1(j,n-1){
                if(a[i][j] < a[i][j-1]){
                    cond = 0;
                    break;
                }
            }
            if(!cond) break;
        }

        if(!cond){
            cnt++;
            rotate(n, a);
            continue;
        }

        for0(j,n){
            for1(i,n-1){
                if(a[i][j] < a[i-1][j]){
                    cond = 0;
                    break;
                }
            }
            if(!cond) break;
        }

        if(cond){
            cout<<(4 - cnt) % 4<<endl;
            return;
        }

        cnt++;
        rotate(n, a);
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
