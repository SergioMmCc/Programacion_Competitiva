#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    ll n; cin>>n;
    if(n % 4 == 1 || n % 4 == 2){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
    vector<int> g1, g2;
    if(n % 2 == 0){
        for(int i = 1; i <= n; i++){
            if(i % 4 == 0 || i % 4 == 1)g1.pb(i);
            else g2.pb(i);
        }
    }
    else{
        for(int i = 1; i <= n; i++){
            if(i % 4 == 0 || i % 4 == 3)g1.pb(i);
            else g2.pb(i);
        }
    }

    cout<<g1.size()<<endl;
    for(int i = 0; i < g1.size(); i++){
        if(i != 0) cout<<' ';
        cout<<g1[i];
    }
    cout<<endl;
    cout<<g2.size()<<endl;
    for(int i = 0; i < g2.size(); i++){
        if(i != 0) cout<<' ';
        cout<<g2[i];
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