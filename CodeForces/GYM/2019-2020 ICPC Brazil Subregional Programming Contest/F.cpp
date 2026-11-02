#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using vi=vector<int>;
#define F first
#define S second
#define PB push_back
#define all(x) x.begin(),x.end()

const int MAX_Y=100005;
int cnt[MAX_Y*4];
ll len[MAX_Y*4];

void upd(int u,int l,int r,int ql,int qr,int val){
    if(ql>=r || qr<=l)return;
    if(ql<=l && r<=qr) cnt[u]+=val;
    else{
        int m=midpoint(l,r);
        upd(2*u,l,m,ql,qr,val);
        upd(2*u+1,m,r,ql,qr,val);
    }
    if(cnt[u]) len[u]=r-l;
    else len[u]=(r-l==1)?0:(len[2*u]+len[2*u+1]);
}

struct River{int x1,y1,x2,y2;};
int n;
vector<River>rivs;
ll P,bx1,by1,bx2,by2,tot;

bool check(int rad){
    vector<tuple<int,int,int,int>>ev;
    for(auto&[x1,y1,x2,y2]:rivs){
        int rx1=max(1LL*min(x1,x2)-rad,bx1);
        int rx2=min(1LL*max(x1,x2)+rad,bx2);
        int ry1=max(1LL*min(y1,y2)-rad,by1);
        int ry2=min(1LL*max(y1,y2)+rad,by2);
        if(rx1>=rx2 || ry1>=ry2) continue;
        ev.PB({rx1,1,ry1,ry2});
        ev.PB({rx2,-1,ry1,ry2});
    }
    sort(all(ev));
    ll cov=0;
    int last=0;
    for(auto[x,type,y1,y2]:ev){
        cov+=1LL*(x-last)*len[1];
        upd(1,0,MAX_Y,y1,y2,type);
        last=x;
    }
    return cov*100>=P*tot;
}

void solver(){
    cin>>n;
    rivs.resize(n);
    for(auto&[x1,y1,x2,y2]:rivs)
        cin>>x1>>y1>>x2>>y2;
    cin>>P>>bx1>>by1>>bx2>>by2;
    tot=(bx2-bx1)*(by2-by1);
    int l=1,r=100005,ans=r;
    while(l<=r){
        int m=midpoint(l,r);
        if(check(m)) ans=m,r=m-1;
        else l=m+1;
    }
    cout<<ans<<"\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}