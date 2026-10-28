#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
#define F first
#define S second
#define PB push_back
#define all(x) x.begin(),x.end()

const int N=100'005;
int n;
ll h[N],l[N],r[N];
vector<pli>adj[N];

void add_edge(int u,int v){
    ll w=abs(h[u]-h[v]);
    adj[u].PB({w,v});
    adj[v].PB({w,u});
}

void sweep(int dir){
    vector<tuple<ll,int,int>> ev;
    for(int i=1;i<=n;i++){
        ev.PB({l[i]+dir*h[i],0,i});
        ev.PB({r[i]+dir*h[i],1,i});
    }
    sort(all(ev));
    set<pli>active={{0,0}};
    for(auto[x,type,id]:ev){
        pli cur={h[id],id};
        if(type==0){
            auto it=active.insert(cur).F;
            add_edge(id,prev(it)->S);
            if(next(it)!=active.end())add_edge(id,next(it)->S);
        }else{
            active.erase(cur);
        }
    }
}

void solver(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>h[i]>>l[i]>>r[i];
    sweep(-1);
    sweep(1);
    priority_queue<pli,vector<pli>,greater<pli>> pq;
    vector<bool>vis(n+1,false);
    pq.push({0,0});
    ll ans=0;
    while(!pq.empty()){
        auto [w,u]=pq.top();pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        ans+=w;
        for(auto [nw,v]:adj[u]){
            if(!vis[v])pq.push({nw,v});
        }
    }
    cout<<ans<<"\n";
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}