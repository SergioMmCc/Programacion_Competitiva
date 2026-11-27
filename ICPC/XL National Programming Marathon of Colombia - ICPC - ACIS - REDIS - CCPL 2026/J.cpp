#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define endl '\n'
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forn0(i,n) for(int i = (int)n-1; i >= 0; i--)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define pb push_back
#define sz(a) (int)a.size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vl;
typedef vector<pii> vii;

const int maxn = 1e5 + 1;
vb ind(maxn, 1);
vi ans(maxn);
vector<vi> graf(maxn);
void toposort(int n){
    // vb vis(n+1);
    queue<int> q;
    for0(i,n+1){
        if(ind[i]){
            ans[i] = i;
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graf[u]){
            // assert(!vis[v]);
            ans[v] = ans[u];
            q.push(v);
            // vis[v] = 1;
        }
    }
}

void solver(int n, int q){
    vi cnt(n+1);
    for0(i,n){
        int num; cin>>num;
        cnt[num]++;
    }
    for1(i,n) cnt[i] += cnt[i-1];
    for0(i,n){
        if(cnt[i] == i) continue;
        ind[i] = 0;
        graf[cnt[i]].pb(i);
    }

    toposort(n);
    while(q--){
        int idx; cin>>idx;
        cout<<ans[idx]<<endl;
    }

    for0(i,n+1){
        ind[i] = 1;
        graf[i].clear();
        ans[i] = 0;
    }
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int n, q;
    while(cin>>n>>q){
        if(!n) break;
        solver(n, q);
    }

    return 0;
}