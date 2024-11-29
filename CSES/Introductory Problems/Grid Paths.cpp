#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back
#define sz size()

const int len = 7;
typedef pair<int, int> pii;
// typedef pair<int, pii> piii;
vector<pii> adj(4);
// stack<piii> st;
vector<set<int>> rows(len+1), columns(len+1);
int ans = 0;

void calculateAdj(){
    adj[0] = {-1, 0};
    adj[1] = {1, 0};
    adj[2] = {0, -1};
    adj[3] = {0, 1};
}

void calculateMoves(int moves, pii cell, bool maze[][len + 1], string &s){
    int xi = cell.first, yi = cell.second;
    maze[xi][yi] = 1;

    vector<pii> option, have;
    if(s[moves] == '?'){
        for(pii to : adj){
            int xf = xi + to.first, yf = yi + to.second;
            if(xf > len || xf < 1 || yf > len || yf < 1 || maze[xf][yf]) continue;
            if(xf == 1 && yf == len){
                if(moves == len * len - 2) ans++;
                else continue;
            }
            if((xf == len || xf == 0)  && yf - 1 > 1 && !maze[xf][yf - 1] && yf < len && !maze[xf][yf + 1]) continue;
            if((yf == len || yf == 0) && xf - 1 > 1 && !maze[xf - 1][yf] && xf < len && !maze[xf + 1][yf]) continue;
            if(yf > 1 && yf < len && !maze[xf][yf - 1] && !maze[xf][yf + 1] && (xf == 1 || maze[xf - 1][yf]) && (xf == len || maze[xf + 1][yf])) continue;
            if(xf > 1 && xf < len && !maze[xf - 1][yf] && !maze[xf + 1][yf] && (yf == 1 || maze[xf][yf - 1]) && (yf == len || maze[xf][yf + 1])) continue;

            int posible = 0;
            for(pii to2 : adj){
                int xf2 = xf + to2.first, yf2 = yf + to2.second;
                if(xf2 > len || xf2 < 1 || yf2 > len || yf2 < 1 || maze[xf2][yf2] || 
                (xf == 1 && yf == len && moves != len * len - 3)) continue;
                posible++;
            }

            if(posible == 0) continue;
            if(posible == 1) have.pb({xf, yf});
            else option.pb({xf, yf});
        }
    }

    else{
        int xf = xi, yf = yi;
        if(s[moves] == 'U') yf--;
        else if(s[moves] == 'D') yf++;
        else if(s[moves] == 'R') xf++;
        else xf--;

        bool cond = 1;
        if(xf > len || xf < 1 || yf > len || yf < 1 || maze[xf][yf]) cond = 0;
        if(xf == 1 && yf == len){
            if(moves == len * len - 2) ans++;
            else cond = 0;
        }

        if((xf == len || xf == 0)  && yf - 1 > 1 && !maze[xf][yf - 1] && yf < len && !maze[xf][yf + 1]) cond = 0;
        if((yf == len || yf == 0) && xf - 1 > 1 && !maze[xf - 1][yf] && xf < len && !maze[xf + 1][yf]) cond = 0;
        if(yf > 1 && yf < len && !maze[xf][yf - 1] && !maze[xf][yf + 1] && (xf == 1 || maze[xf - 1][yf]) && (xf == len || maze[xf + 1][yf])) cond = 0;
        if(xf > 1 && xf < len && !maze[xf - 1][yf] && !maze[xf + 1][yf] && (yf == 1 || maze[xf][yf - 1]) && (yf == len || maze[xf][yf + 1])) cond = 0;

        if(!cond){
            maze[xi][yi] = 0;
            return;
        }

        cond = 0;
        if(moves + 1 < 48 && s[moves + 1] == '?'){
            for(pii to2 : adj){
                int xf2 = xf + to2.first, yf2 = yf + to2.second;
                if(xf2 > len || xf2 < 1 || yf2 > len || yf2 < 1 || maze[xf2][yf2] || 
                (xf == 1 && yf == len && moves != len * len - 3)) continue;
                cond = 1;
            }
        }
        else{
            int xf2 = xf, yf2 = yf;
            if(s[moves + 1] == 'U') yf2--;
            else if(s[moves + 1] == 'D') yf2++;
            else if(s[moves + 1] == 'R') xf2++;
            else xf2--;
            if(!(xf2 > len || xf2 < 1 || yf2 > len || yf2 < 1 || maze[xf2][yf2] || 
            (xf == 1 && yf == len && moves != len * len - 3))) cond = 1;
        }

        if(!cond){
            maze[xi][yi] = 0;
            return;
        }
        have.pb({xf, yf});
    }

    if(have.sz > 1){ // Esta solucion no sirve
        maze[xi][yi] = 0;    
        return;
    } 
    if(have.sz == 1) calculateMoves(moves + 1, have[0], maze, s);
    else{
        for(int i = 0; i < option.sz; i++){
            calculateMoves(moves + 1, option[i], maze, s);
        }
    }
    maze[xi][yi] = 0;
}

void solver(){
    string s; cin>>s;
    calculateAdj();
    bool maze[len+1][len+1];
    for(int i = 1; i < len+1; i++){
        for(int j = 1; j < len+1; j++){
            rows[i].insert(j);
            columns[i].insert(j);
            maze[i][j] = 0;
        }
    }

    calculateMoves(0, {1, 1}, maze, s);
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