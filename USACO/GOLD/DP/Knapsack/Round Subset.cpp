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
    int n, m, p = 0; cin>>n>>m;

    vector<pii> a(n+1);
    for(int i = 1; i <= n; i++){
        ll save; cin>>save;
        int count2 = 0, count5 = 0;
        while(save % 2 == 0){
            count2++;
            save /= 2;
        }
        while(save % 5 == 0){
            count5++;
            save /= 5;
        }

        p += count5;
        a[i] = {count2, count5};
    }

    vector<vector<vector<int>>> dp(2, vector<vector<int>>(m+1, vector<int>(p+1)));
    vector<vector<vector<bool>>>pos(2, vector<vector<bool>>(m+1, vector<bool>(p+1)));
    pos[0][0][0] = 1;

    int ans = 0;
    for(int ind = 1; ind <= n; ind++){
        int c2 = a[ind].fi, c5 = a[ind].se;
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= p; k++){
                int i = ind % 2;
                if(pos[i ^ 1][j][k]){
                    pos[i][j][k] = 1;
                    dp[i][j][k] = dp[i ^ 1][j][k];
                }
                if(j && k - c5 >= 0 && pos[i ^ 1][j-1][k - c5]){
                    pos[i][j][k] = 1;
                    dp[i][j][k] = max(dp[i][j][k], dp[i ^ 1][j-1][k - c5] + c2);
                }
                if(pos[i][j][k]) ans = max(ans, min(k, dp[i][j][k]));
            }
        }
    }

    cout<<ans<<endl;
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