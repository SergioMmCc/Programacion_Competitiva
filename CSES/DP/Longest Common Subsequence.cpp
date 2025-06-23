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
typedef pair<pii, pii> piiii;

void solver(){
    int n, m; cin>>n>>m;
    vector<int> a(n+1), b(n+1);
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) cin>>b[i];

    vector<vector<piiii>> dp(n+1, vector<piiii>(m+1));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i] == b[j]) dp[i][j] = {{dp[i-1][j-1].fi.fi + 1, 1}, {i-1, j-1}};
            if(dp[i-1][j] > dp[i][j]) dp[i][j] = {{dp[i-1][j].fi.fi, 0}, {i-1, j}};
            if(dp[i][j-1] > dp[i][j]) dp[i][j] = {{dp[i][j-1].fi.fi, 0}, {i, j-1}};
        }
    }
    // cout<<dp[n][m].fi.fi<<endl;

    stack<int> ans;
    int len = dp[n][m].fi.fi;
    int y = n, x = m;
    while(y && x){
        if(dp[y][x].fi.se) ans.push(a[y]);

        int aux = y;
        y = dp[y][x].se.fi;
        x = dp[aux][x].se.se;
    }

    cout<<len<<endl;
    while(!ans.empty()){
        cout<<ans.top()<<' ';
        ans.pop();
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