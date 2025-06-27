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
typedef pair<pii, bool> piib;

bool best(pii a, pii b){ // 1 si elijo a, 0 si eliijo b
    if(a.fi == b.fi) return a.se < b.se;
    return a.fi > b.fi;
}

void solver(){
    int n; cin>>n;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++) cin>>a[i];
    int m; cin>>m;
    vector<int> b(m+1);
    for(int i = 1; i <= m; i++) cin>>b[i];

    vector<vector<pii>> dp(n+1, vector<pii> (m+1, {0, -1}));
    vector<vector<piib>> par(n+1, vector<piib> (m+1));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(best(dp[i-1][j], dp[i][j-1])){
                dp[i][j] = dp[i-1][j];
                par[i][j] = {{i-1, j}, 0};
            }
            else{
                dp[i][j] = dp[i][j-1];
                par[i][j] = {{i, j-1}, 0};
            }

            if(a[i] == b[j]){
                for(int k = 0; k < i; k++){
                    if(a[i] > dp[k][j-1].se){
                        pii test = {dp[k][j-1].fi + 1, a[i]};
                        if(best(test, dp[i][j])){
                            dp[i][j] = test;
                            par[i][j] = {{k, j-1}, 1};
                        }
                    }
                }
            }
        }
    }

    cout<<dp[n][m].fi<<endl;
    int y = n, x = m;
    stack<int> ans;
    while(dp[y][x].fi){
        if(par[y][x].se) ans.push(a[y]);

        int aux = x;
        x = par[y][x].fi.se;
        y = par[y][aux].fi.fi;
    }

    while(!ans.empty()){
        cout<<ans.top()<<' ';
        ans.pop();
    }
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