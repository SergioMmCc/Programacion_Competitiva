#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

void solver(){
    string s, ans; cin>>s; ans = "";
    map<char, int> T;
    for(int i = 0; i < s.sz; i++)
        T[s[i]]++;

    bool cond = 1;
    char mid = '*';
    for(map<char, int>::iterator it = T.begin(); it != T.end(); ++it){
        if(it->second % 2 == 1) {
            if(!cond){
                cout<<"NO SOLUTION"<<endl;
                return;
            }
            cond = 0;
            mid = it->first;
        }
    }

    stack<char> st;
    for(map<char, int>::iterator it = T.begin(); it != T.end(); ++it){
        int rep = it->second;
        char add = it->first;
        for(int i = 1; i <= rep / 2; i++){
            ans += add;
            st.push(add);
        }
    }

    if(mid != '*') ans += mid;

    while(!st.empty()){
        char add = st.top(); st.pop();
        ans += add;
    }

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