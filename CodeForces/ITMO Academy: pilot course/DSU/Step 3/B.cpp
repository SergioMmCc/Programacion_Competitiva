#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn = 50005;
int components;
vector<int> leader(maxn);
unordered_set<int> sets[maxn];

int block_size;

struct Query {
    int l, r, id;
    bool operator<(Query other) const
    {
        return r < other.r;
    }
};

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sets[i].clear();
        sets[i].insert(i);
    }
}

void join(int u, int v, stack<pair<bool, piii>>& st, bool tipo){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        if(sets[leaderV].size() > sets[leaderU].size())
            swap(leaderU, leaderV);
        
        for(int v : sets[leaderV]){
            leader[v] = leaderU;
            if(tipo) st.push({1, {v, {leaderV, leaderU}}});
            sets[leaderU].insert(v);
        }
        sets[leaderV].clear();
        components--;
    }
}

// EL rollback sirve para devolver el DSU a un estado previo
void rollback(stack<pair<bool, piii>>& st){
    while(!st.empty()){
        bool op = st.top().first;
        int u = st.top().second.first;
        int to = st.top().second.second.first, from = st.top().second.second.second;
        st.pop();
        if(!op){
            components = u;
            break;
        }
        // Devolvemos cada vertice a su anterior componente
        sets[from].erase(u);
        sets[to].insert(u);
        leader[u] = to;
    }
}

void persist(stack<pair<bool, piii>>& st){
    st.push({0, {components, {0, 0}}});
}

void solver(){
    stack<pair<bool, piii>> st;
    int n, m; cin>>n>>m;
    block_size = sqrt(m) + 1;
    vector<pii> edges(m+1);
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        edges[i+1] = {u, v};
    }

    vector<vector<Query>> blocks(block_size);
    int q; cin>>q;
    for(int i = 0; i < q; i++){
        int l, r; cin>>l>>r;
        blocks[l / block_size].pb({l, r, i});
    }

    vector<int> ans(q);
    for(int i = 0; i < block_size; i++){
        if(blocks[i].empty()) continue;
        int len = blocks[i].sz;
        sort(blocks[i].begin(), blocks[i].end());
        int j = 0;
        initDSU(n);

        // Esta parte al parecer ya esta bien
        // Inicialmente vamos a evaluar individualmente las queries en 
        // las que tanto l como r estan dentro del rango
        int maxRange = (i+1)*block_size;
        while(j < len && blocks[i][j].r < maxRange){
            int l = blocks[i][j].l, r = blocks[i][j].r, id = blocks[i][j].id;
            persist(st);
            for(int edge = l; edge <= r; edge++){
                join(edges[edge].first, edges[edge].second, st, 1);
            }
            
            ans[id] = components;
            rollback(st);
            j++;
        }

        int lastR = maxRange - 1;
        for(; j < len; j++){
            while(lastR < blocks[i][j].r){
                lastR++;
                join(edges[lastR].first, edges[lastR].second, st, 0);
            }
            
            persist(st);
            for(int l = maxRange - 1; l >= blocks[i][j].l; l--)
                join(edges[l].first, edges[l].second, st, 1);

            ans[blocks[i][j].id] = components;
            rollback(st);
        }
    }

    for(int i = 0; i < q; i++) cout<<ans[i]<<endl;
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