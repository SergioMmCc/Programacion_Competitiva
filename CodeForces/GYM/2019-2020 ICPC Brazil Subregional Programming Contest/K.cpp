// Source: https://usaco.guide/general/io

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
const ll MOD = 1e9 + 7;


/*
- Algunas funciones para operaciones con matrices perfectas (n x n).
APLICACIONES:
- Se puede hallar el numero de caminos de una longitud especifica 
  'k' elevando su matriz de adyacencia a la potencia 'k'.
  La posicion i,j en dicha matriz dice la cantidad de caminos de
  longitud 'k' que inician en el vertice 'i' y terminan en el 
  vertice 'j'.
  * Sirve tanto para grafos dirigidos como no dirigidos.
  * Soporta loops.
  * Soporta aristas multiples si en la matriz de adyacencia se 
    guarda cuantas aristas hay desde 'i' hasta 'j'.
  * Si se quieren hallar la cantidad de caminos de longitud maximo 
    'k' que inician en 'i', se crea un vertice extra 's' que tiene 
    una arista hacia si mismo y hacia el cual todos los demas 
    vertices tienen una arista. Se hace exponenciacion con potencia
    'k+1'. La cantidad de caminos que inician en 'i' y tienen maximo 
    longitud 'k' queda en la posicion i,s despues de la 
    exponenciacion. (Quedan incluidos los caminos de longitud '0').
*/

struct Matrix {
    int n;
    vector<vl> M;

    Matrix(int n) : n(n), M(n, vl(n, 0)) {}

    // La matrix identidad, donde todo es '0' excepto en la diagonal principal, que es '1' 
    static Matrix identity(int n){
        Matrix I(n);
        for0(i,n) I.M[i][i] = 1;
        return I;
    }

    // Multiplicación de matrices O(n^3)
    Matrix operator*(const Matrix& other) const {
        Matrix result(n);
        for0(i,n){
            for0(k,n){
                if(!M[i][k]) continue;
                for0(j,n) result.M[i][j] = (result.M[i][j] + (M[i][k] * other.M[k][j] % MOD)) % MOD;
            }
        }
        return result;
    }

    // Suma de matrices (n^2)
    Matrix operator+(const Matrix& other) const {
        Matrix result(n);
        for0(i,n) for0(j,n) result.M[i][j] = (M[i][j] + other.M[i][j]) % MOD;
        return result;
    }

    // Exponenciacion de una matrix, usando exponenciacion binaria en O(log(exp) * n^3)
    Matrix binpow(ll exp) const {
        Matrix result = identity(n);
        Matrix base = *this;

        while(exp){
            if(exp & 1) {
                result = result * base;
            }

            base = base * base;
            exp >>= 1;
        }
        return result;
    }

    // Transpuesta de la matriz: T[j][i] = M[i][j], O(n^2)
    Matrix transpose() const {
        Matrix T(n);
        for0(i,n) for0(j,n) T.M[j][i] = M[i][j];
        return T;
    }

    // Debug, muestra la matrix en el cout
    friend ostream &operator<<(ostream &os, const Matrix &matrix){
        os << "\nMatrix: \n";
        for0(i,matrix.n){
            for0(j,matrix.n){
                os << matrix.M[i][j] << " ";
            }
            os << endl;
        }
        os << " =============== \n";
        return os;
    }
};

void solver(){
    // Lectura
    Matrix m(4);

    m.M = 
    {
        {2, 4, 0, 1},
        {1, 0, 0, 0},
        {0, 16, 2, 0},
        {0, 0, 0, 2}
    };




    ll exp; cin>>exp;
    
    if(exp==1){
        cout<<"2\n";
        return;
    }

    Matrix ans = m.binpow(exp-2); // Para llamar una funcion

    ll val1 = ans.M[0][0]*6 + ans.M[0][1]*1 + ans.M[0][3]*4;
    val1 %= MOD;
    ll val2 = ans.M[2][0]*6 + ans.M[2][1]*1 + ans.M[2][3]*4;
    val2 %= MOD;
    ll val = val1*4 + val2;
    val %= MOD;
    cout<<val<<"\n"; // Imprime la matriz
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