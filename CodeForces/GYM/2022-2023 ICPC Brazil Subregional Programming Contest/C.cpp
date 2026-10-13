#include <bits/stdc++.h>
using namespace std;

const int S=2002;
vector<vector<int>>vis(S,vector<int>(S));
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int bfs(int sx,int sy){
    if(vis[sx][sy])return 0;
    int area=0;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    vis[sx][sy]=1;
    while(q.size()){
        auto[x,y]=q.front();q.pop();
        if(x%2 && y%2)area++;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx>=0 && nx<S && ny>=0 && ny<S && !vis[nx][ny]){
                vis[nx][ny]=1;
                q.push({nx,ny});
            }
        }
    }
    return area;
}

void solver(){
    int n,x1,y1;cin>>n>>x1>>y1;
    while(n--){
        int x2,y2;cin>>x2>>y2;
        for(int x=min(x1,x2)*2;x<=max(x1,x2)*2;x++)
            for(int y=min(y1,y2)*2;y<=max(y1,y2)*2;y++)
                vis[x][y]=1;
        x1=x2;
        y1=y2;
    }
    bfs(0,0);
    int ans=0;
    for(int x=1;x<S;x+=2)
        for(int y=1;y<S;y+=2)
            ans=max(ans,bfs(x,y));
    cout<<ans<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}