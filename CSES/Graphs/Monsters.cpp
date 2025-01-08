#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1002;
const int inf = 1e7;
char maze[maxn][maxn];
bool visited[maxn][maxn];
int d1[maxn][maxn], d2[maxn][maxn];
pii parent[maxn][maxn];
vector<pii> movements(4);

void initializeMovements(){
    movements[0] = {-1, 0};
    movements[1] = {1, 0};
    movements[2] = {0, -1};
    movements[3] = {0, 1};
}

void BFS1(int n, int m){
    queue<pii> q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(maze[i][j] == 'M'){
                q.push({i, j});
                d1[i][j] = 0;
                visited[i][j] = 1;
            }
        }
    }

    while(!q.empty()){
        int x = q.front().second, y = q.front().first; q.pop();
        for(int i = 0; i < 4; i++){
            int xf = x + movements[i].second, yf = y + movements[i].first;
            if(xf < 0 || xf >= m || yf < 0 || yf >= n || maze[yf][xf] == '#' || visited[yf][xf]) continue;
            visited[yf][xf] = 1;
            d1[yf][xf] = 1 + d1[y][x];
            q.push({yf, xf});
        }
    }
}

void BFS2(int n, int m){
    int y, x;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            visited[i][j] = 0;
            parent[i][j] = {-1, -1};
            if(maze[i][j] == 'A'){
                y = i;
                x = j;
            }
        }
    }

    queue<pii> q; q.push({y, x});
    visited[y][x] = 1;
    d2[y][x] = 0;

    while(!q.empty()){
        int uy = q.front().first, ux = q.front().second; q.pop();
        for(int i = 0; i < 4; i++){
            int vy = uy + movements[i].first, vx = ux + movements[i].second;
            if(vy < 0 || vy >= n || vx < 0 || vx >= m || maze[vy][vx] == '#' || visited[vy][vx]) continue;
            visited[vy][vx] = 1;
            d2[vy][vx] = 1 + d2[uy][ux];
            parent[vy][vx] = {uy, ux};
            q.push({vy, vx});
        }
    }
}

void solver(){
    int n, m; cin>>n>>m;
    for(int i = 0; i < n; i++){
        cin>>maze[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            visited[i][j] = 0;
            d1[i][j] = inf;
            d2[i][j] = inf;
        }
    }

    BFS1(n, m);
    BFS2(n, m);

    bool cond = 0;
    pii d;
    for(int i = 0; !cond && i < n; i++){
        if(d2[i][0] < d1[i][0]){
            d = {i, 0};
            cond = 1;
        }

        else if(d2[i][m-1] < d1[i][m-1]){
            d = {i, m-1};
            cond = 1;
        }
    }

    for(int j = 0; !cond && j < m; j++){
        if(d2[0][j] < d1[0][j]){
            d = {0, j};
            cond = 1;
        }

        else if(d2[n-1][j] < d1[n-1][j]){
            d = {n-1, j};
            cond = 1;
        }
    }

    if(!cond){
        cout<<"NO"<<endl;
        return;
    }

    int dy = d.first, dx = d.second;
    cout<<"YES"<<endl;
    cout<<d2[dy][dx]<<endl;
    stack<char> ans;
    while(parent[dy][dx].first != -1){
        int py = parent[dy][dx].first, px = parent[dy][dx].second;
        if(py > dy) ans.push('U');
        else if(py < dy) ans.push('D');
        else if(px > dx) ans.push('L');
        else ans.push('R');

        dy = py; dx = px;
    }

    while(!ans.empty()){
        cout<<ans.top();
        ans.pop();
    }

    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    initializeMovements();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}