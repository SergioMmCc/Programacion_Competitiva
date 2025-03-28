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

const int maxn = 501;
bool dp[maxn][maxn][maxn];
vector<int> coins;

void solver(){
    int n, valor; cin>>n>>valor;
    coins.pb(0);
    for(int i = 0; i < n; i++){
        int save; cin>>save;
        coins.pb(save);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= valor; j++){
            for(int k = 0; k <= valor; k++){
                if(!dp[i][j][k]) continue;

                dp[i+1][j][k] = 1;
                
                if(j + coins[i+1] > valor) continue;
                
                dp[i+1][j + coins[i+1]][k + coins[i+1]] = 1;
                dp[i+1][j + coins[i+1]][k] = 1;
            }
        }
    }

    vector<int> ans;
    for(int i = 0; i <= valor; i++){
        if(dp[n][valor][i]) ans.pb(i);
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
    dp[0][0][0] = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}