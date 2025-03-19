#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, ll> pil;

const int maxn = 1e5 + 1;
vector<vector<pil>> graph(maxn);
vector<priority_queue<ll>> d(maxn);

struct comp{
    bool operator() (pil a, pil b){
        return a.second > b.second;
    }
};

// Complejidad O(m*log(n))
void dijkstra(int k){
    d[1].push(0);
    priority_queue<pil, vector<pil>, comp> pq;
    pq.push({1, 0});
    while(!pq.empty()){
        int u = pq.top().first; ll w1 = pq.top().second;
        pq.pop();

        if(d[u].top() < w1) continue;

        for(pil edge : graph[u]){
            int v = edge.first; ll w2 = edge.second;
            
            if(d[v].sz < k){
                d[v].push(w2 + w1);
                pq.push({v, w2 + w1});
            }

            else{
                if(d[v].top() > w1 + w2){
                    d[v].pop();
                    d[v].push(w1 + w2);
                    pq.push({v, w1 + w2});
                }
            }
        }
    }
}

void solver(){
    int n, m, k; cin>>n>>m>>k;
    for(int i = 0; i < m; i++){
        int u, v; ll w;
        cin>>u>>v>>w;
        graph[u].push_back({v, w});
    }
    dijkstra(k);

    vector<ll> ans;
    while(!d[n].empty()){
        ans.pb(d[n].top());
        d[n].pop();
    }

    reverse(ans.begin(), ans.end());
    for(int i = 0; i < k; i++){
        if(i) cout<<' ';
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