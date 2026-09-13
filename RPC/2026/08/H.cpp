// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#include <iostream>
#define ll long long
using namespace std;

int main() {
    ll n, k, p;
    cin>>n>>k>>p;

    vector<ll> ans;
    for(ll i=1; i*i<=n; i++){
        if(n % i == 0){
            if(n / i <= p
            && i <= k){
                ans.push_back(i);
            }
            ll alt = n / i;
            if(i != alt 
            && n / alt <= p
            && alt <= k){
                ans.push_back(alt);
            }
        }
    }

    sort(ans.begin(), ans.end());
    cout<<ans.size()<<"\n";
    for(ll i : ans){
        cout<<i<<"\n";
    }
}
