#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define int long long
typedef pair<int, int> pii;

const int maxn = 101, inf = 1e15;
int d[maxn][maxn], dp[5001][2]; bool visited[5001][2];
vector<pii> queries;

void floyd(int n){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
}

int calc(int index, int op, int n){
    if(visited[index][op] || !index) return dp[index][op];

    int sum;
    int aux1 = index, aux2 = op;

    if(index == n && op) sum = 0;
    else{
        if(op){
            sum = d[queries[index+1].first][queries[index].second];
            index++;
            op = 0;
        }
        else{
            sum = d[queries[index-1].second][queries[index].first];
            index--;
            op = 1;
        }
    }

    if(op){
        dp[aux1][aux2] = min(dp[aux1][aux2], calc(index, 0, n) + sum + d[queries[index].first][queries[index].second]);
        if(index > 1)
        dp[aux1][aux2] = min(dp[aux1][aux2], calc(index - 1, 1, n) + sum + d[queries[index].second][queries[index-1].second]);
    }
    else{
        dp[aux1][aux2] = min(dp[aux1][aux2], calc(index - 1, 0, n) + sum + d[queries[index].first][queries[index-1].first]);
        if(index > 2)
        dp[aux1][aux2] = min(dp[aux1][aux2], calc(index - 2, 1, n) + sum + d[queries[index].first][queries[index-2].second]);
    }

    // cout<<"index -> "<<aux1<<" op -> "<<aux2<<" sum -> "<<sum<<" ans -> "<<dp[aux1][aux2]<<endl;
    visited[aux1][aux2] = 1;
    return dp[aux1][aux2];
}

void solver(){
    int n, m, k; cin>>n>>m>>k;

    queries.clear(); queries.pb({0, 0});
    for(int i = 1; i < n; i++){
        for(int j = i + 1; j <= n; j++){
            d[i][j] = d[j][i] = inf;
        }
    }
    for(int i = 0; i <= k; i++){
        for(int j = 0; j < 2; j++){
            dp[i][j] = inf;
            visited[i][j] = 0;
        }
    }
    for(int i = 0; i < m; i++){
        int u, v, w; cin>>u>>v>>w;
        if(d[u][v] > w) d[u][v] = d[v][u] = w;
    }

    floyd(n);
    // for(int i = 1; i <= n; i++){
    //     for(int j = 1; j <= n; j++){
    //         cout<<(d[i][j] == inf ? -1 : d[i][j])<<'\t';
    //     }
    //     cout<<endl;
    // }
    for(int i = 0; i < k; i++){
        int u, v; cin>>u>>v;
        queries.pb({u, v});
    }

    if(d[1][queries[0].first] == inf){
        cout<<-1<<endl;
        return;
    }

    dp[1][0] = d[1][queries[1].first]; visited[1][0] = 1;
    int ans = calc(k, 1, k);
    // for(int i = 1; i <= k; i++){
    //     cout<<(dp[i][0] == inf ? -1 : dp[i][0])<<' '<<(dp[i][1] == inf ? -1 : dp[i][1])<<endl;
    // }

    cout<<(ans == inf ? -1 : ans)<<endl;;
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    for(int i = 1; i <= t; i++){
        cout<<"Case #"<<i<<": ";
        solver();
    }

    return 0;
}