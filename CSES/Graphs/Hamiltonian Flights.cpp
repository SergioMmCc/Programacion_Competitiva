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

vector<vector<int>> graph(20);
vector<int> pot2(21);
void calcPot2(){
    pot2[0] = 1;
    for(int i = 1; i < 21; i++) pot2[i] = pot2[i-1] * 2;
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        u--; v--;
        graph[u].pb(v);
    }

    int lim = pot2[n];
    // cout<<n<<' '<<lim<<endl;
    vector<vector<int>> dp(n, vector<int>(lim));
    dp[0][1] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 1; j < lim; j++){

            cout<<"i -> "<<i<<" j -> "<<j<<" dp -> "<<dp[i][j]<<endl;
            vector<bool> vis(n);
            int aux = j;
            for(int k = 0; k < n; k++){
                if(aux % 2) vis[k] = 1;
                aux >>= 1;
            }

            if(!vis[i]) continue;

            for(int v : graph[i]){
                if(vis[v]) continue;
                dp[v][j + pot2[v]] += dp[i][j];
                dp[v][j + pot2[v]] %= mod;
                // cout<<"sum -> "<<" v -> "<<v<<" valor -> "<<lim+pot2[v]
            }
        }
    }

    cout<<dp[n-1][lim - 1]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    calcPot2();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}