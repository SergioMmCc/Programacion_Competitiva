// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353, top=1e6+7;
ll fact[top];

ll mul(ll a, ll b){
    return (a*b) % MOD;
}

ll bpow(ll x, ll p){
    if(p < 0) return 0ll;

    ll ans=1;
    while(p){
        if(p & 1){
            ans = mul(ans, x);
        }

        x = mul(x, x);
        p >>= 1;
    }
    return ans;
}

ll binomial(ll n, ll k){
    if(n < 0 || k < 0 || k > n) return 0;
    ll U = fact[n];
    ll D = mul(fact[n-k], fact[k]);
    return mul(U, bpow(D, MOD-2));
}


int main() {
    long long N, K, A;
    cin>>N>>K>>A;   

    if(N == 1){
        cout<<(K==0? A : 0)<<"\n";
        return 0;
    }

    fact[0] = 1;
    for(ll i=1; i<top; i++){
        fact[i] = mul(fact[i-1], i);
    }

    ll start = A*A; // A*A
    ll np = bpow(A-1, N-2-K); // (A-1)^(N-2-K)
    ll p = binomial(N-2, K); // [N-2, K] <- same

    ll ans = mul(start, mul(np, p));
    cout<<ans<<"\n";
}
