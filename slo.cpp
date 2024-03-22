#include <bits/stdc++.h>
#define nl '\n'
#define pb push_back
#define st first
#define nd second

using namespace std;
using ll = long long;
using pll = pair <ll,ll>;

const int N = 5e5+5;

ll n,x,y,waga,wynik;

struct str{
	int h;
	pll jump[20];
	vector <pll> somsiady;	
}G[N];

void wczytaj(){
	cin >> n;
	for(int i = 0;i<n-1;i++){
		cin >> x >> y >> waga;
		G[x].somsiady.pb({y,waga});
		G[y].somsiady.pb({x,waga});
	}
}

void LCA(int v,int waga,int stary,int wys){
	G[v].jump[0] = {stary,waga};
	G[v].h = wys;
	for(int i = 1;i<20;i++){
		G[v].jump[i].st = 
		G[G[v].jump[i-1].st].jump[i-1].st;
		
		G[v].jump[i].nd = 
		G[G[v].jump[i-1].st].jump[i-1].nd +
		G[v].jump[i-1].nd;
	}
	for(pll a:G[v].somsiady){
		if(a.st == stary){
			continue;
		}
		LCA(a.st,a.nd,v,wys+1);
	}
}

pll wyrownaj(ll v1,ll v2){
	if(G[v1].h == G[v2].h){
		return {v1,v2};
	}
	ll roznica = abs(G[v1].h-G[v2].h);
	if(G[v1].h < G[v2].h){swap(v1,v2);}	
	for(int i = 0;i<20;i++){
		if(roznica&(1<<i)){
			wynik += G[v1].jump[i].nd;
			v1 = G[v1].jump[i].st;		
		}
	}
	return {v1,v2};
}

ll oblicz(ll v1,ll v2){
	pll xd = wyrownaj(v1,v2);
	v1 = xd.st;
	v2 = xd.nd;
	if(v1 == v2){
		return wynik;
	}
	for(int i = 19;i>=0;i--){
		if(G[v1].jump[i].st != G[v2].jump[i].st){
			wynik += G[v1].jump[i].nd + G[v2].jump[i].nd;
			v1 = G[v1].jump[i].st;
			v2 = G[v2].jump[i].st;
		}
	}
	wynik += G[v1].jump[0].nd + G[v2].jump[0].nd;
	return wynik;
}

void wypisz(){
	while(1){
		cin >> x;
		if(x == -1){break;}
		else{
			cin >> y;
			wynik = 0;
			cout << oblicz(x,y) << nl;
		}
	}
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	wczytaj();
	LCA(1,0,0,1);
	wypisz();
}