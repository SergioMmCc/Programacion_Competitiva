#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

typedef pair<ld, ld> pdd;
const int maxn = 210;

bool try_kuhn(int v, vector<bool>& used, vector<int>& mt, vector<int> graph[]){
    if(used[v])
        return 0;
    used[v] = 1;
    for(int to : graph[v]) {
        if(mt[to] == -1 || try_kuhn(mt[to], used, mt, graph)) {
            mt[to] = v;
            return 1;
        }
    }
    return 0;
}

void solver(int n, int m, ld s, ld v){
    vector<int> graph[n+m+1];
    vector<int> mt;
    vector<bool> used;
    vector<pdd> points(n + m + 1);

    for(int i = 1; i <= n; i++) cin>>points[i].first>>points[i].second;
    for(int i = 1; i <= m; i++) cin>>points[i+n].first>>points[i+n].second;

    for(int i = 1; i <= n; i++){
        for(int j = n + 1; j <= n + m; j++){
            ld distance = ((points[i].first - points[j].first) * (points[i].first - points[j].first) + 
                           (points[i].second - points[j].second) * (points[i].second - points[j].second));
            distance = sqrt(distance);
            ld calcTime = distance / v;
            if(calcTime <= s){
                graph[i].pb(j);
                graph[j].pb(i);
            }
        }
    }

    mt.assign(n+m+1, -1);
    vector<bool> used1(n+m+1, 0);
    for(int v = 1; v <= n+m; v++){
        for(int to : graph[v]){
            if(mt[to] == -1){
                mt[to] = v;
                used1[v] = 1;
                break;
            }
        }
    }
    for(int v = 1; v <= n+m; v++){
        if(used1[v]) continue;
        used.assign(n + m + 1, 0);
        try_kuhn(v, used, mt, graph);
    }

    int ans = 0;
    for(int i = 1; i <= n + m; ++i)
        if(mt[i] == -1) ans++;
    
    ans /= 2;
    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    int n, m; ld s, v;
    // cin>>t;
    while(cin>>n>>m>>s>>v){
        solver(n, m, s, v);
    }

    return 0;
}