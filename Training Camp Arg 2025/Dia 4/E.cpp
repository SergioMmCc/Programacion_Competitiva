#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

const int maxn = 5000;
vector<vector<int>> graph(maxn);

set<pii> check(int k, int n, int m, vector<pii>& grado){
    set<pii> edges;
    for(int i = 0; i < n; i++){
        int u = grado[i].se;
        int count = 0;
        for(int v : graph[u]){
            if(count >= k) break;
            if(edges.find({v, u}) == edges.end()){
                edges.insert({u, v});
                count++;
            }
        }
    }

    if(edges.sz < m) edges.clear();
    return edges;
}

void solver(){
    int n, m; cin>>n>>m;
    if(!m){
        cout<<0<<endl;
        return;
    }

    vector<set<int>> aux(n);
    vector<pii> grado(n);
    for(int i = 0; i < n; i++) grado[i] = {0, i};
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v; u--; v--;
        aux[u].insert(v);
        aux[v].insert(u);
        grado[u].fi++;
        grado[v].fi++;
    }

    sort(grado.begin(), grado.end());
    reverse(grado.begin(), grado.end());
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int v = grado[j].se;
            if(aux[i].find(v) != aux[i].end()){
                graph[i].pb(v);
            }
        }
    }

    int l = 1, r = m, ans = m;
    set<pii> edges;
    while(l <= r){
        int k = (l + r) / 2;
        set aux = check(k, n, m, grado);
        if(!aux.empty()){
            edges = aux;
            ans = k;
            r = k - 1;
        }
        else l = k + 1;
    }

    cout<<ans<<endl;
    for(pii e : edges){
        cout<<e.fi + 1<<' '<<e.se + 1<<endl;
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