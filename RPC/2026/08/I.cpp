#include <bits/stdc++.h>
using namespace std;

using pii=pair<int,int>;

void solver() {
    string s;cin>>s;
    set<int>ans,st={9,99,999,9'999,99'999};
    auto getNumber=[&](int start,int len) {
        int x=0;
        for(int idx=start;idx<start+len; idx++) {
            x*=10;
            x+=s[idx]-'0';
        }
        return x;
    };
    for(int i=1;i<=5 && i<=s.size();i++) {
        bool eaten=false;
        int start=0,len=i;
        int cur=getNumber(start,len);
        int init=cur;
        int guess=-1;
        for(start+=len;start+len-1<s.size();start+=len) {
            if(s[start]=='0')break;
            int next=getNumber(start,len);
            if(st.find(cur)!=st.end() || (next!=cur+1 && st.find(cur+1)!=st.end())) {
                len++;
                if(start+len-1>=s.size() || len>5)break;
                next = getNumber(start, len);
            }
            if(next!=cur+1 && next!=cur+2)break;
            if(next==cur+2) {
                if(eaten)break;
                eaten=true;
                guess=cur+1;
            }
            cur=next;
        }
        if(start==s.size()) {
            if(eaten)ans.insert(guess);
            else{
                ans.insert(init-1);
                ans.insert(cur+1);
            }
        }
    }
    ans.erase(0);
    ans.erase(100'000);
    cout<<ans.size()<<'\n';
    bool first=true;
    for(auto&x:ans){
        if(!first)cout<<' ';
        cout<<x;
        first=false;
    }
    cout<<'\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;cin>>t;
    while(t--)solver();
}
