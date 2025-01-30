#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1e5 + 5;
vector<vector<int>> graph(maxn);

bool BFS(int s, int n, vector<int>& parent, vector<int>& distance){
    vector<bool> visited(n+1); visited[s] = 1;
    parent[s] = -1;
    distance[s] = 0;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : graph[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            parent[v] = u;
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }

    return visited[n];
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    vector<int> parent(n+1), distance(n+1);
    bool cond = BFS(1, n, parent, distance);
    if(!cond){
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }

    cout<<distance[n] + 1<<endl;
    stack<int> ans;
    int u = n;
    while(u != -1){
        ans.push(u);
        u = parent[u];
    }

    while(!ans.empty()){
        int v = ans.top(); ans.pop();
        cout<<v<<' ';
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