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

const int maxn = 1e6 + 1, mod = 1e9 + 7;
vector<int> dp(maxn, -1);

int calc(int n){
    if(dp[n] != -1) return dp[n];
    dp[n] = 0;

    for(int i = 1; i <= 6; i++){
        if(n - i < 0) break;
        dp[n] += calc(n-i);
        dp[n] %= mod;
    }

    return dp[n];
}

void solver(){
    int n; cin>>n;
    cout<<calc(n)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    dp[0] = 1;
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}