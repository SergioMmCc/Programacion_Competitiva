#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 5e5 + 1;
vector<set<int>> tree(maxn);
vector<queue<pair<int, pii>>> q(maxn);

// bool BFS(int s, int n, vector<int>& a){
//     bool ans = 0;
//     while(!q[s].empty()){
//         int u = q[s].front().first;
//         int d = q[s].front().second.first, parent = q[s].front().second.second;
//         q[s].pop();
//         if(d > 1) continue;
//         for(int v : tree[u]){
//             if(a[v] == s){
//                 if(v == parent) continue;
//                 ans = 1;
//             }
            
//             q[s].push({v, {d + 1, u}});
//         }
//     }

//     return ans;
// }

void solver(){
    int n; cin>>n;
    for(int i = 1; i <= n; i++) tree[i].clear();
    vector<int> a(n+1), freq(n+1);
    for(int i = 1; i <= n; i++){
        cin>>a[i];
        // q[a[i]].push({i, {0, -1}});
        // freq[a[i]]++;
    }

    vector<bool> ans(n+1);
    for(int i = 1; i < n; i++){
        int u, v; cin>>u>>v;
        if(a[u] == a[v]) ans[a[u]] = 1;
        else{
            if(!ans[a[u]] && tree[a[u]].find(v) != tree[a[u]].end()) ans[a[u]] = 1;
            if(!ans[a[v]] && tree[a[v]].find(u) != tree[a[v]].end()) ans[a[v]] = 1;
        }
        tree[a[u]].insert(v);
        tree[a[v]].insert(u);
    }

    // for(int i = 1; i <= n; i++){
    //     if(freq[i] > 1){
    //         if(BFS(i, n, a)) ans[i] = 1;
    //     }
    //     else if(freq[i] == 1) q[i].pop();
    // }

    for(int i = 1; i <= n; i++) cout<<(ans[i] ? '1' : '0');
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}