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
    int n; cin>>n;
    vector<int> coins(n+1);
    for(int i = 1; i <= n; i++) cin>>coins[i];

    int x = 1000 * n;
    vector<vector<bool>> dp(n+1, vector<bool> (x + 1));
    dp[0][0] = 1;

    for(int i = 1; i <= n; i++){
        int valor = coins[i];
        for(int j = 0; j <= x; j++){
            dp[i][j] = dp[i-1][j];

            if(j - valor >= 0) dp[i][j] = dp[i-1][j] | dp[i-1][j - valor];
        }
    }

    vector<int> ans;
    for(int i = 1; i <= x; i++){
        if(dp[n][i]) ans.pb(i);
    }

    cout<<ans.sz<<endl;
    for(int i = 0; i < ans.sz; i++){
        if(i) cout<<' ';
        cout<<ans[i];
    }
    cout<<endl;
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