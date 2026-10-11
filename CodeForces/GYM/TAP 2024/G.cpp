// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin>>s;

    map<char, int> mp;
    for(char c : s){
        mp[c]++;
    }

    int ans = min(mp['A']+mp['U'] ,min(mp['T'], mp['P']));
    cout<<ans<<"\n";
    return 0;
}
