#include <bits/stdc++.h>
using namespace std;

void solver(){
    set<char>mp={'a','e','i','o','u'};
    string str;cin>>str;
    int ans=0,y_cnt=0;
    for(char&c:str){
        if(auto it=mp.find(c);it!=mp.end())ans++;
        if(c=='y')y_cnt++;
    }
    cout<<ans<<" "<<ans+y_cnt<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t=1;//cin>>t;
    while(t--)solver();
}
