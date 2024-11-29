#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    int n; cin>>n;
    ll last = 0, ans = 0;
    for(int i = 0; i < n; i++){
        ll save; cin>>save;
        if(save < last) ans += last - save;
        else last = save;
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