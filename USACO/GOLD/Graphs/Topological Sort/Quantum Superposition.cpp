#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1001;

int topoSort(int n, vector<int>& orden, vector<vector<int>>& graph, vector<int>& inDegree){
    int nVertex = 0;
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!inDegree[i]){
            if(i == n) nVertex = inDegree.sz;
            q.push(i);
            orden.pb(i);
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graph[u]){
            inDegree[v]--;
            if(!inDegree[v]){
                if(v == n) nVertex = inDegree.sz;
                q.push(v);
                orden.pb(v);
            }
        }
    }
   
    return nVertex;
}

void solver(){
    int n1, n2, m1, m2; cin>>n1>>n2>>m1>>m2;
    vector<vector<int>> graph1(n1 + 1), graph2(n2 + 1);
    vector<int> inDegree1(n1 + 1), inDegree2(n2 + 1);
   
    // Primer Grafo
    for(int i = 0; i < m1; i++){
        int u, v; cin>>u>>v;
        graph1[u].pb(v);
        inDegree1[v]++;
    }

    vector<int> orden1;
    int n1Vertex = topoSort(n1, orden1, graph1, inDegree1);
    vector<set<int>> dp1(n1 + 1);
    dp1[1].insert(0);
    for(int u : orden1){
        for(int v : graph1[u]){
            for(int w : dp1[u]) dp1[v].insert(w+1);
        }
    }
   
    // Segundo grafo
    for(int i = 0; i < m2; i++){
        int u, v; cin>>u>>v;
        graph2[u].pb(v);
        inDegree2[v]++;
    }
   
    vector<int> orden2;
    int n2Vertex = topoSort(n2, orden2, graph2, inDegree2);
    vector<set<int>> dp2(n2 + 1);
    dp2[1].insert(0);
    for(int u : orden2){
        for(int v : graph2[u]){
            for(int w : dp2[u]) dp2[v].insert(w+1);
        }
    }

    set<int> possibleAnswers;
    for(int a1 : dp1[n1]){
        for(int a2 : dp2[n2])
            possibleAnswers.insert(a1 + a2);
    }

    int q; cin>>q;
    while(q--){
        int querie; cin>>querie;
        if(possibleAnswers.find(querie) != possibleAnswers.end()) cout<<"Yes\n";
        else cout<<"No"<<endl;
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