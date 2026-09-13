#include <bits/stdc++.h>
using namespace std;

#define PB push_back
#define FOR(i,x,y) for(int i=x;i<=y;i++)
#define ALL(c) (c).begin(),(c).end()
#define GE(l,r,v) lower_bound(l,r,v)

void solver(){
    int n,q;cin>>n>>q;
    vector<string>a(n),b(n),c(n);
    FOR(i,0,n-1){
        cin>>a[i];
        b[i]=a[i];
        reverse(ALL(b[i]));
        FOR(j,0,a[i].size()-1){
            c[i].PB(a[i][j]);
            c[i].PB(a[i][a[i].size()-1-j]);
        }
    }
    sort(ALL(a));
    sort(ALL(b));
    sort(ALL(c));
    auto f=[](auto&v,string s){
        auto l=GE(v.begin(),v.end(),s);
        s+=char('z'+1);
        return GE(v.begin(),v.end(),s)-l;
    };
    while(q--){
        string o,p,s,t;cin>>o>>p>>s;
        FOR(i,0,p.size()-1)
            t.PB(p[i]),t.PB(s[s.size()-1-i]);
        reverse(ALL(s));
        int A=f(a,p),B=f(b,s),C=f(c,t);
        if(o=="AND")cout<<C;
        else if(o=="OR")cout<<A+B-C;
        else cout<<A+B-2*C;
        cout<<'\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
