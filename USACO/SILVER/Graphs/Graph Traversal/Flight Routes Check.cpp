#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 2e5 + 5;
vector<vector<int>> graph(maxn);

vector<int> d(maxn, -1), low(maxn), scc(maxn), reps(maxn, 0);
vector<bool> stacked(maxn);
stack<int> s;
int ticks = 0, current_scc = 0;

void tarjan(int u){
    d[u] = low[u] = ticks++;
    s.push(u);
    stacked[u] = true;
    const vector<int> &out = graph[u];
    for (int k=0, m=out.size(); k<m; ++k){
        const int &v = out[k];
        if (d[v] == -1){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (stacked[v])
            low[u] = min(low[u], low[v]);
    }
    if (d[u] == low[u]){
        int v;
        do{
            v = s.top();
            s.pop();
            stacked[v] = false;
            scc[v] = current_scc;
        }while (u != v);
        current_scc++;
    }
}

bool BFS(int s, int d, int n){
    vector<bool> visited(n+1); visited[s] = 1;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            q.push(v);
        }
    }

    return visited[d];
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
    }

    for(int i = 1; i <= n; i++){
        if(d[i] == -1) 
            tarjan(i);
    }

    if(current_scc == 1) cout<<"YES"<<endl;
    else{
        cout<<"NO"<<endl;
        int a = 1, b = 0;
        for(int i = 2; !b && i <= n; i++){
            if(scc[i] != scc[1]) b = i;
        }
        if(BFS(1, b, n)) swap(a, b);

        cout<<a<<' '<<b<<endl;
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