#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    int a, b; cin>>a>>b;
    if(b > a)swap(a, b);
    if((a + b) % 3 != 0 || a > 2*b)cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        solver();
    }

    return 0;
}