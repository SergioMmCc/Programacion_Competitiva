#include <bits/stdc++.h>
using namespace std;

using ll=long long;

ll calc(vector<ll>v,ll avg) {
    int n=v.size();
    ll ans=0,cur=0;
    for(int step=0;step<2*n;step++){
        int i=step%n;
        cur+=v[i]-avg;
        v[i]=avg;
        if(cur<0){
            v[i]+=cur;
            cur=0;
        }
        ans+=cur;
    }
    return ans;
}

void solver(){
    int n;cin>>n;
    vector<ll>v(n);
    ll avg=0;
    for(auto&i:v){
        cin>>i;
        avg+=i;
    }
    avg/=n;
    ll ans=calc(v,avg);
    reverse(v.begin(),v.end());
    ans=min(ans,calc(v,avg));
    cout<<ans<<"\n";
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t=1;//cin>>t;
	while(t--)solver();
}