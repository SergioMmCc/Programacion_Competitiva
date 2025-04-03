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

const int mod = 998244353;

void solver(){
    int q, k; cin>>q>>k;

    vector<vector<int>> dp(q + 1, vector<int>(k + 1));
    dp[0][0] = 1;

    for(int i = 1; i <= q; i++){
        char op; int num; cin>>op>>num;
        for(int j = 0; j <= k; j++){
            if(op == '+'){
                dp[i][j] = dp[i-1][j];
                if(j - num >= 0){
                    dp[i][j] += dp[i-1][j-num];
                    dp[i][j] %= mod;
                }
            }
            else{
                if(j == num) dp[i][j] = (mod + dp[i-1][j] - 1) % mod;
                else if(j > num) dp[i][j] = (mod + dp[i-1][j] - dp[i][j-num]) % mod;
                else dp[i][j] = dp[i-1][j];
            }
        }

        cout<<dp[i][k]<<endl;
    }
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