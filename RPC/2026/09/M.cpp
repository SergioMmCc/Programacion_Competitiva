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
typedef pair<pii, pii> piiii;
typedef pair<piiii, int> piiiii;
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

vi dy = {1, -1, 0, 0};
vi dx = {0, 0, 1, -1};

int dis[30][30][30][30][5];
void llenar(){
    for0(i,30){
        for0(j,30){
            for0(k,30){
                for0(l,30){
                    for0(m,5){
                        dis[i][j][k][l][m] = 1000000;
                    }
                }
            }
        }
    }
}

bool lim(int y, int x, int n, int m, vs& a){
    if(y < 0 || y >= n || x < 0 || x >= m || a[y][x] == 'O') return 0;
    return 1;
}

void solver(){
    llenar();
    int n, m; cin>>n>>m;
    vs a(n);
    for0(i,n) cin>>a[i];

    pii s1, s2;
    cin>>s1.fi>>s1.se>>s2.fi>>s2.se; s1.fi--; s1.se--; s2.fi--; s2.se--;
    if(a[s1.fi][s1.se] == 'G' && a[s2.fi][s2.se] == 'G'){
        cout<<0<<endl;
        return;
    }
    dis[s1.fi][s1.se][s2.fi][s2.se][4] = 0;
    deque<piiiii> q; q.push_front({{s1, s2}, 4});
    while(!q.empty()){
        int uy1 = q.front().fi.fi.fi, ux1 = q.front().fi.fi.se, uy2 = q.front().fi.se.fi, ux2 = q.front().fi.se.se, idx = q.front().se; q.pop_front();
        // cout<<"uy1 -> "<<uy1<<" ux1 -> "<<ux1<<" uy2 -> "<<uy2<<" ux2 -> "<<ux2<<endl;
        for0(i,4){
            if(!lim(uy1 + dy[i], ux1 + dx[i], n, m, a) || !lim(uy2 + dy[i], ux2 + dx[i], n, m, a)) continue;
            // cout<<"here1 i -> "<<i<<endl;
            int vy1, vx1, vy2, vx2;
            if(uy1 + dy[i] == uy2 && ux1 + dx[i] == ux2){
                if(a[uy2 + dy[i]][ux2 + dx[i]] == '#') continue;
                vy1 = uy2, vx1 = ux2, vy2 = uy2 + dy[i], vx2 = ux2 + dx[i];
            }
            else if(uy1 == uy2 + dy[i] && ux1 == ux2 + dx[i]){
                if(a[uy1 + dy[i]][ux1 + dx[i]] == '#') continue;
                vy1 = uy1 + dy[i], vx1 = ux1 + dx[i], vy2 = uy1, vx2 = ux1;
            }
            else{
                // cout<<"here i -> "<<i<<endl;
                vy1 = uy1, vx1 = ux1;
                if(a[uy1 + dy[i]][ux1 + dx[i]] != '#'){
                    vy1 += dy[i], vx1 += dx[i];
                }
                vy2 = uy2, vx2 = ux2;
                if(a[uy2 + dy[i]][ux2 + dx[i]] != '#') vy2 += dy[i], vx2 += dx[i];
            }

            // cout<<"here"<<endl;
            // cout<<"vy1 -> "<<vy1<<" vx1 -> "<<vx1<<" vy2 -> "<<vy2<<" vx2 -> "<<vx2<<endl;
            int add = idx == i ? 0 : 1;

            // cout<<"here"<<endl;
            if(dis[vy1][vx1][vy2][vx2][i] > dis[uy1][ux1][uy2][ux2][idx] + add){
                dis[vy1][vx1][vy2][vx2][i] = dis[uy1][ux1][uy2][ux2][idx] + add;
                if(!add) q.push_front({{{vy1, vx1}, {vy2, vx2}}, i});
                else q.push_back({{{vy1, vx1}, {vy2, vx2}}, i});
            }
        }
    }

    int ans = 1000000;
    for0(i,n){
        for0(j,m){
            if(a[i][j] != 'G') continue;
            for0(k,n){
                for0(l,m){
                    if(a[k][l] != 'G') continue;
                    for0(idx,4){
                        ans = min(ans, dis[i][j][k][l][idx]);
                    }
                }
            }
        }
    }

    if(ans != 1000000) cout<<ans<<endl;
    else cout<<-1<<endl;
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
