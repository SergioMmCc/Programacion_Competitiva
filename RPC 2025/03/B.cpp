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
typedef pair<ld, int> pdi;

int tonum(string s){
    int ans=0, k=1000;
    bool b=0;
    for(char i : s){
        if(i == '.'){
            b = 1;
            continue;
        }
        ans *= 10;
        ans += i-'0';
        if(b) k /= 10;
    }
    return ans*k;
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    // x * 1000;
    int n; string s;
    cin>>n>>s;
    int p = tonum(s);
    vector<pdi> vec(n+1);
    int num;
    ld ans = 0.0;
    for(int i=0; i<n; i++){
        cin>>num>>s;
        int aux = tonum(s);
        if(aux == p){
            ans += (ld)num;
            num = 0;
        }
        vec[i] = {(ld)num, aux};
    }

    // for(int i=0; i<n; i++){
    //     cout<<vec[i].first<<", "<<vec[i].second<<"\n";
    // }

    vector<pair<ld, pii>> comp;
    for(int i = 0; i < n - 1; i++){
        if(vec[i].se == p) continue;
        for(int j = i + 1; j <= n; j++){
            if(vec[j].se == p) continue;
            if((vec[i].se > p && vec[j].se > p) || (vec[i].se < p && vec[j].se < p)) continue;
            int mayor = abs(p - vec[i].se), menor = abs(p - vec[j].se);

            int auxI = i, auxJ = j;
            if(menor > mayor){
                swap(auxI, auxJ);
                swap(mayor, menor);
            }
            ld r = (ld)menor / (ld)mayor;
            if(r == 0.0) continue;
            comp.pb({r, {auxI, auxJ}});
        }
    }

    sort(comp.begin(), comp.end());
    reverse(comp.begin(), comp.end());

    // cout<<ans<<endl;
    for(int k = 0; k < comp.sz; k++){
        ld r = comp[k].fi; int i = comp[k].se.fi, j = comp[k].se.se;
        ld avMayor = vec[i].fi, avMenor = vec[j].fi;

        ld ir = 1.0 / r;


        // cout<<"k -> "<<k<<" i -> "<<i<<" avMayor -> "<<avMayor<<" j -> "<<j<<" avMenor -> "<<avMenor<<" r -> "<<r<<" ir -> "<<ir<<" ans -> "<<ans<<endl;

        if(avMayor > r * avMenor){
            // cout<<"here"<<endl;
            ans += r * avMenor; vec[i].fi -= r * avMenor;
            ans += avMenor; vec[j].fi = 0.0;
        }
        else{
            ans += ir * avMayor; vec[j].fi -= ir * avMayor;
            ans += avMayor; vec[i].fi = 0.0;
        }

    }

    cout<<fixed<<setprecision(5)<<ans<<endl;
}