#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 200005;
int components;
vector<int> graph[maxn];
vector<int> leader(maxn);
multiset<int> sizes;
vector<int> sets[maxn];

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        sizes.insert(1);
        leader[i] = i;
        sets[i].push_back(i);
    }
}

void join(int u, int v){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        multiset<int>::iterator it = sizes.find(sets[leaderU].sz);
        sizes.erase(it);
        it = sizes.find(sets[leaderV].sz);
        sizes.erase(it);
        if(sets[leaderV].size() > sets[leaderU].size())
            swap(leaderU, leaderV);
        
        for(int i = 0; i < sets[leaderV].size(); i++){
            int v = sets[leaderV][i];
            leader[v] = leaderU;
            sets[leaderU].push_back(v);
        }
        sets[leaderV].clear();
        components--;

        sizes.insert(sets[leaderU].sz);
    }
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    while(m--){
        int u, v; cin>>u>>v;
        join(u, v);
        multiset<int>::iterator it = sizes.end(); --it;
        cout<<components<<' '<<*it<<endl;
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