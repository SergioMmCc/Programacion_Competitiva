#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

char swapBit(char b){
    if(b == '0') return '1';
    return '0';
}

void solver(){
    int n; cin>>n;
    int num = 1 << n;
    vector<int> changes(num + 1);
    int pot = 4;
    int exp = 1;
    while(pot <= num){
        int mod = (pot >> 1) + 1;
        while(mod <= num){
            changes[mod] = exp;
            mod += pot;
        }

        pot <<= 1;
        exp++;
    }

    string ans = "";
    for(int i = 0; i < n - 1; i++) ans += '0';
    ans += '1';

    for(int i = 1; i <= num; i++){
        int bit = n - changes[i] - 1;
        ans[bit] = swapBit(ans[bit]);

        cout<<ans<<endl;
    }

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