#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 2e5 + 1;
vector<vector<int>> graph(maxn);
vector<bool> visited(maxn), onStack(maxn);
stack<int> st;
vector<int> topo_sort;
bool cond = 0;

void DFS(int u){
    st.push(u);
    onStack[u] = 1;
    for(int v : graph[u]){
        if(cond) return;
        if(visited[v]){
            if(onStack[v]){
                cond = 1;
                stack<int> ans; ans.push(v);
                while(st.top() != v){
                    ans.push(st.top());
                    st.pop();
                }
                ans.push(v);
                while(!st.empty()) st.pop();
                cout<<ans.sz<<endl;
                while(!ans.empty()){
                    cout<<ans.top()<<' ';
                    ans.pop();
                }
                cout<<endl;

                return;
            }
            continue;
        }
        visited[v] = 1;
        DFS(v);
    }

    st.pop();
    onStack[u] = 0;
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
    }

    for(int i = 1; !cond && i <= n; i++){
        if(!visited[i]){
            visited[i] = 1;
            DFS(i);
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