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

string toLow(string& s){
    string ans = "";
    for0(i,sz(s)){
        if(s[i] >= 'A' && s[i] <= 'Z') ans += (s[i] - 'A' + 'a');
        else ans += s[i];
    }

    return ans;
}

void solver(){
    string s; cin>>s;
    // cout<<toLow(s)<<endl;
    map<int, string> is;
    map<string, int> si;
    map<string, string> ss;

    string aux = "";
    int idx = 0;
    int last = 0, last2 = 0;
    vi a;
    for0(i,sz(s)){
        if(s[i] == '!'){
            string c = toLow(aux);
            if(ss.find(c) == ss.end()){
                ss[c] = aux;
                is[idx] = c;
                si[c] = idx;
                a.pb(idx);
                idx++;
            }
            else {a.pb(si[c]);}
            aux = "";
            continue;
        }

        aux += s[i];
    }
    if(aux != ""){
        string c = toLow(aux);
        if(ss.find(c) == ss.end()){
            ss[c] = aux;
            is[idx] = c;
            si[c] = idx;
            a.pb(idx);
            idx++;
        }
        else {a.pb(si[c]);}
    }

    if(sz(a) == 1){
        cout<<ss[is[a[0]]]<<endl;
        return;
    }

    vi ans; ans.pb(a[0]);
    for1(i,sz(a)-2){
        if(a[i] == ans.back()) continue;
        if(sz(ans) >= 2 && ans[sz(ans) - 2] == a[i]){
            ans.pop_back();
            continue;
        }

        ans.pb(a[i]);
    }

    for(int x : ans) cout<<ss[is[x]]<<'!';
    cout<<ss[is[a.back()]]<<endl;
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
