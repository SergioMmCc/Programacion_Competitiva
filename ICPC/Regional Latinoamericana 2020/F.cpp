#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
const ll INF = 1e18;

void solver() {
    int n;cin>>n;
    vll a(n+1,INF);
    for(int i=1;i<=n;i++)cin>>a[i];
    vll pdp(n+1,INF),dp(n+1,INF),bst(n+1);
    vi prv(n+1);
    pdp[0]=0;
    vll sa(a.begin()+1,a.end());
    sort(sa.rbegin(),sa.rend());
    ll mx=0;
    for(int k=1;k<=n;k++) {
        dp[0]=INF;
        for(int i=1;i<=n;i++) {
            int p=i-1;
            bst[i]=pdp[p];
            while(a[p]<=a[i]) {
                bst[i]=min(bst[i],bst[p]);
                p=prv[p];
            }
            prv[i]=p;
            dp[i]=min(dp[p],bst[i]+a[i]);
        }
        mx+=sa[k-1];
        cout<<dp[n]<<" "<<mx<<"\n";
        swap(pdp,dp);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; //cin >> t;
    while (t--) solver();
}