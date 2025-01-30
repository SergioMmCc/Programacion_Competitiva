#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<ll, pii> plii;
typedef pair<ll, int> pli;

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
    int n, q; cin>>n>>q;
    initDSU(n);
    vector<plii> edges;
    for(int i = 1; i < n; i++){
        int u, v; ll w; cin>>u>>v>>w;
        edges.pb({w, {u, v}});
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());

    vector<plii> queries;
    for(int i = 0; i < q; i++){
        ll k; int u; cin>>k>>u;
        queries.pb({k, {u, i}});
    }
    sort(queries.begin(), queries.end());
    reverse(queries.begin(), queries.end());

    int i = 0;
    vector<int> ans(q);
    for(plii querie : queries){
        while(i < edges.sz && edges[i].first >= querie.first){
            join(edges[i].second.first, edges[i].second.second);
            i++;
        }

        ans[querie.second.second] = sets[leader[querie.second.first]].sz - 1;
    }

    for(int j = 0; j < q; j++) cout<<ans[j]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    freopen("mootube.in", "r", stdin);
	freopen("mootube.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}