#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 501;
const ll inf = 1e18;
ll d[maxn][maxn];

void floyd(int n){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

void solver(){
    int n, m, q; cin>>n>>m>>q;
    for(int i = 1; i < n; i++){
        for(int j = i + 1; j <= n; j++){
            d[i][j] = d[j][i] = inf;
        }
    }
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin>>u>>v>>w;
        if(d[u][v] > w) d[u][v] = d[v][u] = w;
    }

    floyd(n);

    while(q--){
        int a, b; cin>>a>>b;
        cout<<(d[a][b] == inf ? -1 : d[a][b])<<endl;
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