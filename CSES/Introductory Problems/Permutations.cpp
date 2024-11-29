#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    int n; cin>>n;
    if(n == 1){
        cout<<1<<endl;
        return;
    }
    if(n <= 3){
        cout<<"NO SOLUTION"<<endl;
        return;
    }
    vector<int> ans;
    for(int i = 2; i <= n; i += 2)ans.pb(i);
    for(int i = 1; i <= n; i += 2)ans.pb(i);
    for(int i = 0; i < n; i++){
        if(i > 0) cout<<' ';
        cout<<ans[i];
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