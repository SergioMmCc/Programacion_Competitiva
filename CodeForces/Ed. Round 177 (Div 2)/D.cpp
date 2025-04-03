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
    vector<int> c(26);
    int total = 0;
    for(int i = 0; i < 26; i++){
        cin>>c[i];
        total += c[i];
    }

    int n = 26, x = total / 2;

    vector<vector<int>> dp(n+1, vector<int> (x+1));
    dp[0][0] = 1;
 
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x; j++){
            dp[i][j] = dp[i-1][j];
            if(j - c[i-1] >= 0){
                dp[i][j] += dp[i-1][j - c[i-1]];
                dp[i][j] %= mod;
            }
        }
    }


}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}