#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void move(int len, int s, int d){
    if(len == 1){
        cout<<s<<' '<<d<<endl;
        return;
    }

    move(len - 1, s, s ^ d);
    cout<<s<<' '<<d<<endl;
    move(len - 1, s ^ d, d);
}

void solver(){
    int n; cin>>n;
    int ans = 1;
    for(int i = 1; i <= n; i++) ans *= 2;
    ans--;
    cout<<ans<<endl;
    move(n, 1, 3);
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