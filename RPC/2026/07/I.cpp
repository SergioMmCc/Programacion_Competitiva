#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
const int INF = 1e9;
vector<vector<int>>g(1e5+1);

vector<int>BFS(int s,int n) {
    deque<pii>q;
    vector<int>d(n+1,INF);
    d[s]=0;
    q.push_back({s,0});
    while(!q.empty()) {
        auto[u,dis]=q.front();
        q.pop_front();
        if (dis>d[u]) continue;
        for(int v:g[u]) {
            if(d[v]>d[u]+1) {
                d[v]=d[u]+1;
                q.push_back({v,d[v]});
            }
        }
    }
    return d;
}

void solver() {
    int n,m;cin>>n>>m;
    bool ans=false;
    vector<pii>e(m);
    for (auto&[u,v]:e) {
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>d1=BFS(1, n);
    vector<int>dn=BFS(n, n);
    int shortest=d1[n];
    for (auto[u,v] :e) {
        if (d1[u]==d1[v] &&
           (d1[u]+dn[u]==shortest||
            d1[v]+dn[v]==shortest)) {
            ans=true;
        }
    }
    cout<<(ans?"possible":"impossible")<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
