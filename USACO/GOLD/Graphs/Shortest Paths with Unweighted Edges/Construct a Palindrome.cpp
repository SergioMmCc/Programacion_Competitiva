#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1001, inf = 1e9;
int dis[maxn][maxn];
bool visited[maxn][maxn];
set<pii> graph[maxn][maxn], edges;

int BFS(int s, int d){
    int ans = inf;

    dis[s][d] = 0;
    visited[s][d] = 1;
    queue<pii> q; q.push({s, d});
    while(!q.empty()){
        int u = q.front().first, v = q.front().second; q.pop();
        if(u == v){
            ans = min(ans, dis[u][v]);
            continue;
        }
        else if(edges.find({u, v}) != edges.end()){
            ans = min(ans, dis[u][v] + 1);
            continue;
        }
        for(pii to : graph[u][v]){
            int x = to.first, y = to.second;
            if(visited[x][y]) continue;
            visited[x][y] = 1;
            q.push({x, y});
            dis[x][y] = dis[u][v] + 2;
        }
    }

    return ans;
}

void solver(){
    int n, m; cin>>n>>m;
    map<char, vector<pii>> construct;

    for(int i = 0; i < m; i++){
        int u, v; char c; cin>>u>>v>>c;
        if(u > v) swap(u, v);
        for(pii to : construct[c]){
            int s1 = min(u, to.first), s2 = min(u, to.second);
            int d1 = min(v, to.first), d2 = max(v, to.second);
            graph[min(u, to.first)][max(u, to.first)].insert({min(v, to.second), max(v, to.second)});
            graph[min(v, to.second)][max(v, to.second)].insert({min(u, to.first), max(u, to.first)});
            graph[min(u, to.second)][max(u, to.second)].insert({min(v, to.first), max(v, to.first)});
            graph[min(v, to.first)][max(v, to.first)].insert({min(u, to.second), max(u, to.second)});
        }
        edges.insert({u, v});
        construct[c].pb({u, v});
    }

    int ans = BFS(1, n);
    cout<<(ans == inf ? -1 : ans)<<endl;
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