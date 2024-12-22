#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 201;
const ll inf = 1e5;
ll matriz[maxn][maxn], table[maxn][maxn][maxn], dp[maxn][maxn][maxn];

void fillTable(ll n, ll m, ll k){
    for(int i = 1; i <= n; i++){
        for(int jl = 1; jl <= m; jl++){
            ll sum = 0; 
            for(int jr = jl, count = 1; count <= m; jr++, count++){
                if(jr == m + 1) jr = 1;
                sum += matriz[i][jr];
                table[i][jl][jr] = sum;
            }
        }
    }
}

void solver(){
    ll n, m, k; cin>>n>>m>>k;

    // Limpiar dp
    for(int i = 1; i <= n; i++){
        for(int jl = 1; jl <= m; jl++){
            for(int jr = 1; jr <= m; jr++){
                dp[i][jl][jr] = inf;
            }
        }
    }

    // Lectura de la matriz
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin>>matriz[i][j];
        }
    }

    fillTable(n, m, k);

    // Testear fillTable
    for(int i = 1; i <= n; i++){
        cout<<"Fila "<<i<<":"<<endl;
        for(int jl = 1; jl <= m; jl++){
            for(int jr = jl, count = 1; count <= m; jr++, count++){
                if(jr > m) jr = 1;
                cout<<table[i][jl][jr]<<' ';
            }
            cout<<endl;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}