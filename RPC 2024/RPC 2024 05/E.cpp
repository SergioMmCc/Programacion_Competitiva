#include <bits/stdc++.h>
using namespace std;
#define limite 1000005

int binarySearch (const vector<int>& A, int i, int j, int k) {
    int m;
    while (i <= j) {
        m = (i + j) >> 1;
        if (A[m] == k)
            return m;
        else if (k > A[m])
            i = m + 1;
        else
            j = m - 1;
    }
    return -i -1;
}

int binarySearchFirstOccurrence(const vector<int>& A, int i, int j, int k) {
    int result, result2;
    result = binarySearch(A, i, j, k);
    if (result >= 0) {
        result2 = binarySearch(A, i, result - 1, k);
        while (result2 >= 0) {
            result = result2;
            result2 = binarySearch(A, i, result - 1, k);
        }
    }
    return result;
}

int binarySearchLastOccurrence(const vector<int>& A, int i, int j, int k) {
    int result, result2;
    result = binarySearch(A, i, j, k);
    if (result >= 0) {
        result2 = binarySearch(A, result + 1, j, k);
        while (result2 >= 0) {
            result = result2;
            result2 = binarySearch(A, result + 1, j, k);
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    
    //Guardar los numeros primos en un arreglo
    bool es_primo[limite + 1];
    
    es_primo[0] = es_primo[1] = false;
    for (int i = 2; i <= limite; ++i) 
        es_primo[i] = true;
    
    for (long long int p = 2; p * p <= limite; p++) {
        if (es_primo[p]) {
            for (long long int i = p * p; i <= limite; i += p) 
                es_primo[i] = false;
        }
    }
    
    vector<int> primos;
    primos.push_back(0);
    for (int i = 2; i <= limite; i++) {
        if (es_primo[i]) 
            primos.push_back(i);
    }
    //--------------------------------------------------
    int days;cin >> days;
    int save;
    int test;
    vector<vector<int>> freq(primos.size()+1, vector<int>(1, 0));
    for (int i = 1; i <= days; i++) {
        cin >> save;
        test = 1;
        
        while (save != 1) {
            if (save % primos[test] == 0) {
                freq[test].push_back(i);
                save /= primos[test];
            }
            else test++;
        }
    }

    bool possible;
    int q, l, r, n, searchL, searchR;
    cin >> q;
    while (q--) {
        possible = true;
        test = 1;
        cin >> l >> r >> n;
        vector<int> caso(primos.size()+1, 0);
        while (n != 1 && possible) {
            if (n % primos[test] == 0) {
                caso[test]++;
                n /= primos[test];
            }
            else {
                if (caso[test] > 0) {
                    searchL = binarySearchFirstOccurrence(freq[test], 1, freq[test].size()-1, l);
                    searchR = binarySearchLastOccurrence(freq[test], 1, freq[test].size()-1, r);
                    if (searchL < 0)searchL = -searchL -1;
                    else if (searchR < 0)searchR = -searchR -2;
                    if (searchR - searchL + 1 < caso[test])
                        possible = false;
                }
                test++;
            }
        }
        if (possible) {
            if (caso[test] > 0) {
                searchL = binarySearchFirstOccurrence(freq[test], 1, freq[test].size()-1, l);
                searchR = binarySearchLastOccurrence(freq[test], 1, freq[test].size()-1, r);
                if (searchL < 0)searchL = -searchL -1;
                else if (searchR < 0)
                    searchR = -searchR -2;
                if (searchR - searchL + 1 < caso[test])
                    possible = false;
            }
        }
        if (possible) cout << "Yes\n";
        else cout << "No\n";
    }
    
    return 0;
}