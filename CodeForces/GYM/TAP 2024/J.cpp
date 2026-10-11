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

void solver(){
    int n, x; cin>>n>>x;
    map<int, int> freq;
    for0(i,n){
        int num; cin>>num;
        freq[num]++;
    }

    if((x & 1) || freq.find(x / 2) == freq.end()){
        vi pl, pr, pm;
        for(const auto& par : freq){
            int aux = par.fi;
            if(freq.find(x - aux) == freq.end()) pm.pb(aux);
            else if(x - aux > aux) pl.pb(aux);
            else pr.pb(aux);
        }
        if(sz(freq) == 2 && sz(pl) == 1){
            cout<<'*'<<endl;
            return;
        }

        vi ans;
        while(!pl.empty()){
            int aux = pl.back();
            for0(i,freq[aux]) ans.pb(aux);
            pl.pop_back();
        }
        while(!pm.empty()){
            int aux = pm.back();
            for0(i,freq[aux]) ans.pb(aux);
            pm.pop_back();
        }
        reverse(all(pr));
        while(!pr.empty()){
            int aux = pr.back();
            for0(i,freq[aux]) ans.pb(aux);
            pr.pop_back();
        }

        for(int x : ans) cout<<x<<' ';
        cout<<endl;
    }
    else{
        if(freq[x/2] > (n+1) / 2){
            cout<<'*'<<endl;
            return;
        }
        deque<int> ans;
        vi pl, pr, pm;
        for(const auto& par : freq){
            int aux = par.fi;
            if(aux == x/2) continue;
            if(freq.find(x - aux) == freq.end()) pm.pb(aux);
            else if(x - aux > aux) pl.pb(aux);
            else pr.pb(aux);
        }

        ans.pb(x/2);
        freq[x/2]--;
        for(int aux : pl){
            for0(i,freq[aux]){
                ans.pb(aux);
                if(freq[x/2]){
                    ans.pb(x/2);
                    freq[x/2]--;
                }
            }
        }

        for(int aux : pr){
            for0(i,freq[aux]){
                ans.push_front(aux);
                if(freq[x/2]){
                    ans.push_front(x/2);
                    freq[x/2]--;
                }
            }
        }
        for(int aux : pm){
            for0(i,freq[aux]){
                ans.push_front(aux);
                if(freq[x/2]){
                    ans.push_front(x/2);
                    freq[x/2]--;
                }
            }
        }

        while(!ans.empty()){
            cout<<ans.back()<<' ';
            ans.pop_back();
        }
        cout<<endl;
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
