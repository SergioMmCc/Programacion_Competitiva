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
    int n; cin>>n; n *= 2;
    multiset<int> a;
    for(int i = 0; i < n; i++){
        int save; cin>>save;
        a.insert(save);
    }
    // cout<<"a"<<endl;
    multiset<int>::iterator endp = a.end(); --endp;
    for(multiset<int>::iterator it = a.begin(); it != endp; ++it){
        multiset<int> test = a;
        queue<pii> ans;
        
        multiset<int>::iterator big = test.find(*endp);
        int last = *big;
        test.erase(big); // Eliminar big antes de asignar disc por si *it == *endp
        multiset<int>::iterator disc = test.find(*it);
        ans.push({last, *disc});
        test.erase(disc);

        bool cond = 1;
        while(cond && !test.empty()){
            big = test.end(); --big;
            int aux = *big;
            test.erase(big); // Eliminar big antes de asignar comp por si *big == *comp
            multiset<int>::iterator comp = test.find(last - aux);
            if(comp == test.end()) cond = 0;
            else{
                ans.push({aux, last - aux});
                last = aux;
                test.erase(comp);
            }
        }

        if(cond){
            cout<<"YES"<<endl<<ans.front().fi + ans.front().se<<endl;
            while(!ans.empty()){
                cout<<ans.front().fi<<' '<<ans.front().se<<endl;
                ans.pop();
            }

            return;
        }
    }

    cout<<"NO"<<endl;
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