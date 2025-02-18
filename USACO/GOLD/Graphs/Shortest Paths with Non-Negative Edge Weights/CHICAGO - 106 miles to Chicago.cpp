#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 101, inf = 2e9;
ld d[maxn][maxn];

// Complejidad O(n³)
void floyd(int n){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                d[i][j] = max(d[i][j], d[i][k] * d[k][j]);
            }
        }
    }
}

void solver(int n, int m){
    for(int i = 1; i < n; i++){
        for(int j = i + 1; j <= n; j++){
            d[i][j] = d[j][i] = 0.0;
        }
    }
    for(int i = 1; i <= n; i++) d[i][i] = 1.0;

    for(int i = 0; i < m; i++){
        int u, v; ld w; cin>>u>>v>>w;
        w /= 100;
        if(d[u][v] < w) d[u][v] = d[v][u] = w;
    }

    floyd(n);
    ld ans = d[1][n] * 100;
    cout<<fixed<<setprecision(6)<<ans<<" percent"<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    int n, m; cin>>n;
    while(n){
        int m; cin>>m;
        solver(n, m);
        cin>>n;
    }

    return 0;
}