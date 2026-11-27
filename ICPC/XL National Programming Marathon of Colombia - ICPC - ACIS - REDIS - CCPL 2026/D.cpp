#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forn0(i,n) for(int i = (int)n-1; i >= 0; i--)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<ll> vl;
typedef vector<pii> vii;



void solver(int n, int k, int b){
    vs a(n);

    vector<vi> bingo(n, vi(k));
    for0(i, n){
        string name; cin>>name;
        a[i] = name;
        for0(j, k) cin>>bingo[i][j];
    }

    vi nums(b), c(b);
    set<int> aux;
    map<int, int> com;
    int idx = 0;
    for0(i, b){
        cin>>nums[i];
        c[i] = nums[i];
    }
    sort(all(c));
    for0(i, b){
        if(com.find(c[i]) != com.end()) continue;
        com[c[i]] = idx;
        idx++;
    }

    vi app(idx, b);
    forn0(i, b) app[com[nums[i]]] = i;
    vector<vi> last(b);
    int mini = b;
    for0(i,n){
        int maxi = 0;
        for0(j,k){
            maxi = max(maxi, app[com[bingo[i][j]]]);
        }
        if(maxi > mini) continue;
        mini = maxi;
        last[mini].pb(i);
    }

    vs ans;
    for(int x : last[mini]) ans.pb(a[x]);
    sort(all(ans));
    for0(i, sz(ans)){
        if(i) cout<<' ';
        cout<<ans[i];
    }
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, k, b;
    while(cin>>n>>k>>b){
        if(n==0 && k==0 && b == 0) break;

        solver(n, k, b);
    }

    return 0;
}