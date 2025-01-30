#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 4002, inf = 2e7;
char maze[maxn][maxn];
int d[maxn][maxn];
vector<pii> movements(4);

void initializeMovements(){
    movements[0] = {0, -1};
    movements[1] = {0, 1};
    movements[2] = {-1, 0};
    movements[3] = {1, 0};
}

void BFS(int n, int m){
    deque<pii> q; q.push_front({n-1, m-1});
    d[n-1][m-1] = 1;

    while(!q.empty()){
        int ux = q.front().second, uy = q.front().first;
        q.pop_front();
        for(int i = 0; i < 4; i++){
            int vx = ux + movements[i].second, vy = uy + movements[i].first;
            if(vx < 0 || vx >= m || vy < 0 || vy >= n || maze[vy][vx] == '.') continue;
            int add = 0;
            if(maze[uy][ux] != maze[vy][vx]) add++;
            if(d[vy][vx] > d[uy][ux] + add){
                d[vy][vx] = d[uy][ux] + add;
                if(!add) q.push_front({vy, vx});
                else q.push_back({vy, vx});
            }
        }
    }
}

void solver(){
    initializeMovements();
    int n, m; cin>>n>>m;
    for(int i = 0; i < n; i++) cin>>maze[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            d[i][j] = inf;
        }
    }

    BFS(n, m);
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(maze[i][j] == '.') continue;
            ans = max(ans, d[i][j]);
        }
    }

    cout<<ans<<endl;
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