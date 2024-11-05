#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

ll const inf = 1e18;

void solver() {
    ll x, y, z, k; cin>>x>>y>>z>>k;
    ll d = 0, ans = inf, aux = 0, sum = 0;
    while(z > 0){
        d++;
        sum += x;
        aux = ((z + d - 1) / d) * y;
        ans = min(ans, aux + sum);

        if((z + d - 1) / d == 1) break;

        if(d % k == 0) {
            z -= d;
            sum += y;
        }
    }

    cout<<ans<<endl;
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t;
    cin>>t;
    while(t--) {
        solver();
    }

    return 0;
}