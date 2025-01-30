#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()
typedef pair<int, int> pii;

unordered_map<int, int> d;
vector<int> pot9(9);
 
void calcPot9(){
    pot9[0] = 1;
    for(int i = 1; i < 9; i++) pot9[i] = 9 * pot9[i-1];
}
 
int calcNum(const vector<vector<int>>& matriz){
    int num = 0;
    num += pot9[0] * (matriz[1][1] - 1);
    num += pot9[1] * (matriz[1][2] - 1);
    num += pot9[2] * (matriz[1][3] - 1);
    num += pot9[3] * (matriz[2][1] - 1);
    num += pot9[4] * (matriz[2][2] - 1);
    num += pot9[5] * (matriz[2][3] - 1);
    num += pot9[6] * (matriz[3][1] - 1);
    num += pot9[7] * (matriz[3][2] - 1);
    num += pot9[8] * (matriz[3][3] - 1);
 
    return num;
}
 
int BFS(vector<vector<int>>& start){
    queue<vector<vector<int>>> q; q.push(start);
    int num = calcNum(start);
    d[num] = 0;
    while(!q.empty()){
        vector<vector<int>> u = q.front(); q.pop();
        if(u[1][1] == 1 && u[1][2] == 2 && u[1][3] == 3
        && u[2][1] == 4 && u[2][2] == 5 && u[2][3] == 6
        && u[3][1] == 7 && u[3][2] == 8 && u[3][3] == 9) return d[calcNum(u)];

        int numU = calcNum(u);
        vector<vector<int>> v(4, vector<int>(4));
        v = u;
        for(int i = 1; i <= 12; i++){
            if(i == 1){
                v[1][1] = u[1][2];
                v[1][2] = u[1][1];
            }
            else if(i == 2){
                v[1][1] = u[2][1];
                v[2][1] = u[1][1];
            }
            else if(i == 3){
                v[1][2] = u[1][3];
                v[1][3] = u[1][2];
            }
            else if(i == 4){
                v[1][2] = u[2][2];
                v[2][2] = u[1][2];
            }
            else if(i == 5){
                v[1][3] = u[2][3];
                v[2][3] = u[1][3];
            }
            else if(i == 6){
                v[2][1] = u[2][2];
                v[2][2] = u[2][1];
            }
            else if(i == 7){
                v[2][1] = u[3][1];
                v[3][1] = u[2][1];
            }
            else if(i == 8){
                v[2][2] = u[2][3];
                v[2][3] = u[2][2];
            }
            else if(i == 9){
                v[2][2] = u[3][2];
                v[3][2] = u[2][2];
            }
            else if(i == 10){
                v[2][3] = u[3][3];
                v[3][3] = u[2][3];
            }
            else if(i == 11){
                v[3][1] = u[3][2];
                v[3][2] = u[3][1];
            }
            else{ // i == 12
                v[3][2] = u[3][3];
                v[3][3] = u[3][2];
            }
 
            int numV = calcNum(v);
            if(d.find(numV) == d.end()){
                d[numV] = d[numU] + 1;
                q.push(v);
            }
            if(i == 1){
                v[1][1] = u[1][1];
                v[1][2] = u[1][2];
            }
            else if(i == 2){
                v[1][1] = u[1][1];
                v[2][1] = u[2][1];
            }
            else if(i == 3){
                v[1][2] = u[1][2];
                v[1][3] = u[1][3];
            }
            else if(i == 4){
                v[1][2] = u[1][2];
                v[2][2] = u[2][2];
            }
            else if(i == 5){
                v[1][3] = u[1][3];
                v[2][3] = u[2][3];
            }
            else if(i == 6){
                v[2][1] = u[2][1];
                v[2][2] = u[2][2];
            }
            else if(i == 7){
                v[2][1] = u[2][1];
                v[3][1] = u[3][1];
            }
            else if(i == 8){
                v[2][2] = u[2][2];
                v[2][3] = u[2][3];
            }
            else if(i == 9){
                v[2][2] = u[2][2];
                v[3][2] = u[3][2];
            }
            else if(i == 10){
                v[2][3] = u[2][3];
                v[3][3] = u[3][3];
            }
            else if(i == 11){
                v[3][1] = u[3][1];
                v[3][2] = u[3][2];
            }
            else{ // i == 12
                v[3][2] = u[3][2];
                v[3][3] = u[3][3];
            }
        }
    }
}
 
void solver(){
    vector<vector<int>> start(4, vector<int>(4));
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            cin>>start[i][j];
        }
    }
 
    cout<<BFS(start)<<endl;
}
 
int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    calcPot9();
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }
 
    return 0;
}