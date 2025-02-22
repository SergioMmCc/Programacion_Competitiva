#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn = 300001;
int components;
vector<int> leader(maxn), sizen(maxn);
vector<int> ans;

struct change{
    int u, len, from;
};

struct query{
    bool op;
    int l, r, u, v;
};

void initDSU(int n){
    components = n;
    for(int i = 1; i <= n; i++){
        leader[i] = i;
        sizen[i] = 1;
    }
}

int find(int u){
    if(leader[u] == u) return u;
    return find(leader[u]);
}

void join(int u, int v, stack<change>& st){
    u = find(u); v = find(v);
    if(u != v){
        if(sizen[v] > sizen[u])
            swap(u, v);
        leader[v] = u;
        st.push({v, sizen[u], u});
        sizen[u] += sizen[v];
        components--;
    }
}

void rollback(stack<change>& st){
    while(!st.empty()){
        int u = st.top().u;
        int len = st.top().len, from = st.top().from;
        st.pop();

        if(!u) break;
        
        sizen[from] = len;
        leader[u] = u;
        components++;
    }
}

void persist(stack<change>& st){
    st.push({0, 0, 0});
}

void work(int l, int r, queue<query>& q1, stack<change>& st){
    // cout<<"l -> "<<l<<" r -> "<<r<<endl;
    if(l == r - 1){
        persist(st);
        
        queue<query> q2;
        while(!q1.empty()){
            query q = q1.front(); q1.pop();
            // cout<<q.op<<' '<<q.t<<' '<<q.l<<' '<<q.r<<' '<<q.u<<' '<<q.v<<endl;
            if(!q.op && q.l == l) q2.push(q);
            if(q.op && q.l <= l && q.r >= r) join(q.u, q.v, st);
        }
        // cout<<"components -> "<<components<<endl;
        while(!q2.empty()){
            query q = q2.front(); q2.pop();
            ans[q.l] = components;
        }
        rollback(st);
        return;
    }

    persist(st);
    queue<query> q2, q3;
    int m = (l + r) >> 1;
    while(!q1.empty()){
        query q = q1.front(); q1.pop();
        // cout<<q.op<<' '<<q.t<<' '<<q.l<<' '<<q.r<<' '<<q.u<<' '<<q.v<<endl;
        if(q.op && q.l <= l && q.r >= r) join(q.u, q.v, st);
        else{
            if ((!q.op && q.l >= l && q.l < m) ||
                (q.op && ((q.l >= l && q.l < m) || (q.r - 1 >= l && q.r <= m)))) q2.push(q);
            if ((!q.op && q.l >= m && q.l < r) ||
                (q.op && ((q.l >= m && q.l < r) || (q.r - 1 >= m && q.r <= r)))) q3.push(q);
        }
    }

    work(l, m, q2, st);
    work(m, r, q3, st);
    rollback(st);
}

void solver(){
    int n, m; cin>>n>>m; if(!m) return;
    initDSU(n);
    stack<change> st;
    map<pii, int> T;
    vector<query> queries;
    for(int i = 0; i < m; i++){
        char op; cin>>op;
        if(op == '?') queries.pb({0, i, 0, 0, 0});
        else{
            int u, v; cin>>u>>v; if(u > v) swap(u, v);
            if(op == '+'){
                T[{u, v}] = queries.sz;
                queries.pb({1, i, -1, u, v});
            }
            else queries[T[{u, v}]].r = i;
        }
    }

    queue<query> q1;
    for(int i = 0; i < queries.sz; i++){
        if(queries[i].op && queries[i].r == -1) queries[i].r = m;
        q1.push(queries[i]);
    }
    queries.clear();
    T.clear();

    ans.resize(m);
    work(0, m, q1, st);
    for(int i = 0; i < m; i++){
        if(!ans[i]) continue;
        cout<<ans[i]<<endl;
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