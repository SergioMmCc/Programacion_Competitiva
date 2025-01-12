#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

void floyd(int x, vector<int>& adj, vector<int>& ans){
    stack<int> st; st.push(x);
    int a = adj[x];
    int b = adj[adj[x]];
    while(a != b){
        if(ans[a]){
            while(!st.empty()){
                int u = st.top(); st.pop();
                ans[u] = ans[adj[u]] + 1;
            }
            return;
        }
        st.push(a);
        a = adj[a];
        b = adj[adj[b]];
    }

    while(!st.empty()) st.pop();

    a = x;
    while(a != b){
        st.push(a);
        a = adj[a];
        b = adj[b];
    }

    int startingCycle = a;
    int length = 0;
    do{
        length++;
        b = adj[b];
    } while(b != startingCycle);

    do{
        ans[b] = length;
        b = adj[b];
    } while(b != startingCycle);

    while(!st.empty()){
        int u = st.top(); st.pop();
        ans[u] = ans[adj[u]] + 1;
    }
}

void solver(){
    int n; cin>>n;
    vector<bool> coming(n+1);
    vector<int> adj(n+1), ans(n+1);
    for(int i = 1; i <= n; i++) cin>>adj[i];

    for(int i = 1; i <= n; i++){
        if(!ans[i]) floyd(i, adj, ans);
    }

    for(int i = 1; i <= n; i++){
        if(i > 1) cout<<' ';
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