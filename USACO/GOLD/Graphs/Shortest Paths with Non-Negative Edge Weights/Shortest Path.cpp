#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

const int maxn = 3001;
vector<vector<int>> graph(maxn);
bool visited[maxn][maxn];
int d[maxn][maxn];
pii parent[maxn][maxn];
set<piii> prohibited;

pii BFS(int n){
    visited[1][0] = 1;
    parent[1][0] = {0, 0};
    queue<pii> q; q.push({1, 0});
    while(!q.empty()){
        int u = q.front().first, prev = q.front().second; q.pop();
        for(int v : graph[u]){
            if(visited[v][u] || v == 1) continue;
            if(prohibited.find({{prev, u}, v}) != prohibited.end()) continue;
            
            visited[v][u] = 1; 
            d[v][u] = d[u][prev] + 1;
            parent[v][u] = {u, prev};
            if(v == n) return {v, u};
            q.push({v, u});
        }
    }

    return {0, 0};
}

void solver(){
    int n, m, k; cin>>n>>m>>k;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    for(int i = 0; i < k; i++){
        int a, b, c; cin>>a>>b>>c;
        prohibited.insert({{a, b}, c});
    }

    pii ans = BFS(n);
    if(!ans.first){
        cout<<-1<<endl;
        return;
    }

    int u = ans.first, v = ans.second;
    cout<<d[u][v]<<endl;
    stack<int> order; order.push(n);
    while(u != 1){
        pii next = parent[u][v];
        u = next.first; v = next.second;
        order.push(u);
    }
    while(!order.empty()){
        cout<<order.top()<<' ';
        order.pop();
    }

    cout<<endl;
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