#include <bits/stdc++.h>
#define nl '\n'
#define pb push_back
#define st first
#define nd second

using namespace std;
using ll = long long;
using pll = pair <ll,ll>;

const int N = (int)(5e5+5);

const int xd = (int)((-1)*(1e9));

int n,a,b,c,x,y;
ll wynik = xd;
ll wynik2 = xd;

struct node{
    ll wys;
    vector <pll> somsiady;
    pll jump[20];
}G[N];

void DFS(ll v,ll waga,ll stary,ll h){
    G[v].wys = h;
    G[v].jump[0] = {stary,waga};
    for(int i = 1;i<20;i++){
        G[v].jump[i].st = 
        G[G[v].jump[i-1].st].jump[i-1].st;
        G[v].jump[i].nd = 
        max(G[G[v].jump[i-1].st].jump[i-1].nd,G[v].jump[i-1].nd);
    }
    for(pll u:G[v].somsiady){
        if(u.st == stary){continue;}
        DFS(u.st,u.nd,v,h+1);
    }
}

void wczytaj(){
    cin >> n;
    for(int i = 1;i<n;i++){
        cin >> a >> b >> c;
        G[a].somsiady.pb({b,c});
        G[b].somsiady.pb({a,c});
    }
}

void wypisz(){
    for(int i = 1;i<=n;i++){
        cout << i << " " << G[i].wys << nl;
        for(int j = 0;j<20;j++){
            cout << G[i].jump[j].st << " " << G[i].jump[j].nd << nl;
        }
        cout << nl << nl;
    }
}

void robzadymke(int v1,int v2){
    //ll wynik2 = xd;
    if(v1 != v2){
        for(int i = 19;i>=0;i--){
            if(G[v1].jump[i].st != G[v2].jump[i].st){
                wynik = max(wynik,max(G[v1].jump[i].nd,G[v2].jump[i].nd));
                v1 = G[v1].jump[i].st;
                v2 = G[v2].jump[i].st;
            }
        }
        wynik = max(wynik,max(G[v1].jump[0].nd,G[v2].jump[0].nd));
    } 
}

void wyrownuj(int v1,int v2){
    if(G[v1].wys != G[v2].wys){
        int h1 = min(G[v1].wys,G[v2].wys);
        int h2 = max(G[v1].wys,G[v2].wys);
        if(G[v1].wys != h1){
            int pom = v1;
            v1 = v2;
            v2 = pom;
        }
        int roznica = h2-h1;
        for(int i = 0;i<20;i++){
            if(roznica&(1<<i)){
                wynik = max(wynik,G[v2].jump[i].nd);
                v2 = G[v2].jump[i].st;
            }
        }
        robzadymke(v1,v2);
    }
    else{
        if(v1 == v2){
            wynik = 0;
        }
        else{
            robzadymke(v1,v2);
        }
    }
    
    //maks = max(maks,(ll)0);
    //return {{v1,v2},maks};
}

void zapytania(){
    while(1){
        cin >> x;
        if(x == -1){break;}
        else{
            cin >> y;
            wynik = xd;
            wyrownuj(x,y);
            //robzadymke(wyrownuj(x,y).st.st,wyrownuj(x,y).st.nd);
            cout << wynik << nl;
        } 
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    wczytaj();
    DFS(1,0,0,1);
    //wypisz();
    zapytania();
}