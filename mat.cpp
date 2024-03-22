#include <bits/stdc++.h>

using namespace std;

string napis;
int alfabet[100];

void wczytaj(){
    cin >> napis;
}

void wyczysc(){
    for(int i = 0;i<100;i++){
        alfabet[i] = 0;
    }
}

bool czy_szablon(int dl_szablonu){
    wyczysc();
    int dl_badana = napis.size() + 1 - dl_szablonu;
    int liczba_liter = 0;
    for(int i = 0;i < napis.size();i++){
        if(napis[i] != '*'){
            alfabet[napis[i]]++;
            if(alfabet[napis[i]] == 1){
                liczba_liter++;
            }
        }
        if(i >= dl_badana){
            if(napis[i - dl_badana] != '*'){
                alfabet[napis[i -dl_badana]]--;
                if(alfabet[napis[i -dl_badana]] == 0){
                    liczba_liter--;
                }
            }
        }
        if(liczba_liter > 1){
            return false;
        }
    }
    return true;
}

int bin_szukanie(){

    int wynik = 0;
    int l = 1;
    int p = napis.size();
    int sr;

    while(l <= p){
        sr = (l+p)/2;
        if(czy_szablon(sr)){
            //cout << czy_szablon(5) << '\n';
            wynik = sr;
            p = sr - 1;
        }
        else{
            l = sr + 1;
        }
    }
    return wynik;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    wczytaj();
    cout << bin_szukanie() << '\n';
}