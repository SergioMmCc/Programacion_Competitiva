#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forn0(i,n) for(int i = (int)n-1; i >= 0; i--)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define pb push_back
#define sz(a) (int)a.size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

void solver(int n, int m){
    string s; cin>>s;
    vi par(1), imp(1);
    for0(i,n){
        if(i & 1) imp.pb(s[i] - '0');
        else par.pb(s[i] - '0');
    }

    int ans = 0;
    vi psp(1), psi(1);
    for1(i, sz(par) - 1){
        psp.pb(par[i] + psp.back());
        if(i < m) ans = max(ans, psp.back());
        else ans = max(ans, psp.back() - psp[i-m]);
    }
    for1(i, sz(imp) - 1){
        psi.pb(imp[i] + psi.back());
        if(i < m) ans = max(ans, psi.back());
        else ans = max(ans, psi.back() - psi[i-m]);
    }

    cout<<ans<<endl;
}   

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m;
    while(cin>>n>>m){
        if(!n) break;
        solver(n, m);
    }

    return 0;
}