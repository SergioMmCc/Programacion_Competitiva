// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#define ll long long
using namespace std;
long double INF=1e11;
long double DELTA=1e-10;
vector<pair<int, int>> info;
int n, k;

void show(multiset<pair<int, long double>> ms){
    while(!ms.empty()){
        cout<<"{"<<(*ms.begin()).first<<", "<<(*ms.begin()).second<<"} ";
        ms.erase(ms.begin());
    }
    cout<<"\n";
}

bool op(long double x){
    long double target = x*k;
    multiset<pair<int, long double>> ms;
    for(int i=0; i<n; i++){
        long double today = target;
        ms.insert(info[i]);
        //show(ms);

        while(!ms.empty()
            && today > 0)
        {
            auto it =  *ms.begin();
            //cout<<it.first<<" "<<it.second<<" ]\n";
            ms.erase(ms.begin());
            if(it.first <= i) continue;

            // first store how many day left the food before waste
            // second store quantity of food stored
            if(today > it.second){
                today -= it.second;
            }else{
                it.second -= today;
                today = 0;
                ms.insert(it);
            }
        }
        //cout<<i<<": "<<today<<"\n";

        if(today > 0){
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>k;
    info.resize(n);
    for(int i=0; i<n; i++){
        cin>>info[i].second>>info[i].first;
    }

    long double l=0, r=INF;
    while(r-l > DELTA){
        long double mid = (l+r)/2;

        if(op(mid)){
            l = mid;
        }else{
            r = mid - DELTA;
        }
    }

    if(l < DELTA){
        cout<<"-1\n";
        return 0;
        //can't win
    }

    cout<<fixed<<setprecision(10)<<l<<"\n";
}
