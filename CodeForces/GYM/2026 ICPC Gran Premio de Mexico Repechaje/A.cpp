#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin>>n>>q;

    vector<long long> vec(n+1), dp(n+3);
    dp[n+1] = -1e12;
    for(int i=1; i<=n; i++)cin>>vec[i];

    for(int i=n; i>=1; i--){
        dp[i] = max(vec[i], dp[i+1]+vec[i]);
    }



    //for(int x : vec) cout<<x<<" ";cout<<"\n";
    //for(int x : dp) cout<<x<<" ";cout<<"\n";

    for(int i=n; i>=0; i--) dp[i] = max(dp[i], dp[i+1]);
    //for(int x : dp) cout<<x<<" ";cout<<"\n";

    int x;
    while(q--){
        cin>>x;
        cout<<dp[x+1]<<"\n";
    }

}
