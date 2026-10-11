#include <bits/stdc++.h>
using namespace std;

vector<set<int>> gp(10);

int O = -1;
int E = 0;
int X = 1;
int INF=10;

map<int, pair<int, int>> chash;
map<pair<int, int>, int> invhash;

void DEBUG(vector<vector<int>>& board){
    cout<<"----------\n";
     for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == O) cout<<"O ";
            if(board[i][j] == 0) cout<<". ";
            if(board[i][j] == X) cout<<"X ";
        }
        cout<<"\n";
    }
    cout<<"----------\n";
}

int check(int& flag, vector<vector<int>>& board){


    //chech row
    for(int i=0; i<3; i++){
        int sum=0;
        for(int j=0; j<3; j++){
            sum += board[i][j];
        }
        if(sum == 3) return X;
        if(sum == -3) return O;
    }

    //check col
    for(int j=0; j<3; j++){
        int sum=0;
        for(int i=0; i<3; i++){
            sum += board[i][j];
        }
        if(sum == 3) return X;
        if(sum == -3) return O;
    }

    //check diagonals
    int sum=0;
    sum = board[0][0] + board[1][1] + board[2][2];
    if(sum == 3) return X;
    if(sum == -3) return O;

    sum = 0;
    sum = board[2][0] + board[1][1] + board[0][2];
    if(sum == 3) return X;
    if(sum == -3) return O;


    return E;
}

bool canPlay(int i, int j, vector<vector<int>>& board){
    for(int v : gp[invhash[{i, j}]]){
        auto [y, x] = chash[v];
        if(board[y][x] == 0) return 0;
    }
    return 1;
}

int minmax(int p, vector<vector<int>> board){
    int ans=check(ans, board);

    //cout<<p<<" |";DEBUG(board);
    if(ans != 0){
        //cout<<" =============> "<<ans<<"\n";
        return ans;
    }

    if(p == X){
        int game=-INF;
        bool can=0;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] != 0
                || !canPlay(i, j, board)) continue;
                can = 1;
                board[i][j] = X;
                game = max(game, minmax(O, board));
                board[i][j] = 0;
            }
        }
        if(!can) game = 0;
        return game;
    }

    if(p == O){
        bool can=0;
        int game=INF;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] != 0
                || !canPlay(i, j, board)) continue;
                can = 1;
                board[i][j] = O;
                game = min(game, minmax(X, board));
                board[i][j] = 0;
            }
        }
        if(!can) game = 0;
        return game;
    }
    board[0][0] = 'O';

    return E;
}

int main(){
    int n;
    cin>>n;
    int a, b;
    for(int i=0; i<n; i++){
        cin>>a>>b;
        gp[b].insert(a);
    }

    /*
    1 | 2 | 3
    4 | 5 | 6
    7 | 8 | 9
    */
    chash[1] = {0, 0};
    chash[2] = {0, 1};
    chash[3] = {0, 2};
    chash[4] = {1, 0};
    chash[5] = {1, 1};
    chash[6] = {1, 2};
    chash[7] = {2, 0};
    chash[8] = {2, 1};
    chash[9] = {2, 2};

    invhash[{0, 0}] = 1;
    invhash[{0, 1}] = 2;
    invhash[{0, 2}] = 3;
    invhash[{1, 0}] = 4;
    invhash[{1, 1}] = 5;
    invhash[{1, 2}] = 6;
    invhash[{2, 0}] = 7;
    invhash[{2, 1}] = 8;
    invhash[{2, 2}] = 9;

    vector<vector<int>> board(3, vector<int>(3));

    //DEBUG(board);
    int ans = minmax(X, board);

    char lt[] = {'O', 'E', 'X'};
    cout<<lt[ans+1]<<"\n";

    return 0;
}