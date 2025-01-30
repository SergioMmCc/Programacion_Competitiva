#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2e5 + 5;
vector<vector<int>> tree(maxn);
vector<ll> leftD(maxn);
vector<ll> rightD(maxn);
vector<ll> lenTree(maxn, 1);

ll DFS(int s, vector<bool>& visited){
    for(int v : tree[s]){
        if(visited[v]) continue;
        visited[v] = 1;
        leftD[s] += DFS(v, visited);
        lenTree[s] += lenTree[v];
    }

    return leftD[s] + lenTree[s];
}

void BFS(int s, int n){
    vector<bool> visited(n+1); visited[s] = 1;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : tree[u]){
            if(visited[v]) continue;
            visited[v] = 1;
            q.push(v);
            rightD[v] = rightD[u] + n - 2*lenTree[v];
        }
    }
}

void solver(){
    int n; cin>>n;
    for(int i = 1; i < n; i++){
        int u, v; cin>>u>>v;
        tree[u].pb(v);
        tree[v].pb(u);
    }

    vector<bool> visited(n+1); visited[1] = 1;
    DFS(1, visited);
    rightD[1] = leftD[1];
    // for(int i = 1; i <= n; i++){
    //     cout<<leftD[i]<<' ';
    // }
    // cout<<endl;

    BFS(1, n);
    for(int i = 1; i <= n; i++){
        if(i > 1) cout<<' ';
        cout<<rightD[i];
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