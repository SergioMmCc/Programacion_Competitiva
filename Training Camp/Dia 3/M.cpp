#include<bits/stdc++.h>
using namespace std;
#define MAXT 200000

vector<set<int>> G(MAXT+1);
queue<int> q;
vector<int> sons(MAXT+1);
vector<int> visited(MAXT+1, 0);
vector<vector<int>> grupo;
vector<pair<int, int>> ans;

void componentes(int start) {
    int u;
    q.push(start);
    while(!q.empty()) {
        u = q.front();
        q.pop();
        for(int i : G[u]) {
            if(visited[i] == 1)
                continue;
            else {
                if(i == 1) {
                    sons[i] = 1;
                    grupo[]
                    continue;
                } 
                q.push(i);
            }
        }
    }
}

int main() {
    int n, m, d, u, v;
    int nComp = 0;
    cin >> n >> m >> d;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        G[v].insert(u);
        G[u].insert(v);
    }

    for(int i : G[1]) {
        if(sons[i] == 1)
            continue;
        else {
            nComp++;
            grupo.push_back(vector<int>(1, i));
            componentes(i, &nComp);
        }
    }

    if(nSons != d)
        cout << "NO\n";
    else {
        cout << "YES\n";
        for(int i = 0; i < ans.size(); i++)
            cout << ans[i].first << " " << ans[i].second << "\n";
    }

    return 0;
}