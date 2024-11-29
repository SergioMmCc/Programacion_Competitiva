#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    ll n; cin>>n;
    cout<<n;
    while(n != 1){
        if(n % 2 == 0)n /= 2;
        else n = 3*n + 1;
        cout<<' '<<n;
    }
    cout<<endl;
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