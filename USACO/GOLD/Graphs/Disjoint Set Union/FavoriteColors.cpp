#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 200005;
vector<int> leader(maxn);
vector<int> adm[maxn];
set<pii> process;

void initDSU(int n){
    for(int i = 1; i <= n; i++){
        leader[i] = i;
    }
}

int find(int u){
    if(leader[u] != u)
        leader[u] = find(leader[u]);
    return leader[u];
}

void join(int a, int b){
    process.erase({adm[a].sz, a});
    if(process.find({adm[b].sz, b}) != process.end()) process.erase({adm[b].sz, b});
    for(int v : adm[b]){
        adm[a].pb(v);
    }

    if(adm[a].sz > 1) process.insert({adm[a].sz, a});
    adm[b].clear();
}

void updateAllLeaders(int n){
    for(int i = 1; i <= n; i++)
        find(i);
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        adm[u].pb(v);
    }

    for(int i = 1; i <= n; i++){
        if(adm[i].sz > 1) process.insert({adm[i].sz, i});
    }

    bool cond = 1;
    while(!process.empty()){
        set<pii>::iterator it = process.end(); --it;
        int x = (*it).second;
        process.erase(it);
        if(adm[x].sz > 1){
            int u = adm[x][0];
            int v = adm[x][adm[x].sz - 1];
            if(adm[u].sz < adm[v].sz){
                adm[x][0] = v;
                swap(u, v);
            }
            leader[v] = u;
            adm[x].pop_back();
    
            join(u, v);
            if(adm[x].sz > 1) process.insert({adm[x].sz, x});
        }
    }

    updateAllLeaders(n);
    int num = 1;
    vector<bool> visited(n+1);
    vector<int> ans(n+1);
    for(int i = 1; i <= n; i++){
        if(!visited[leader[i]]){
            visited[leader[i]] = 1;
            ans[leader[i]] = num;
            num++;
        }

        ans[i] = ans[leader[i]];
    }

    for(int i = 1; i <= n; i++) cout<<ans[i]<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    freopen("fcolor.in", "r", stdin);
	freopen("fcolor.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}