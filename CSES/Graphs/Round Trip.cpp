#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1e5 + 2;
vector<vector<int>> graph(maxn);
bool cond = 0;

void DFS(int s, vector<bool>& visited, vector<int>& parent){
    for(int d : graph[s]){
        if(visited[d]){
            if(parent[s] == d || cond) continue;
            cond = 1;
            stack<int> cities; cities.push(d);
            int aux = s;
            while(aux != d){
                cities.push(aux);
                aux = parent[aux];
            }

            cout<<cities.sz + 1<<endl;
            cout<<d;
            while(!cities.empty()){
                cout<<' '<<cities.top();
                cities.pop();
            }
            cout<<endl;
        }

        visited[d] = 1;
        parent[d] = s;
        DFS(d, visited, parent);
    }
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    vector<int> parent(n+1);
    vector<bool> visited(n+1);

    for(int i = 1; i <= n; i++){
        if(!visited[i] && !cond){
            parent[i] = -1;
            visited[i] = 1;
            DFS(i, visited, parent);
        }
    }

    if(!cond) cout<<"IMPOSSIBLE"<<endl;
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