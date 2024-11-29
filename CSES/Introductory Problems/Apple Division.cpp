#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

const ll inf = 1e18;

void solver(){
    int n; cin>>n;
    vector<ll> a(n+1);
    for(int i = 0; i < n; i++) cin>>a[i];
    ll ans = inf;
    int posibilities = 1 << (n - 1);
    for(int bitMask = 0; bitMask <= posibilities; bitMask++){
        int aux = bitMask;
        ll g1 = 0, g0 = 0;
        for(int i = 0; i < n; i++){
            if(aux % 2 == 1) g1 += a[i];
            else g0 += a[i];
            aux >>= 1;
        }

        ans = min(ans, abs(g0 - g1));
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