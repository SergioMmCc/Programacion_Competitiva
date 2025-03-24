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

const int maxn = 1e5 + 1;
const ll inf = 1e15;
vector<ll> h(maxn), dp(maxn, inf);

ll calc(int n){
    if(dp[n] != inf) return dp[n];

    if(n > 1) dp[n] = min(dp[n], (ll)abs(h[n] - h[n-1]) + calc(n-1));
    if(n >  2) dp[n] = min(dp[n], abs(h[n] - h[n-2]) + calc(n-2));

    return dp[n];
}

void solver(){
    int n; cin>>n;
    for(int i = 1; i <= n; i++) cin>>h[i];
    cout<<calc(n)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    dp[1] = 0;
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}