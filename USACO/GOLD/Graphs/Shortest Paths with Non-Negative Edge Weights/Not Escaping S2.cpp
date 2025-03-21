#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, ll> pil;

const int maxn = 2e5 + 5;
const ll inf = 2e18, poti = 1e12, take = 1e6;
vector<vector<pil>> graph(maxn);

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
bool spfa(int s, int n, vector<ll>& d){
    for(int i = 1; i <= n; i++) d[i] = inf;
    d[s] = 0;
    vector<bool> in(n+1);
    in[s] = 1;
    vector<int> count(n+1);
    deque<int> q;
    q.push_front(s);

    int mini = 2, maxi = sqrt(n) + 5; 
    while(!q.empty()){
        int u = q.front(); q.pop_front();
        in[u] = 0; // Marca que el vertice ya no esta en la cola

        for(pil edge : graph[u]){
            int v = edge.first; ll w = edge.second;
            
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                if(!in[v]){ // Antes de agregar un vertice a la cola, verifica que no se encuentre ya en ella
                    in[v] = 1; // Marca que el vertice ahora esta en la cola

                    if(count[v] >= mini && count[v] <= maxi) q.push_front(v);
                    else q.push_back(v);

                    count[v]++;
                }
            }
        }
    }

    return 1; // No hay ciclos negativos
}

void solver(){
    int n, m, k; cin>>n>>m>>k;
    vector<ll> x(n+1);
    for(int i = 1; i <= n; i++) cin>>x[i];

    int index = 3;
    map<pii, int> T;
    T[{1, 1}] = 1; T[{n, m}] = 2;
    vector<set<int>> filas(n+1);
    filas[1].insert(1); filas[n].insert(m);

    for(int i = 0; i < k; i++){
        int a, b, c, d; ll w;
        cin>>a>>b>>c>>d>>w;
        w *= -1;
        filas[a].insert(b);
        filas[c].insert(d);

        int u, v;
        if(T.find({a, b}) != T.end()) u = T[{a, b}];
        else{
            u = index;
            T[{a, b}] = u;
            index++;
        }

        if(T.find({c, d}) != T.end()) v = T[{c, d}];
        else{
            v = index;
            T[{c, d}] = v;
            index++;
        }

        graph[u].pb({v, w});
    }

    for(int i = 1; i <= n; i++){
        if(filas[i].empty()) continue;
        int lastCol = *filas[i].begin();
        filas[i].erase(lastCol);
        for(int col : filas[i]){
            int u = T[{i, lastCol}], v = T[{i, col}];
            graph[u].pb({v, x[i] * ((ll)col - (ll)lastCol)});
            graph[v].pb({u, x[i] * ((ll)col - (ll)lastCol)});
            lastCol = col;
        }
    }

    vector<ll> d(index+1);
    spfa(1, index, d);

    if(d[2] == inf) cout<<"NO ESCAPE"<<endl;
    else cout<<d[2]<<endl;

    for(int i = 1; i <= index; i++) graph[i].clear();
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