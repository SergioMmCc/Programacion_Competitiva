#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 2e5 + 5;
vector<vector<int>> tree(maxn);

int BFS(int s, int n, vector<int>& distance){
    vector<bool> visited(n+1); visited[s] = 1;
    distance[s] = 0;
    queue<int> q; q.push(s);
    int maxD = -1, maxi = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(distance[u] > maxD){
            maxD = distance[u];
            maxi = u;
        }
        for(int v : tree[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }

    return maxi;
}

void solver(){
    int n; cin>>n;
    for(int i = 1; i < n; i++){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    vector<int> distance1(n+1), distance2(n+1);
    int u = BFS(1, n, distance1);
    int v = BFS(u, n, distance1);
    BFS(v, n, distance2);

    for(int i = 1; i <= n; i++){
        if(i > 1) cout<<' ';
        cout<<max(distance1[i], distance2[i]);
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