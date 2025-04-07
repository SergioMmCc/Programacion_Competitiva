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

const int mod = 1e9 + 7;

int mod_inverse(int a) {
    ll i = mod, v = 0, d = 1;
    while(a > 0) {
        int t = i/a, x = a;
        a = i%x;
        i = x;
        x = d;
        d = v - t*x;
        v = x;
    }
    v %= mod;
    if(v < 0)
        v += mod;
    return v;
}

void solver(){
    int n, x; cin>>n;
    x = (n * (n+1)) / 2;
    if(x % 2){
        cout<<0<<endl;
        return;
    }

    x /= 2;
    vector<vector<int>> dp(n+1, vector<int>(x+1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x; j++){
            dp[i][j] = dp[i-1][j];
            if(j - i >= 0){
                dp[i][j] += dp[i-1][j-i];
                dp[i][j] %= mod;
            }
        }
    }

    int i2 = mod_inverse(2);
    cout<<((ll)i2 * (ll)dp[n][x]) % mod<<endl;
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