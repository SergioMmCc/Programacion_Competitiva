#include <bits/stdc++.h>
using namespace std;

void solver(){
    set<string>pick,drop;
    bool ans=true;
    int n;cin>>n;
    for(int i=0;i<n;i++){
        string s,a;cin>>s>>a;
        if(s=="pickup")
            pick.insert(a);
        else{
            if(auto it=pick.find(a);it!=pick.end())
                drop.insert(a);
            else
                ans=false;
        }
    }
    if(pick.size()!=drop.size())
        ans=false;
    if(pick.size()+drop.size()<n)
        ans=false;
    cout<<(ans? "yes":"no")<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    int t=1;//cin>>t;
    while(t--)solver();
}
