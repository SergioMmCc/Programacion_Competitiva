#include <bits/stdc++.h>
using namespace std;

using ll=long long;

void solver(){
    int n,k,f;cin>>n>>k>>f;
    vector<bitset<51>> bad(f);
    for(int i=0;i<f;i++){
        int c;cin>>c;
        while(c--){
            int x;cin>>x;
            bad[i][x]=1;
        }
    }
    int ans=0;
    for(int m=0;m<(1<<f);m++){
        bitset<51> combined_bad;
        int friends=0;
        for(int i=0;i<f;i++){
            if((m>>i)&1){
                combined_bad|=bad[i];
                friends++;
            }
        }
        int bad_cnt=combined_bad.count();
        if(n-bad_cnt>=k)
            ans=max(ans,friends);
    }
    cout<<ans<<"\n";
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    int t=1;//cin>>t;
    while(t--)solver();
}