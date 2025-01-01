#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int maxn = 100005;
int components;
vector<int> graph[maxn];
vector<int> leader(maxn);
vector<int> sets[maxn];

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sets[i].push_back(i);
    }
}

void join(int u, int v){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        if(sets[leaderV].size() > sets[leaderU].size())
            swap(leaderU, leaderV);
        
        for(int i = 0; i < sets[leaderV].size(); i++){
            int v = sets[leaderV][i];
            leader[v] = leaderU;
            sets[leaderU].push_back(v);
        }
        sets[leaderV].clear();
        components--;
    }
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    for(int i = 0; i < m; i++){
        int u, v;cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        join(u, v);
    }

    cout<<components - 1<<endl;

    int num = 0;
    for(int i = 1; i <= n; i++){
        if(sets[i].sz){
            if(!num) num = sets[i][0];
            else cout<<num<<' '<<sets[i][0]<<endl;
        }
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