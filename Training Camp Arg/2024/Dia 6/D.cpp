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

map<int, int> nums;
map<int, int> save;
void calcpot2(){
    for0(i,31){
        save[1 << i] = i+1;
    }
}

int go(int mask){
    if(!mask) return 0;
    if(save.find(mask) != save.end()) return save[mask];

    vb mex(35);
    for0(i,31){
        if((1 << i) > mask) break;
        int aux = 0;
        for0(j,31){
            if((mask & (1 << j)) && j < i) aux += (1 << j);
            if((mask & (1 << j)) && j - i - 1 >= 0){
                aux |= 1 << (j - i - 1);
            }
        }

        // cout<<"mask -> "<<mask<<" aux -> "<<aux<<endl;

        mex[go(aux)] = 1;
    }

    for0(i,35){
        if(!mex[i]){
            save[mask] = i;
            return i;
        }
    }

    assert(0);
}

void solver(){
    int n; cin>>n;
    for0(i,n){
        int num; cin>>num;
        for(int d = 2; d*d <= num; d++){
            if(num % d == 0){
                int cnt = -1;
                while(num % d == 0){
                    cnt++;
                    num /= d;
                }

                if(nums.find(d) == nums.end() || !(nums[d] & (1 << cnt))) nums[d] += (1 << cnt);
            }
        }
        if(num > 1){
            if(nums.find(num) == nums.end() || !(nums[num] & 1)) nums[num]++;
        }
    }

    int ans = 0;
    for(const auto& x : nums){
        ans ^= go(x.se);
    }

    cout<<(ans ? "Mojtaba" : "Arpa")<<endl;
}

int main(){
    // ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    calcpot2();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}