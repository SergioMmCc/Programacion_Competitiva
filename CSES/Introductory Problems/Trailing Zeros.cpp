#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    ll n; cin>>n;
    ll pot5 = 5;
    ll ans = 0;
    while(pot5 <= n){
        ans += (n / pot5);
        pot5 *= 5;
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