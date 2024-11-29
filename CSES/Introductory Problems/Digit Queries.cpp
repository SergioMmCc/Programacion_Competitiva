#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

vector<ll> pot10(20);
void preCalcPot10(){
    pot10[0] = 1;
    for(int i = 1; i < 20; i++) pot10[i] = 10 * pot10[i-1];
}

void solver(){
    ll k; cin>>k;
    ll cifras = 0;
    ll lastN = 0, N = 0;
    while(k > N){
        cifras++;
        lastN = N;
        N += 9 * cifras * pot10[cifras - 1];
    }
    ll number = (k - 1 - lastN) / cifras + pot10[cifras-1];
    ll cifra = (cifras - (k - lastN - 1) % cifras) - 1;
    number /= pot10[cifra];
    ll ans = number % 10;
    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    preCalcPot10();
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}