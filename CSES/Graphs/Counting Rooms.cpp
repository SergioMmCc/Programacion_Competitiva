#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

const int maxn = 1002;
char maze[maxn][maxn];
bool visited[maxn][maxn];
vector<pii> movements(4);

void initializeMovements(){
    movements[0] = {-1, 0};
    movements[1] = {1, 0};
    movements[2] = {0, -1};
    movements[3] = {0, 1};
}

void BFS(int n, int m, int x, int y){
    queue<pii> q; q.push({y, x});
    while(!q.empty()){
        pii u = q.front(); q.pop();
        int uy = u.first, ux = u.second;
        for(int i = 0; i < 4; i++){
            int ufy = uy + movements[i].first, ufx = ux + movements[i].second;
            if(ufy < 0 || ufy >= n || ufx < 0 || ufx >= m || visited[ufy][ufx] || maze[ufy][ufx] == '#') continue;
            visited[ufy][ufx] = 1;
            q.push({ufy, ufx});
        }
    }
}

void solver(){
    initializeMovements();
    int n, m; cin>>n>>m;
    for(int i = 0; i < n; i++) cin>>maze[i];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            visited[i][j] = 0;
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(maze[i][j] == '.' && !visited[i][j]){
                visited[i][j] = 1;
                ans++;
                BFS(n, m, j, i);
            }
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