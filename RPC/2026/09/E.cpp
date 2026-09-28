// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int strtoint(string str){
    int v=0, x=1;
    for(int i=str.size()-1; i>=0; i--){
        v += (str[i]-'0')*x;
        x<<=1;
    }
    return v;
}


int getchar(vector<vector<int>>& vec, int f, int a, int b, int n1, int n2){
    a--; b--;
    if(f == 0){
        return vec[0][a % n1];
    }
    return vec[1][b % n2];
}

int INF=1e9;
int A=0, B=1;
int solve(vector<vector<int>>& vec, int K, int T, int n1, int n2){
    map<tuple<int, int, int>, int> space[2][2];

    space[0][A][{1, 0, K}] = 0;
    bool cnt=true;
    int debugX=4;
    int maxx=-1;
    int t=0;

    while(cnt){
        cnt = 0;
           // cout<<t<<" ========================================== \n";
                //cout<<"A----\n";
                while(!space[t][A].empty()){
                    cnt = 1;
                    auto it = (space[t][A].begin());
                    auto x = *it;
                    space[t][A].erase(it);

                    

                    auto [f1, val] = x;
                    auto [a, b, K] = f1;
                    /*
                    cout<<"{"<<a<<", "<<b<<", "<<K<<"} -> "<<val<<"     ";
                    cout<<getchar(vec, A, a, b, n1, n2)<<" ["<<getchar(vec, A, a+1, b+1, n1, n2)<<", "<<getchar(vec, !A, a+1, b+1, n1, n2)<<"]      ";
                    //cout<<a+1<<b<<K<<" -> "<<max(
                                                (space[!t][A].count({a+1, b, K}) > 0)? space[!t][A][{a+1, b, K}] : -INF, 
                                                val 
                                                + (getchar(vec, A, a+1, b+1, n1, n2) == getchar(vec, A, a, b, n1, n2))
                                                )<<" ... ";
                    cout<<a<<b+1<<K<<" -> "<<max(
                                                    (space[!t][!A].count({a, b+1, K-1}) > 0)? space[!t][!A][{a, b+1, K-1}] : -INF, 
                                                    val 
                                                    + (getchar(vec, !A, a+1, b+1, n1, n2) == getchar(vec, A, a, b, n1, n2))
                                                    )<<"\n";
                                                    */


                    if(a + b >= T){
                        maxx = max(maxx, val);
                        continue;
                    }

                    
                    space[!t][A][{a+1, b, K}] = max(
                                                (space[!t][A].count({a+1, b, K}) > 0)? space[!t][A][{a+1, b, K}] : -INF, 
                                                val 
                                                + (getchar(vec, A, a+1, b+1, n1, n2) == getchar(vec, A, a, b, n1, n2))
                                                );


                    if(K > 0){

                        space[!t][!A][{a, b+1, K-1}] = max(
                                                    (space[!t][!A].count({a, b+1, K-1}) > 0)? space[!t][!A][{a, b+1, K-1}] : -INF, 
                                                    val 
                                                    + (getchar(vec, !A, a+1, b+1, n1, n2) == getchar(vec, A, a, b, n1, n2))
                                                    );
                    }
                }
                
                // ==============================


                //cout<<"B----\n";
                while(!space[t][B].empty()){
                    cnt = 1;
                    auto it = (space[t][B].begin());
                    auto x = *it;
                    space[t][B].erase(it);

                    

                    auto [f1, val] = x;
                    auto [a, b, K] = f1;
                    //cout<<"{"<<a<<", "<<b<<", "<<K<<"} -> "<<val<<"     ";
                    //cout<<getchar(vec, B, a, b, n1, n2)<<" ["<<getchar(vec, !B, a+1, b+1, n1, n2)<<", "<<getchar(vec, B, a+1, b+1, n1, n2)<<"]\n";


                    if(a + b >= T){
                        maxx = max(maxx, val);
                        continue;
                    }

                    space[!t][B][{a, b+1, K}] = max(
                                                (space[!t][B].count({a, b+1, K}) > 0)? space[!t][B][{a, b+1, K}] : -INF,
                                                val 
                                                + (getchar(vec, B, a+1, b+1, n1, n2) == getchar(vec, B, a, b, n1, n2))
                                                );

                    if(K > 0){

                        space[!t][!B][{a+1, b, K-1}] = max(
                                                    (space[!t][!B].count({a+1, b, K-1}) > 0)? space[!t][!B][{a+1, b, K-1}] : -INF, 
                                                    val 
                                                    + (getchar(vec, !B, a+1, b+1, n1, n2) == getchar(vec, B, a, b, n1, n2))
                                                    );
                    }
                }
                
                // ==============================
        t = !t;
    }
    //cout<<"asñdklfjasdkñlfjañldksfjaosidfjd\n";
    return maxx;
}

int main() {
    int K, T, n1, n2;
    cin>>K>>T;

    vector<vector<int>> vec(2);
    string dumm;
    cin>>n1;
    vec[0].resize(n1);
    for(int i=0; i<n1; i++){
        cin>>dumm;
        vec[0][i] = strtoint(dumm);
    }
    cin>>n2;
    vec[1].resize(n2);
    for(int i=0; i<n2; i++){
        cin>>dumm;
        vec[1][i] = strtoint(dumm);
    }
    int ans = solve(vec, K, T, n1, n2);
    cout<<ans<<"\n";
    return 0;
}
