#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2e5 + 5;
vector<vector<int>> graph(maxn);
vector<bool> visited(maxn);
vector<int> dp(maxn), sons[maxn], father(maxn, -1);
set<pii> used;
vector<int> pot10(9);
void calcPot10(){
    pot10[0] = 1;
    for(int i = 1; i < 9; i++) pot10[i] = 10 * pot10[i-1];
}

void DFS(int u, int prev){
    visited[u] = 1;
    for(int v : graph[u]){
        if(v == prev) continue;
        if(visited[v]){
            if(used.find({v, u}) != used.end()) continue;
            dp[u]++;
            dp[v]--;
            used.insert({u, v});
            continue;
        }
        sons[u].pb(v);
        used.insert({u, v});
        father[v] = u;
        DFS(v, u);
    }
}

int calc(int u){
    for(int v : sons[u]) dp[u] += calc(v);
    return dp[u];
}

void solver(int n){
    for(int i = 0; i < n; i++){
        int u; string con; cin>>u>>con;
        int edges = 0;
        for(int j = con.sz - 2, pot = 0; j > 0; j--, pot++)
            edges += ((int) con[j] - '0') * pot10[pot];
        
        for(int j = 0; j < edges; j++){
            int v; cin>>v;
            graph[u].pb(v);
        }
    }

    vector<bool> root(n);
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            root[i] = 1;
            DFS(i, -1);
            calc(i);
        }
    }

    vector<pii> bridges;
    for(int i = 0; i < n; i++){
        if(root[i]) continue;
        if(!dp[i]) bridges.pb({min(i, father[i]), max(i, father[i])});
    }

    sort(bridges.begin(), bridges.end());
    cout<<bridges.sz<<" critical links"<<endl;
    for(int i = 0; i < bridges.sz; i++){
        cout<<bridges[i].first<<" - "<<bridges[i].second<<endl;
    }
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    calcPot10();
    int n = 1;
    while(cin>>n){
        for(int i = 0; i < n; i++){
            graph[i].clear();
            sons[i].clear();
            father[i] = -1;
            dp[i] = 0;
            visited[i] = 0;
        }
        used.clear();
        solver(n);
    }

    return 0;
}