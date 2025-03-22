#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, ll> pil;

struct Edge{
    int u, v; ll w;
};

const ll inf = 1e15;

int bellmanFord(int n, vector<Edge>& edges, vector<ll>& d, vector<int>& parent){

    for(int i = 1; i < n; i++){
        bool cond = 0;
        for(Edge e : edges){
            int u = e.u, v = e.v; ll w = e.w;
            if(d[u] < inf && d[v] > d[u] + w){
                d[v] = d[u] + w;
                parent[v] = u;
                cond = 1;
            }
        }

        if(!cond) return 0; 
    }
    
    int ans = 0;
    for(Edge e : edges){
        int u = e.u, v = e.v; ll w = e.w;
        if(d[u] < inf && d[v] > d[u] + w){
            parent[v] = u;
            ans = v;
        }
    }

    return ans;
}

void solver(){
    int n, m; cin>>n>>m;
    vector<Edge> edges;
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin>>u>>v>>w;
        edges.pb({u, v, w});
    }

    vector<ll> d(n+1);
    vector<int> parent(n+1, -1);
    int u = bellmanFord(n, edges, d, parent);
    
    if(!u){
        cout<<"NO"<<endl;
        return;
    }

    cout<<"YES"<<endl;
    for(int i = 0; i < n; i++) u = parent[u];

    vector<int> ans; ans.pb(u); ans.pb(parent[u]);
    int aux = parent[u];
    while(aux != u){
        aux = parent[aux];
        ans.pb(aux);
    }

    reverse(ans.begin(), ans.end());
    for(int i = 0; i < ans.sz; i++){
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