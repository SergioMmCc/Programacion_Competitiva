#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define db(x) cerr<< #x<<" "<<x<<endl
#define for0(i,n) for(int i = 0; i < (int)n; i++)
#define for1(i,n) for(int i = 1; i <= (int)n; i++)
#define forlr(i,l,r) for(int i = (int)l; i <= (int)r; i++)
#define forn1(i,n) for(int i = (int)n; i > 0; i--)
#define forn0(i,n) for(int i = (int)(n) - 1; i >= 0; i--)
#define forrl(i,l,r) for(int i = (int)r; i >= (int)l; i--)
#define pb push_back
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pqueue priority_queue
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<pll> vll;
// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using indexed_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INFL = 1000000000000000001;
const int INF = 1e9 + 1;
// const ll MOD = 1e9 + 7;

/*
- 1-index.
- Permite hacer borrado de aristas, con el orden de una pila.
- La complejidad es la igual a la del DSU normal, en este 
  caso usando union-by-size sin compresion.
Funcionamiento:
- Cuando se agrega una arista u->v, si 'u' y 'v' ya estaban 
  en el mismo componente esta se ignora. De lo contrario se 
  agrega al DSU y a la pila de aristas.
- snapshot guarda la cantidad de operaciones reales que se 
  han hecho en el DSU hasta ahora. Quiere decir que al hacer 
  join entre dos nodos que ya estan en el mismo componente, 
  esta operacion no se cuenta.
- rollback(t) borra aristas del DSU hasta que solo queden 
  't'.
- En algunos ejercicios se usa una tecnica de guardado y el 
  rollback borra hasta el ultimo guardado (y elimina ese 
  ultimo guardado tambien).
  Para manejar esto se agrega una pila extra de guardados, en 
  la cual cada que se hace un guardado se mete la cantidad de 
  aristas del DSU en el momento en que se hizo. Entonces 
  cuando se pida hacer rollback, se manda como parametro el
  tope de la pila de guardados y se elimina.
- Si en los rollback se quiere borrar la arista 
  inmediatamente anterior, es posible que esta haya sido 
  ignorada ya que conectaba dos nodos que ya estaban en el 
  mismo componente.
  Para manejar este caso se puede usar la misma tecnica del
  caso superior, haciendo un guardado cada que se intenta
  agregar una arista.
*/

struct DSURollback {
    vi p, len;
    stack<pii> st;
    int comps;

    DSURollback(int n) : p(n), len(n, 1), comps(n-1) { iota(all(p), 0); }
    int find(int x){
        while(p[x] != x) x = p[x];
        return x;
    }
    bool join(int a, int b){
        a = find(a); b = find(b);
        if(a == b) return 0;
        if(len[a] < len[b]) swap(a, b);
        p[b] = a; len[a] += len[b]; comps--;
        st.push({a, b});
        return 1;
    }
    int snapshot() { return sz(st); }
    void rollback(int t){ // deshace hasta que la pila tenga tamaño t
        while(sz(st) > t){
            auto [a, b] = st.top(); st.pop();
            len[a] -= len[b]; p[b] = b; comps++;
        }
    }
};

void solver(){
    int n, q; cin>>n>>q;
    stack<int> save;
    DSURollback uf(n+1);
    for0(i,q){
        string op; cin>>op;
        if(op == "union"){ // Agregar arista
            int u, v; cin>>u>>v;
            uf.join(u, v);
            cout<<uf.comps<<endl;
        }
        else if(op == "persist"){ // Agregar guardado
            save.push(uf.snapshot());  
        }
        else if(op == "rollback"){ // Hacer rollback al ultimo guardado
            if(save.empty()) uf.rollback(0); // Borrar todas las aristas si no hay ningun guardado
            else{
                uf.rollback(save.top());
                save.pop();
                cout<<uf.comps<<endl;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("name.in", "r", stdin);
	// freopen("name.out", "w", stdout);
    int t = 1;
    // cin>>t;
    while(t--){
        solver();
    }

    return 0;
}