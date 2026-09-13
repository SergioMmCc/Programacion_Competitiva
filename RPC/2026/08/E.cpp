#include <bits/stdc++.h>
using namespace std;

using pii=pair<int,int>;

void solver(){
    int n;cin>>n;
    queue<pii>q;
    int ans=0;
    for(int i=1;i<=n;i++){
        int a,b;cin>>a>>b;
        if(!q.empty()&&(q.front().second<i||a>i-q.size()))q.pop();
        if(!q.empty()&&(q.front().second<i||a>i-q.size()))q.pop();
        q.push({a,b});
        if(q.size()==3){
            ans++;
            q.pop();
            q.pop();
            q.pop();
        }
    }
    cout<<ans<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
