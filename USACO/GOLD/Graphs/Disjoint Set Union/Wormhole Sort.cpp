#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn = 100005, inf = 2e9;
int components;
set<int> graph[maxn];
vector<int> leader(maxn);
vector<int> sets[maxn];
set<pii> used;

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sets[i].push_back(i);
    }
}

void check(int u){
    for(set<int>::iterator it = graph[u].begin(); it != graph[u].end();){
        int v = *it;
        if(leader[u] == leader[v]){
            used.erase({min(u, v), max(u, v)});
            graph[v].erase(u);
            it = graph[u].erase(it);
        }
        else ++it;
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
            check(v);
        }
        sets[leaderV].clear();
        components--;
    }
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    for(int i = 1; i <= n; i++){
        int save; cin>>save;
        if(save != i){
            graph[i].insert(save);
            graph[save].insert(i);
            used.insert({min(save, i), max(save, i)});
        }
    }

    vector<piii> edges;
    for(int i = 0; i < m; i++){
        int u, v, w; cin>>u>>v>>w;
        edges.pb({w, {u, v}});
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());

    int ans = inf;
    int i = 0;
    while(!used.empty()){
        ans = edges[i].first;
        join(edges[i].second.first, edges[i].second.second);
        i++;
    }

    cout<<(ans == inf ? -1 : ans)<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    freopen("wormsort.in", "r", stdin);
	freopen("wormsort.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}