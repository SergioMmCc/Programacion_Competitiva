#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
typedef vector<vector<long long>> matrix;

/* Multiplicación de matrices
  - Se multiplica la fila de A con la columna de B
  - Para poder multiplicar el numero de columnas de A debe ser igual al 
    numero de filas de B, y la matriz resultante tendra el mismo numero
    filas que A y el mismo numero de columnas de B
*/
matrix multMatrix (const matrix &A, const matrix &B) {
    int len = A.size();
    matrix result(len, vector<long long>(len, 0));
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) 
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % mod;
        }
    }
    return result;
}

// Potencia de una matriz
// Cualquier matriz elevada a la 0 da como resultado la matriz identidad
matrix potMatrix (matrix A, long long expo) {
    int len = A.size();
    matrix result(len, vector<long long>(len, 0));
    for (int i = 0; i < len; i++)
        result[i][i] = 1;
    while (expo > 0) {
            if (expo % 2 == 1)
                result = multMatrix(result, A);
            A = multMatrix(A, A);
            expo /= 2;
    }
    return result;
}

long long gcd (long long a, long long b) {
    long long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*
  Para este ejercicio un vertice i se conecta con un vertice j si gcd(i, j) == 1
  La matriz A representa la matriz de adyacencia del grafo
  La matriz B representa la matriz de adyacencia del grafo elevada a la n-1
  La potencia de la matriz de adyacencia del grafo es la cantidad de caminos de longitud n entre los vertices
  Si quiero saber el número de caminos de longitud n, debo elevar la matriz de adyacencia a la n-1
*/
int main() {
    long long n, D, k, s;
    cin >> n >> D >> k >> s;
    matrix A(n+3, vector<long long>(n+3, 0));
    A[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A[i][j] = (abs(i-j) <= D || (n - abs(i-j)) <= D);
        }
        A[i][n+1] = 1;
    }
    A[n+1][n+1] = 1;
    
    A = potMatrix(A, k);


    cout<<A[s][n+1]<<"\n";
    
    return 0;
}