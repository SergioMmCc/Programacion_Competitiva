#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2e5 + 1;
vector<vector<int>> inGraph(maxn), outGraph(maxn);
vector<int> inDegree(maxn), dp(maxn, -1), parent(maxn, -1);

void topoSort(int n, vector<int>& orden){
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!inDegree[i]){ 
            q.push(i);
            orden.pb(i);
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : inGraph[u]){
            inDegree[v]--;
            if(!inDegree[v]){ 
                q.push(v);
                orden.pb(v);
            }
        }
    }
}

void calc(int u){
    if(dp[u] != -1) return;
    dp[u] = 0;
    for(int v : outGraph[u]){
        if(!dp[v]) continue;
        if(dp[u] < dp[v] + 1){
            dp[u] = dp[v] + 1;
            parent[u] = v;
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    dp[1] = 1;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        inGraph[u].pb(v);
        outGraph[v].pb(u);
        inDegree[v]++;
    }

    vector<int> orden;
    topoSort(n, orden);
    for(int i = 1; i <= n; i++) calc(orden[i]);
    if(!dp[n]){
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }
    cout<<dp[n]<<endl;
    stack<int> ans;
    ans.push(n);
    int u = n;
    while(u != 1){
        u = parent[u];
        ans.push(u);
    }

    while(!ans.empty()){
        cout<<ans.top()<<' ';
        ans.pop();
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