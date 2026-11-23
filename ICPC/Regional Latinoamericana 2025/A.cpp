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

void solver(){
    int n; cin>>n;
    vector<vb> graf(n+1, vb(n+1, 1));
    
    int p; cin>>p;
    int last = 0;
    bool cond = 1;
    for0(i,p){
        int num; cin>>num;
        if(last){
            if(!graf[num][last] || num == last) cond = 0;
            graf[num][last] = graf[last][num] = 0;
        }
        last = num;
    }

    int a = last, fst = 0;
    last = 0;
    int q; cin>>q;
    for0(i,q){
        int num; cin>>num;
        if(last){
            if(!graf[num][last] || num == last) cond = 0;
            graf[num][last] = graf[last][num] = 0;
        }
        else fst = num;
        last = num;
    }

    int tot = 1 + (n * (n-1)) / 2;
    if(!cond || (n > 2 && !(n & 1)) || p + q > tot){
        cout<<'N'<<endl;
        return;
    }

    // Verifica que solo halla un componente con aristas
    bool comp = 0;
    vb vis(n+1);
    for1(i,n){
        if(vis[i]) continue;
        bool go = 0;
        for1(j,n){
            if(i == j) continue;
            if(graf[i][j] && comp){
                cout<<'N'<<endl;
                return;
            }
            else if(graf[i][j]){
                go = 1;
                break;
            }
        }

        if(!go) continue;
        comp = 1;
        queue<int> q; q.push(i); vis[i] = 1;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for1(v,n){
                if(!graf[u][v] || vis[v]) continue;
                q.push(v);
                vis[v] = 1;
            }
        }
    }

    int b = fst;

    int u = 0, v = 0;
    for1(i,n){
        int cnt = 0;
        for1(j,n){
            if(i != j && graf[i][j]) cnt++;
        }

        if(cnt & 1){
            if(!u) u = i;
            else if(!v) v = i;
            else{
                cout<<'N'<<endl;
                return;
            }
        }
    }

    if(a > b) swap(a, b); // Siendo a y b los nodos donde termina cada lado
    if(u > v) swap(u, v); // Siendo u y v los nodos de grado impar en el grafo resultante

    if(a && a == b){
        if(u + v){
            cout<<'N'<<endl;
            return;
        }
    }

    if(b){
        if(a){
            if(v){
                if(a != u || b != v){
                    cout<<'N'<<endl;
                    return;
                }
            }
        }
        else{
            if(v){
                if(u != b && v != b){
                    cout<<'N'<<endl;
                    return;
                }
            }
        }
    }
    if(a && a != b && !v){
        cout<<'N'<<endl;
        return;
    }

    if(a && p != tot && q != tot){
        bool test = 0;
        for1(i,n) if(i != a && graf[a][i]) test = 1;
        if(!test){
            cout<<'N'<<endl;
            return;
        }
    }
    if(b && a != b && p != tot && q != tot){
        bool test = 0;
        for1(i,n) if(i != b && graf[b][i]) test = 1;
        if(!test){
            cout<<'N'<<endl;
            return;
        }
    }

    cout<<'Y'<<endl;
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
