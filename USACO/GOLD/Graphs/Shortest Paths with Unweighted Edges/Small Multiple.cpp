#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1e5 + 1, inf = 1e9;
vector<vector<int>> graph(maxn);

int BFS(int n){
    vector<int> d(n, inf); d[1] = 1;
    deque<int> q; q.push_front(1);
    while(!q.empty()){
        int u = q.front(); q.pop_front();

        // u * 10
        int v = (u*10) % n;
        if(d[v] > d[u]){
            d[v] = d[u];
            q.push_front(v);
        }

        // u + 1
        v = (u+1) % n;
        if(d[v] > d[u] + 1){
            d[v] = d[u] + 1;
            q.push_back(v);
        }
    }

    return d[0];
}

void solver(){
    int n; cin>>n;
    cout<<BFS(n)<<endl;
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