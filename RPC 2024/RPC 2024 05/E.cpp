#include <bits/stdc++.h>
using namespace std;
#define limite 1000005



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
    
    int primos[79000];
    int s = 1;
    for (int i = 2; i <= limite; i++) {
        if (es_primo[i]) {
            primos[s] = i;
            s++;
        }
    }
    //--------------------------------------------------
    int days;cin >> days;
    
    int save;
    int test;
    vector<vector<int>> freq(1, vector<int>(79000, 0));
    for (int i = 1; i <= days; i++) {
        freq.push_back(vector<int>(79000, 0));
        cin >> save;
        test = 1;
        
        while (save != 1) {
            if (save % primos[test] == 0) {
                if (freq[i][test] == 0) 
                    freq[i][test] = freq[i-1][test] + 1;
                else
                    freq[i][test]++;
                save /= primos[test];
            }
            else test++;
        }
    }

    bool possible;
    int q, l, r, n;
    cin >> q;
    while (q--) {
        possible = true;
        test = 1;
        cin >> l >> r >> n;
        l--;
        vector<int> caso(79000, 0);
        while (n != 1 && possible) {
            if (n % primos[test] == 0) {
                caso[test]++;
                if (caso[test] > freq[r][test] - freq[l][test]) {
                    possible = false;
                    cout << primos[test] << " " << caso[test] << " " << freq[r][test] << " " << freq[l][test] << "\n";
                }
                n /= primos[test];
            }
            else test++;
        }
        if (possible) cout << "Yes\n";
        else cout << "No\n";
    }
    
    return 0;
}