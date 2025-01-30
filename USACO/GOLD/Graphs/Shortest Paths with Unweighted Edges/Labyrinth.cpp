#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1002;
const int inf = 1e6 + 2;
char maze[maxn][maxn];
bool visited[maxn][maxn];
pii parent[maxn][maxn];
int d[maxn][maxn];
vector<pii> movements(4);

void initializeMovements(){
    movements[0] = {-1, 0};
    movements[1] = {1, 0};
    movements[2] = {0, -1};
    movements[3] = {0, 1};
}

void BFS(int n, int m, int x, int y){
    d[y][x] = 0;
    visited[y][x] = 1;
    queue<pii> q; q.push({y, x});
    while(!q.empty()){
        pii u = q.front(); q.pop();
        int uy = u.first, ux = u.second;
        for(int i = 0; i < 4; i++){
            int ufy = uy + movements[i].first, ufx = ux + movements[i].second;
            if(ufy < 0 || ufy >= n || ufx < 0 || ufx >= m || visited[ufy][ufx] || maze[ufy][ufx] == '#') continue;
            visited[ufy][ufx] = 1;
            parent[ufy][ufx] = {uy, ux};
            d[ufy][ufx] = 1 + d[uy][ux];
            q.push({ufy, ufx});
        }
    }
}

void solver(){
    initializeMovements();
    int n, m; cin>>n>>m;
    pii a, b;
    for(int i = 0; i < n; i++){
        cin>>maze[i];
        for(int j = 0; j < m; j++){
            if(maze[i][j] == 'A') a = {i, j};
            else if(maze[i][j] == 'B') b = {i, j};
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            visited[i][j] = 0;
            parent[i][j] = {-1, -1};
            d[i][j] = inf;
        }
    }

    BFS(n, m, a.second, a.first);
    if(d[b.first][b.second] == inf){
        cout<<"NO"<<endl;
        return;
    }

    cout<<"YES"<<endl;
    cout<<d[b.first][b.second]<<endl;

    stack<char> ans;
    pii coord = b;
    while(coord.first != a.first || coord.second != a.second){
        pii aux = parent[coord.first][coord.second];
        if(aux.first > coord.first) ans.push('U');
        else if(aux.first < coord.first) ans.push('D');
        else if(aux.second > coord.second) ans.push('L');
        else ans.push('R');
        coord = aux;
    }

    while(!ans.empty()){
        char next = ans.top();
        ans.pop();
        cout<<next;
    }

    cout<<endl;
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