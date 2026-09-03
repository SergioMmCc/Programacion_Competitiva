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

int go[101][101];

void solver(){
    int n, m; cin>>n>>m;
    vector<vi> act(m+1);
    for1(i,n){
        int cnt; cin>>cnt;
        for0(j,cnt){
            int a; cin>>a;
            act[a].pb(i);
        }
    }

    for1(i,m){
        for0(j, sz(act[i])-1){
            forlr(k,j+1,sz(act[i])-1){
                go[act[i][j]][act[i][k]] = go[act[i][k]][act[i][j]] = i;
            }
        }
    }

    int qu; cin>>qu;
    while(qu--){
        int a, b; cin>>a>>b;
        queue<int> q;
        vb vis(n+1); vi pa(n+1);
        for(int x : act[a]){
            q.push(x);
            vis[x] = 1;
        }
        vb des(n+1);
        bool cond = 0;
        for(int x : act[b]){
            if(vis[x]){
                cout<<2<<endl<<a<<' '<<x<<' '<<b<<endl;
                cond = 1;
                break;
            }
            des[x] = 1;
        }
        if(cond) continue;

        bool read = 0;
        while(!read && !q.empty()){
            int u = q.front(); q.pop();
            for1(v,n){
                if(!go[u][v] || vis[v]) continue;
                pa[v] = u;

                if(des[v]){
                    // cout<<"here"<<endl;
                    read = 1;
                    stack<int> ans;
                    ans.push(b);
                    
                    while(pa[v]){
                        // cout<<"v -> "<<v<<" pa -> "<<pa[v]<<endl;
                        ans.push(v);
                        ans.push(go[v][pa[v]]);
                        v = pa[v];
                    }
                    ans.push(v);
                    ans.push(a);

                    cout<<(sz(ans) + 1) / 2<<endl;
                    while(!ans.empty()){
                        cout<<ans.top()<<' ';
                        ans.pop();
                    }cout<<endl;
                    break;
                }
            
                vis[v] = 1;
                q.push(v);
            }
        }

        if(!read) cout<<-1<<endl;
    }
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
