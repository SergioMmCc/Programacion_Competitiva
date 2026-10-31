// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
long long tenmod[3000];
long long MOD = 1E9+7;

int trans(int x, int m, int d, int p){
    return (tenmod[1] * x + tenmod[m+1] * d + d) % p;
}

int main() {
    int n, p;
    cin>>n>>p;

    tenmod[0] = 1 % p;
    for(int i=1; i<=2007; i++){
        tenmod[i] = (tenmod[i-1] * 10) % p; 
    }

    int m = (n+1)/2;
    vector<vector<long long>> dp(n+3, vector<long long>(p));
    dp[0][0] = 1;
    for(int d=0; d<=9; d++)dp[1][d%p]++; 

    long long ans=1;
    for(int d=1; d<=9; d++) ans += (d%p) == 0;

    for(int i=0; i+2<=n; i++){
        for(int d=0; d<=9; d++){
            for(int x=0; x<p; x++){
                int nxt = trans(x, i, d, p);
                dp[i+2][nxt] += dp[i][x];
                dp[i+2][nxt] %= MOD;
                if(d >= 1 && nxt == 0){
                    ans += dp[i][x];
                    ans %= MOD;
                }
            }
        }
    }

    cout<<ans<<"\n";
}
