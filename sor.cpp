#include <bits/stdc++.h>

using namespace std;

int n, a;
int liczby[1005];
int tab[1005][1005][2];
long long wynik;



void wczytaj(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> liczby[i];
    }
}

void wypisz(){
    for(int i = 1; i<= n;i++){
        for(int j = 1;j <= n;j++){
            cout << tab[i][j][0] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    for(int i = 1; i<= n;i++){
        for(int j = 1;j <= n;j++){
            cout << tab[i][j][1] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void odpal(){
    for(int i = 1;i <= n;i++){
        tab[i][i][1] = 1;
    }
    for(int j = 0;j < n-1;j++) {
        for (int i = 2+j; i <= n; i++) {
            if(liczby[i-1-j] < liczby[i]){
                tab[i-1-j][i][1] += tab[i-1-j][i-1][0];
            }
            if(liczby[i-1] < liczby[i]){
                tab[i-1-j][i][1] += tab[i-1-j][i-1][1];
            }
            if(liczby[n-i+1] < liczby[n-i+2]){
                tab[n-i+1][n-i+2+j][0] += tab[n-i+2][n-i+2+j][0];
            }
            if(liczby[n-i+1] < liczby[n-i+2+j]){
                tab[n-i+1][n-i+2+j][0] += tab[n-i+2][n-i+2+j][1];
            }
            if(tab[i-1-j][i][1] > (int)(1e9)){
                tab[i-1-j][i][1] %= (int)(1e9);
            }
            if(tab[n-i+1][n-i+2+j][0] > (int)(1e9)){
                tab[n-i+1][n-i+2+j][0] %= (int)(1e9);
            }
        }
    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    wczytaj();
    odpal();
    cout << ((tab[1][n][0] + tab[1][n][1])%(int)(1e9)) << '\n';
    return 0;
}