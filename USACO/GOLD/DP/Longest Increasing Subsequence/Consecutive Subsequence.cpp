#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
#define fi first
#define se second
typedef pair<int, int> pii;

void solver(){
    int n; cin>>n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin>>a[i];
    set<pii> sets;

    for(int i = 0; i < n; i++){
        auto it = sets.upper_bound({a[i], 0});
        int num = a[i], len = 1;
        if(it != sets.begin()){
            --it;
            if((*it).fi == a[i] - 1){
                len = (*it).se + 1;
                sets.erase(it);
            }
        }

        sets.insert({num, len});
    }

    int len = 0, num = -1;
    for(auto it = sets.begin(); it != sets.end(); ++it){
        if((*it).se > len){
            len = (*it).se;
            num = (*it).fi;
        }
    }

    cout<<len<<endl;

    stack<int> ans;
    for(int i = n-1; i >= 0; i--){
        if(a[i] == num){
            ans.push(i+1);
            num--;
        }
    }

    while(!ans.empty()){
        cout<<ans.top()<<' ';
        ans.pop();
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