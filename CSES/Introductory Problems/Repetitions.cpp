#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

void solver(){
    string s; cin>>s;
    int ans = 0, count = 0;
    char letter = '*';
    for(int i = 0; i < s.size(); i++){
        if(s[i] == letter) count++;
        else{
            ans = max(ans, count);
            count = 1;
            letter = s[i];
        }
    }

    ans = max(ans, count);
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