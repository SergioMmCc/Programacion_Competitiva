#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 200001;
vector<int> tree[maxn];

int DFS(int s, vector<int>& ans, vector<bool>& visited){
    for(int u : tree[s]){
        if(!visited[u]){
            visited[u] = 1;
            ans[s]++;
            ans[s] += DFS(u, ans, visited);
        }
    }

    return ans[s];
}

void solver(){
    int n; cin>>n;
    for(int i = 2; i <= n; i++){
        int save; cin>>save;
        tree[i].pb(save);
        tree[save].pb(i);
    }

    vector<int> ans(n+1);
    vector<bool> visited(n+1); visited[1] = 1;
    DFS(1, ans, visited);

    for(int i = 1; i <= n; i++){
        if(i > 1) cout<<' ';
        cout<<ans[i];
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