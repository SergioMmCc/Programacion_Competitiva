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

const int mod = 1e9 + 7, maxn = 20;
int dp[maxn][1 << maxn];
vector<vector<int>> graph(20);

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        u--; v--;
        graph[u].pb(v);
    }

    int lim = 1 << n;
    dp[0][1] = 1;
    for(int j = 1; j < lim; j++){

        // Estos 2 ifs eliminan muchas posibilidades, así que pueden ayudar a evitar TLE
        if(!(j & 1)) continue; // Si no he pasado por la fuente (1 << s)
        if(j & (1 << (n-1)) && j < lim - 1) continue; // Si llego al destino sin haber pasado por los demas (1 << d)

        for(int i = 0; i < n; i++){

            if(!(j & (1 << i))) continue;

            for(int v : graph[i]){
                if(j & (1 << v)) continue;
                dp[v][j | (1 << v)] += dp[i][j];
                dp[v][j | (1 << v)] %= mod;
            }
        }
    }

    cout<<dp[n-1][lim - 1]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}