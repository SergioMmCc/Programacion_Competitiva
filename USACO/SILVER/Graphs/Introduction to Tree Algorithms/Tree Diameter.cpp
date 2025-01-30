#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 2e5 + 5;
vector<vector<int>> tree(maxn);

int BFS1(int s, int n){
    vector<bool>visited(n+1); visited[s] = 1;
    queue<int> q; q.push(s);
    vector<int> distance(n+1);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }

    int ans = 0, maxDistance = -1;
    for(int i = 1; i <= n; i++){
        if(distance[i] > maxDistance){
            maxDistance = distance[i];
            ans = i;
        }
    }

    return ans;
}

int BFS2(int s, int n){
    vector<bool>visited(n+1); visited[s] = 1;
    queue<int> q; q.push(s);
    vector<int> distance(n+1);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, distance[i]);
    return ans;
}

void solver(){
    int n; cin>>n;
    for(int i = 1; i < n; i++){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    int larger = BFS1(1, n);
    cout<<BFS2(larger, n)<<endl;
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