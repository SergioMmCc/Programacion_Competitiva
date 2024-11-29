#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ld = long double;
#define pb push_back

vector<int> factorial(9);

void preCalcFactorial(){
    factorial[0] = 1;
    for(int i = 1; i < 9; i++) factorial[i] = factorial[i-1] * i;
}

void solver(){
    preCalcFactorial();
    string s; cin>>s;
    int n = s.size();
    int total = factorial[n];

    vector<int> freq(27);
    for(int i = 0; i < n; i++) freq[s[i] - 'a']++;
    for(int i = 0; i < 27; i++) total /= factorial[freq[i]];

    cout<<total<<endl;

    set<string> ans;
    vector<string> words;
    string firstWord = "";
    firstWord += s[0];
    words.pb(firstWord);
    for(int i = 1; i < n; i++){
        char letter = s[i];
        for(int j = words.size() - 1; j >= 0; j--){
            words[j] += letter;
            string change = words[j];
            for(int k = change.size() - 2; k >= 0; k--){
                string aux = change;
                aux[k] = letter;
                aux[aux.size()-1] = change[k];
                words.pb(aux);
            }
        }
    }

    for(string word : words) ans.insert(word);
    for(string word : ans) cout<<word<<endl;
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