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
vector<int> adm[maxn], sets[maxn];
queue<int> q;

void initDSU(int n){
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sets[i].pb(i);
    }
}

void join(int u, int v){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        if(sets[leaderU] < sets[leaderV])
            swap(leaderU, leaderV);
        for(int admirador : adm[leaderV]) adm[leaderU].pb(admirador);
        for(int v : sets[leaderV]){
            sets[leaderU].pb(v);
            leader[v] = leaderU;
        }

        sets[leaderV].clear();
        adm[leaderV].clear();
        if(adm[leaderU].sz > 1) q.push(leaderU);
    }
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        adm[u].pb(v);
    }

    for(int i = 1; i <= n; i++){
        if(adm[i].sz > 1) q.push(i);
    }

    while(!q.empty()){
        int x = q.front();
        if(adm[x].sz <= 1){
            q.pop();
            continue;
        }
        int u = adm[x][0];
        int v = adm[x][adm[x].sz - 1];
        adm[x].pop_back();

        join(u, v);
    }

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