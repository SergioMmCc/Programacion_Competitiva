#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

void solver(){
    int n; cin>>n;
    string a, b; cin>>a>>b;
    int ans = 0;

    char last = a[0];
    int count = 1;
    for(int i = 1; i < n; i++){
        if(a[i] == last) count++;
        else{
            ans += count - 1;
            count = 1;
            last = a[i];
        }
    }

    ans += count - 1;

    cout<<ans<<endl;
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