#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forn0(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int maxn = 1e6;
vi pa;
int cnt[maxn], dia[maxn];
ll dp[maxn], re[maxn];
int n;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    
    int n; cin>>n;
    pa.pb(-1);
    for1(i,n-1){
        int p; cin>>p;
        pa.pb(p-1);
    }
    forn0(i,n){
        cnt[i]++;
        if(!i) break;
        dp[pa[i]] += dp[i] + (ll)cnt[i];
        cnt[pa[i]] += cnt[i];
    }
    for1(i,n-1) re[i] = re[pa[i]] + dp[pa[i]] - dp[i] - (ll)2*(ll)cnt[i] + (ll)n;
    ll ans1 = 0;
    for0(i,n) ans1 += re[i] + dp[i];
    ans1 /= 2;
    cout<<ans1<<endl;
    
    vii aux(n);
    forn0(i,n){
        dia[i] = max(dia[i], aux[i].fi + aux[i].se);
        if(!i) break;

        dia[pa[i]] = max(dia[pa[i]], dia[i]);
        if(aux[i].fi + 1 > aux[pa[i]].fi){
            aux[pa[i]].se = aux[pa[i]].fi;
            aux[pa[i]].fi = aux[i].fi + 1;
        }
        else if(aux[i].fi + 1 > aux[pa[i]].se) aux[pa[i]].se = aux[i].fi + 1;
    }

    
    for0(i, n){
        if(i) cout<<' ';
        cout<<dia[i];
    }
    cout<<endl;

    return 0;
}
