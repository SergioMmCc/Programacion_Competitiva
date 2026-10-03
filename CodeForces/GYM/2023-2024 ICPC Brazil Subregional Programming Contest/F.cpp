#include <bits/stdc++.h>
using namespace std;

using ll=long long;

void solver(){
    ll D,C,R;cin>>D>>C>>R;
    vector<ll>V;
    ll ans=0;
    for(int i=0;i<C;i++){
        int input;cin>>input;
        V.push_back(input);
    }
    for(int i=0;i<R;i++){
        int input;cin>>input;
        D+=input;
        ans++;
    }
    for(int i=0;i<C;i++){
        if(V[i]>D)break;
        D-=V[i];
        ans++;
    }
    cout<<ans<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
