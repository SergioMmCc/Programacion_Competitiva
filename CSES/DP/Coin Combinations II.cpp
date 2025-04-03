#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
 
const int mod = 1e9 + 7;
int dp[101][1000001];
vector<int> coins(101);

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    
    int n, x; cin>>n>>x;
    for(int i = 0; i < n; i++) cin>>coins[i];
 
    dp[0][0] = 1;
 
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x; j++){
            dp[i][j] = dp[i-1][j];
            if(j - coins[i-1] >= 0){
                dp[i][j] += dp[i-1][j - coins[i-1]];
                dp[i][j] %= mod;
            }
        }
    }
 
    cout<<dp[n][x]<<endl;
 
    return 0;
}