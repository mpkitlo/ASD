#include <bits/stdc++.h>
#define nl '\n'
#define pb push_back
#define st first
#define nd second

using namespace std;
using ll = long long;

const int N = 1e5+10;


const int M = sqrt(N)+10; 

int tab[M][N];

int wynik[N];

int n,q,a,l,d;

set <int> we;

void wczytaj(){
    cin >> n >> q;
}

void rob(int a,int l,int d){
    if(d < M){
        tab[d][a]++;
        if((a+((l-1)*d)+d) <= n)tab[d][a+(l-1)*d+d]--;
    }
}

void rob2(){

    for(int i:we){
        for(int j = 1;j<=n;j++){
            if(j-i >= 0){
                tab[i][j] += tab[i][j-i];
            }
            wynik[j] += tab[i][j];
            
        }
    }
}

void wywal(){
    for(int i = 1;i<=n;i++){
        cout << wynik[i] << " ";
    }
    cout << nl;
}

void wypisz(){
    while(q--){
        cin >> a >> l >> d;
        if(d >= M){
            for(int i = a;i<=(a+((l-1)*d));i+=d){
                wynik[i]++;     
            }
        }
        else{
            rob(a,l,d);
            we.insert(d);
        }
    }
    rob2();

}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    wczytaj();
    wypisz();
    wywal();
}