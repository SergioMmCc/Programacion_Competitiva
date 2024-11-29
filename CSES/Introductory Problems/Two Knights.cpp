#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    ll n; cin>>n;
    ll rest = 0;
    for(ll i = 1; i <= n; i++){
        if(i == 1) {cout<<0<<endl; continue;}
        rest += 8 * (i - 2);
        ll ans = (i * i * (i * i - 1)) / 2 - rest;
        cout<<ans<<endl;
    }
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