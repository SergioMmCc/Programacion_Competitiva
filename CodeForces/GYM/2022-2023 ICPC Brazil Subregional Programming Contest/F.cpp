#include <bits/stdc++.h>
using namespace std;
 
using ll=long long;

void solver() {
    int n,c;cin>>n>>c;
    map<string,int>freq;
    for (int i=0;i<n;++i) {
        string s;cin>>s;
        int star_pos=s.find('*');
        for (char c='a';c<='z';++c) {
            s[star_pos]=c;
            freq[s]++;
        }
    }
    string ans="";
    int maxcount=-1;
    for(const auto&[word,count]:freq) {
        if(count>maxcount) {
            maxcount=count;
            ans=word;
        }
    }
    cout<<ans<<" "<<maxcount<<"\n";
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}