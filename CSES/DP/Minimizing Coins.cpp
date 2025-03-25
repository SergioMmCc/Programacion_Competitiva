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

const int maxn = 1e6 + 1, inf = 1e9;
vector<int> dp(maxn, inf); vector<bool> visited(maxn);
vector<int> coins;

int calc(int n){
    if(visited[n]) return dp[n];
    visited[n] = 1;

    for(int coin : coins){
        if(n - coin < 0) break;

        dp[n] = min(dp[n], 1 + calc(n - coin));
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

    int ans = calc(x);
    cout<<(ans == inf ? -1 : ans)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    dp[0] = 0; visited[0] = 1;
    solver();

    return 0;
}