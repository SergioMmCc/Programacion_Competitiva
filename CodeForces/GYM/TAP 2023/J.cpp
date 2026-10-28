#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forlr(i,l,r) for(int i = (int)l; i <= (int)r; i++)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define forn0(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define forrl(i,l,r) for(int i = (int)r; i >= (int)l; i--)
#define pb push_back
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pqueue priority_queue
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

const int maxn = 2e5 + 1;
vector<vi> graf(maxn), ing(maxn), oug(maxn);
vi capa(maxn), cnt(maxn), indeg(maxn), oudeg(maxn);

void BFS(int s, int n, vi& dis){
    queue<int> q; q.push(s);
    vb vis(n+1); vis[s] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : graf[u]){
            if(vis[v]) continue;
            vis[v] = 1;
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
}

void solver(){
    int n, m, k; cin>>n>>m>>k;
    for0(i,m){
        int u, v; cin>>u>>v;
        graf[u].pb(v);
        graf[v].pb(u);
    }

    vi d1(n+1), dn(n+1);
    BFS(1, n, d1); BFS(n, n, dn);

    for1(u,n){
        if(d1[u] + dn[u] == d1[n]){
            capa[u] = d1[u];
            cnt[capa[u]]++;
        }
        for(int v : graf[u]){
            if(d1[u] + 1 + dn[v] == d1[n]){
                ing[v].pb(u); oudeg[v]++;
                oug[u].pb(v); indeg[u]++;
            }
        }
    }

    int ans = 0;
    for1(i,d1[n]-1) if(cnt[i] == 1) ans++;

    cout<<ans;
    vb vis(n+1);
    for0(i,k){
        int s; cin>>s;
        if(!capa[s] || vis[s]){
            cout<<' '<<ans;
            continue;
        }
        if(ans == -1 || cnt[capa[s]] == 1){
            ans = -1;
            cout<<' '<<-1;
            continue;
        }

        vis[s] = 1;
        cnt[capa[s]]--;
        if(cnt[capa[s]] == 1) ans++;
        queue<int> q; q.push(s);
        while(!q.empty() && ans != -1){
            int u = q.front(); q.pop();
            for(int v : oug[u]){
                if(ans == -1) break;
                if(vis[v] || v == 1 || v == n) continue;
                oudeg[v]--;
                if(!oudeg[v]){
                    vis[v] = 1;
                    q.push(v);
                    cnt[capa[v]]--;
                    if(!cnt[capa[v]]) ans = -1;
                    else if(cnt[capa[v]] == 1 && ans != -1) ans++;
                }
            }
            for(int v : ing[u]){
                if(ans == -1) break;
                if(vis[v] || v == 1 || v == n) continue;
                indeg[v]--;
                if(!indeg[v]){
                    vis[v] = 1;
                    q.push(v);
                    cnt[capa[v]]--;
                    if(!cnt[capa[v]]) ans = -1;
                    else if(cnt[capa[v]] == 1 && ans != -1) ans++;
                }
            }
        }

        cout<<' '<<ans;
    }

    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}
