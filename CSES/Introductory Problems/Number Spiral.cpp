#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    ll y, x; cin>>y>>x;
    ll ans;
    if(y >= x){
        if(y % 2 == 0)
            ans = y * y - x + 1;
        else
            ans = (y - 1) * (y - 1) + x;
    }
    else{
        if(x % 2 == 1)
            ans = x * x - y + 1;
        else
            ans = (x - 1) * (x - 1) + y;
    }

    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}