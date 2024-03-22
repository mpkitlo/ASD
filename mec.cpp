#include <bits/stdc++.h>

using namespace std;

int n,m;
int a;

string tab[400005];
set <string> secik;

void wczytaj(){
    cin >> n >> m;
    int it = 1;
    for(int i = 0;i < m;i++){
        for(int j  = 0;j < n;j++){
            cin >> a;
            if(j < n/2){
                tab[a] += char(it);
            }
            else{
                tab[a] += char(it+1);
            }
        }
        it += 2;
    }
}

void rob(){
    for(int i = 1;i <= n;i++){
        //cout << tab[i] << '\n';
        secik.insert(tab[i]);
    }
    if(secik.size() != n){
        cout << "NIE" << '\n';
    }
    else{
        if(tab[1].size() >= ceil(log2(n))){
            cout << "TAK" << '\n';
        }
        else{
            cout << "NIE" << '\n';
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    wczytaj();
    rob();
    //cout << "TAK" << '\n';
    return 0;
}