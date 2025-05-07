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

const int mod = 1e9 + 7;

void solver(){
    int n, m; cin>>n>>m;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++) cin>>a[i];

    vector<vector<int>> dp(n+1, vector<int>(m+1));

    if(a[1]) dp[1][a[1]] = 1;
    else{
        for(int j = 1; j <= m; j++){
            dp[1][j] = 1;
        }
    }

    for(int i = 2; i <= n; i++){
        if(a[i]){
            int j = a[i];
            dp[i][j] = dp[i-1][j];
            if(j > 1){
                dp[i][j] += dp[i-1][j-1];
                dp[i][j] %= mod;
            }
            if(j < m){
                dp[i][j] += dp[i-1][j+1];
                dp[i][j] %= mod;
            }

            continue;
        }

        for(int j = 1; j <= m; j++){
            dp[i][j] = dp[i-1][j];
            if(j > 1){
                dp[i][j] += dp[i-1][j-1];
                dp[i][j] %= mod;
            }
            if(j < m){
                dp[i][j] += dp[i-1][j+1];
                dp[i][j] %= mod;
            }
        }
    }

    int ans = 0;
    for(int j = 1; j <= m; j++){
        ans += dp[n][j];
        ans %= mod;
    }

    cout<<ans<<endl;
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