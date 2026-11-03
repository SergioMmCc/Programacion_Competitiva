#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;

const int MOD = 1e9 + 7;

void solver() {
    int s, b;cin>>s>>b;
    int n=b-s;
    vector<vi>dp(n+1,vi(s+1,0));
    vector<vi>sum(n+1,vi(s+1,0));
    for(int j=1;j<=s;j++)
        dp[0][j] = 1;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=s;j++) {
            int s_val=sum[i][j - 1];
            if(i>=j)
                s_val=(s_val+dp[i-j][j])%MOD;
            sum[i][j]=s_val;
            dp[i][j]=(dp[i][j-1]+s_val)%MOD;
        }
    }
    cout<<dp[n][s]<<"\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1; 
    while (t--) solver();
}