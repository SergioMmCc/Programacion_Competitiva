#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, ll> pil;

// Estructura para almacenar todas las aristas
struct edge {
    int u, v; ll w;

    // Ordenar las aristas por el menor peso
    bool operator<(const edge& that) const {
        return w < that.w; // Cambiar '<' por '>' para hallar el Maximal Spanning Tree
    }
};

const int maxn = 2005;
const ll inf = 1e15;
int components;
vector<int> leader(maxn), sizen(maxn);
vector<vector<pil>> graph(maxn);
ll d[maxn][maxn];

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sizen[i] = 1;
    }
}

int find(int u){
    if(leader[u] != u)
        leader[u] = find(leader[u]);
    return leader[u];
}

void join(int u, int v){
    int leaderU = find(u), leaderV = find(v);
    if(leaderU != leaderV){
        if(sizen[leaderV] > sizen[leaderU])
            swap(leaderU, leaderV);
        leader[leaderV] = leaderU;
        sizen[leaderU] += sizen[leaderV];
        components--;
    }
}

// Algoritmo de Kruskal para hallar el Minimal Spanning Tree
// Complejidad O(m * lg(m))
// En grafos densos m ≈ n²
ll kruskal(vector<edge>& edges, int n){
    ll total = 0;
    sort(edges.begin(), edges.end());
    initDSU(n);

    for(int i = 0; i < edges.sz; i++){
        int u = edges[i].u, v = edges[i].v; ll w = edges[i].w;
        if(find(u) != find(v)){
            total += w;
            join(u, v);
            graph[u].pb({v, w});
            graph[v].pb({u, w});
        }
    }

    return total; // Retornar el peso total del MST
}

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int s, int n){
    for(int i = 1; i <= n; i++) d[s][i] = inf;
    d[s][s] = 0;
    priority_queue<pil, vector<pil>, comp> pq;
    pq.push({s, 0});
    while(!pq.empty()){
        int u = pq.top().first; ll w1 = pq.top().second;
        pq.pop();
        if(d[s][u] < w1) continue;
        for(pil edge : graph[u]){
            int v = edge.first; ll w2 = edge.second;
            if(d[s][v] > w1 + w2){
                d[s][v] = w1 + w2;
                pq.push({v, d[s][v]});
            }
        }
    }
}

void solver(){
    int n; cin>>n;
    ll table[n+1][n+1];
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin>>table[i][j];
        }
    }

    vector<edge> edges;
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            if((i == j && table[i][j]) || ((i != j) && (table[i][j] != table[j][i] || !table[i][j]))){
                cout<<"NO"<<endl;
                return;
            }
            
            if(i != j) edges.pb({i, j, table[i][j]});
        }
    }

    kruskal(edges, n);
    for(int i = 1; i <= n; i++) dijkstra(i, n);

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(table[i][j] != d[i][j]){
                cout<<"NO"<<endl;
                return;
            }
        }
    }

    cout<<"YES"<<endl;
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