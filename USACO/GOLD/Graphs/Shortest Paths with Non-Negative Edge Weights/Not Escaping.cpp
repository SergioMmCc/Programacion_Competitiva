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
bool dijkstra(int source, int n, vector<ll>& d, vector<ll>& p){
    bool cond = 0;
    for(int i = 1; i <= n; i++) d[i] = inf;
    d[source] = 0;
    priority_queue<pil, vector<pil>, comp> pq;
    pq.push({source, 0});
    while(!pq.empty()){
        int u = pq.top().first; ll w1 = pq.top().second;
        pq.pop();
        if(d[u] < w1) continue;
        for(pil edge : graph[u]){
            int v = edge.first; ll w2 = edge.second;
            w2 += p[u] - p[v];
            if(v == 2) cond = 1;
            if(d[v] > w1 + w2){
                d[v] = w1 + w2;
                pq.push({v, d[v]});
            }
        }
    }

    return cond;
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
    vector<ll> p(3);
    p[1] = poti - take; p[2] = poti - n * take;

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
            p.pb(poti - a * take);
            T[{a, b}] = u;
            index++;
        }

        if(T.find({c, d}) != T.end()) v = T[{c, d}];
        else{
            v = index;
            p.pb(poti - c * take);
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
    bool cond = dijkstra(1, index, d, p);

    if(!cond) cout<<"NO ESCAPE"<<endl;
    else cout<<d[2] - p[1] + p[2]<<endl;

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