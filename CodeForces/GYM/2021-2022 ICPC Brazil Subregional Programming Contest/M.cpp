// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct Node{
    int id=-1;
    Node* parent=nullptr;

    set<int> childs;

    Node(int id, Node* parent = nullptr)
        : id(id), parent(parent) {}
};

Node* addNode(int& idx, Node* parent, vector<Node*>& person){
    Node* t = new Node(idx, parent);

    person[idx] = t;

    if(parent != nullptr){
        parent->childs.insert(idx);
    }
    idx++;
    return t;
}

int nextLead(int x, vector<int>& alive, vector<Node*>& person){
    // define next leader
    // show the new leader
    // childs > sibling
    // olders ones first (less index value)
    if(alive[x]) return x;

    Node* cur = person[x];

    while (true) {
        if (!cur->childs.empty()) {
            cur = person[*cur->childs.begin()];
        }
        else
        {
            //SIBLING!!!!
            while (cur->parent != nullptr) {
                Node* p = cur->parent;

                auto it = p->childs.upper_bound(cur->id);

                if (it != p->childs.end()) {
                    cur = person[*it];
                    break;
                }

                cur = p; //  no more childsss
            }

            if (cur->parent == nullptr && cur->childs.empty()) {
                // and everyone die, end :3
                return -1;
            }
        }

        if (alive[cur->id]) {
            return cur->id;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int q;
    cin>>q;

    int t, x;
    int idx=1, lead=1;
    vector<Node*> person(q+3, nullptr);
    vector<int> alive(q+3, 1);
    person[1] = addNode(idx, nullptr, person);
    while(q--){
        cin>>t>>x;

        if(t == 1){
            // add a new child
            Node* t = addNode(idx, person[x], person);
            person[t->id] = t;
        }

        if(t == 2){
            // die a person
            alive[x] = 0;
            lead = nextLead(lead, alive, person);
            cout<<lead<<"\n";

        }
    }
}
