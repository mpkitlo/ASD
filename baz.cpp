#include <bits/stdc++.h>

long long m, n, a, maksimum = 0;

using namespace std;

vector <long long> lista_cen;
vector <long long> zapytania;

long long wynik[(long long)(1e6+5)];
long long lewe_p[(long long)(1e6+5)];
long long lewe_np[(long long)(1e6+5)];
long long prawe_p[(long long)(1e6+5)];
long long prawe_np[(long long)(1e6+5)];

void wczytaj(){

    cin >> n;

    lista_cen.push_back((int)(1e6)*(-1));

    lewe_p[0] = (int)(1e9 + 5)*(-1);
    lewe_np[0] = (int)(1e9 + 5)*(-1);
    prawe_p[n+1] = (int)(1e9 + 5);
    prawe_np[n+1] = (int)(1e9 + 5);
    lewe_p[n+1] = (int)(1e9 + 5)*(-1);
    lewe_np[n+1] = (int)(1e9 + 5)*(-1);
    prawe_p[0] = (int)(1e9 + 5);
    prawe_np[0] = (int)(1e9 + 5);

    for(long long i = 0;i < n;i++){
        cin >> a;
        lista_cen.push_back(a);
    }

    sort(lista_cen.begin(), lista_cen.end());

    cin >> m;
    for(long long i = 0;i < m;i++){
        cin >> a;
        zapytania.push_back(a);
        maksimum = max(maksimum, a);
    }

}

void wykonaj(){
    for(int i = 1;i <= n;i++){
        wynik[i] = lista_cen[n - i + 1] + wynik[i-1];
    }
    for(int i = 1;i <= n;i++){
        if(lista_cen[i] % 2 == 1){
            lewe_np[i] = max(lewe_np[i-1], lista_cen[i]);
            lewe_p[i] = lewe_p[i-1];
        }
        else{
            lewe_p[i] = max(lewe_p[i-1], lista_cen[i]);
            lewe_np[i] = lewe_np[i-1];
        }
    }
    for(int i = n;i > 0;i--){
        if(lista_cen[i] % 2 == 1){
            prawe_np[i] = min(prawe_np[i+1], lista_cen[i]);
            prawe_p[i] = prawe_p[i+1];
        }
        else{
            prawe_p[i] = min(prawe_np[i+1], lista_cen[i]);
            prawe_np[i] = prawe_np[i+1];
        }
    }

    for(int i = 0;i < zapytania.size();i++){
        long long res = -1;
        if(wynik[zapytania[i]] % 2 == 1){
            res = wynik[zapytania[i]];
        }
        else{
            int it = zapytania[i];

            if(prawe_p[n-it+1] < (int)(1e9) and lewe_np[n-it] > 0){
                res = max(wynik[it]+lewe_np[n-it]-prawe_p[n-it+1], res);
            }

            if(prawe_np[n-it+1] < (int)(1e9) and lewe_p[n-it] > 0){
                res = max(wynik[it]+lewe_p[n-it]-prawe_np[n-it+1], res);
            }

        }
        cout << res << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    wczytaj();
    wykonaj();
}