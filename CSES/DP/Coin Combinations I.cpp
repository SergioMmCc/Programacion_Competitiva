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
vector<int> coins;

int calc(int n){
    if(dp[n] != -1) return dp[n];
    dp[n] = 0;

    for(int coin : coins){
        if(n - coin < 0) break;

        dp[n] += calc(n - coin);
        dp[n] %= mod;
    }

    return dp[n];
}

void solver(){
    int n, x; cin>>n>>x;
    for(int i = 0; i < n; i++){
        int save; cin>>save;
        coins.pb(save);
    }
    sort(coins.begin(), coins.end());

    cout<<calc(x)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    dp[0] = 1;
    solver();

    return 0;
}