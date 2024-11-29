#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

typedef pair<int, int> pii;

void validateRow(int row, int &ans, char maze[][8], stack<pii>& st, vector<bool>& column, vector<bool>& diaglr, vector<bool> diagrl){
    for(int col = 0; col < 8; col++){
        while(!st.empty() && st.top().first >= row){
            pii cell = st.top();
            int rowAux = cell.first, colAux = cell.second;
            column[colAux] = 0;
            diaglr[rowAux + colAux] = 0;
            diagrl[rowAux + (7 - colAux)] = 0;
            st.pop();
        }
        if(maze[row][col] == '.' && !column[col] && !diaglr[row + col] && !diagrl[row + (7 - col)]){
            if(row == 7) ans++;
            else{
                st.push({row, col});
                column[col] = 1;
                diaglr[row + col] = 1;
                diagrl[row + (7 - col)] = 1;
                validateRow(row + 1, ans, maze, st, column, diaglr, diagrl);
            }
        }
    }
}

void solver(){
    char maze[8][8];
    for(int i = 0; i < 8; i++) cin>>maze[i];

    vector<bool> column(8), diaglr(15), diagrl(15);
    int ans = 0;
    stack<pii> st;
    validateRow(0, ans, maze, st, column, diaglr, diagrl);

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