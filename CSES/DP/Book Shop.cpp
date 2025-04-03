#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

int main(){
    // ios_base::sync_with_stdio(0);cin.tie(NULL);
    
    int n, w; cin>>n>>w;
    vector<int> peso(n+1), valor(n+1);
    for(int i = 1; i <= n; i++) cin>>peso[i];
    for(int i = 1; i <= n; i++) cin>>valor[i];

    vector<vector<int>> dp(n+1, vector<int>(w+1));

    for(int i = 1; i <= n; i++){
        int pesoAux = peso[i], valorAux = valor[i];
        for(int j = 1; j <= w; j++){
            dp[i][j] = dp[i-1][j];
            if(j - pesoAux >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j - pesoAux] + valorAux);
        }
    }

    cout<<dp[n][w]<<endl;

    return 0;
}