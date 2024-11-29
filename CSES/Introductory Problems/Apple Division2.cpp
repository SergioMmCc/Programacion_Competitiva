#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

const ll inf = 1e18;
ll ans;

void testCombination(int index, const vector<ll>& a, ll g1, ll g0){
    if(index == a.size()){
        ans = min(ans, abs(g1 - g0));
        return;
    }
    g1 += a[index];
    testCombination(index + 1, a, g1, g0);
    g1 -= a[index];

    g0 += a[index];
    testCombination(index + 1, a, g1, g0);
    g0 -= a[index];
}

void solver(){
    ans = inf;
    int n; cin>>n;
    vector<ll> a(n+1);
    for(int i = 0; i < n; i++) cin>>a[i];
    ll g1 = 0, g0 = 0;
    testCombination(0, a, g1, g0);

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