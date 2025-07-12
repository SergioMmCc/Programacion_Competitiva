#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;

void solver(){
    int n, x; cin>>n>>x;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin>>a[i];
    int limit = 1 << n;
    vector<pii> dp(limit, {n, 0}); dp[0] = {1, 0};
    for(int mask = 1; mask < limit; mask++){
        for(int i = 0; i < n; i++){
            if(mask & (1 << i) == 0) continue;
            int back = mask ^ (1 << i);
            int total = dp[back].fi, w = dp[back].se;
            if(w + a[i] > x){
                total++;
                w = a[i];
            }
            else w += a[i];
            
            dp[mask] = min(dp[mask], {total, w});
        }
    }

    cout<<dp[limit-1].fi<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}