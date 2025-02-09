#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn = 200005;
int components;
vector<int> leader(maxn);
unordered_set<int> sets[maxn];

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sets[i].insert(i);
    }
}

void join(int u, int v, stack<pair<bool, piii>>& st){
    int leaderU = leader[u], leaderV = leader[v];
    if(leaderU != leaderV){
        if(sets[leaderV].size() > sets[leaderU].size())
            swap(leaderU, leaderV);
        
        for(int v : sets[leaderV]){
            leader[v] = leaderU;
            st.push({1, {v, {leaderV, leaderU}}});
            sets[leaderU].insert(v);
        }
        sets[leaderV].clear();
        components--;
    }
}

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
        sets[from].erase(u);
        sets[to].insert(u);
        leader[u] = to;
    }
}

void solver(){
    int n, m; cin>>n>>m;
    initDSU(n);
    stack<pair<bool, piii>> st;
    while(m--){
        string op; cin>>op;
        if(op == "persist") st.push({0, {components, {0, 0}}});
        else if(op == "rollback"){
            rollback(st);
            cout<<components<<endl;
        }
        else{
            int u, v; cin>>u>>v;
            join(u, v, st);
            cout<<components<<endl;
        }
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