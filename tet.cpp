#include <bits/stdc++.h>
#define nl '\n'
#define pb push_back
#define st first
#define nd second

using namespace std;
using ll = long long;

const int N = (1<<30)-1;

struct node{
    ll val = 0,lazy = 0;
    node* l = nullptr;
    node* p = nullptr;
    node* L(){
        if(l == nullptr){
            l = new node;
        }
        return l;
    }
    node* P(){
        if(p == nullptr){
            p = new node;
        }
        return p;
    }
    void ustaw(ll wart){
        val = max(val,wart);
        lazy = max(lazy,wart);
    }
    void zepchnij(){
        if(lazy){
            L()->ustaw(lazy);
            P()->ustaw(lazy);
        }
        lazy = 0;
    }
};

node* korzen = new node;
int lewy,prawy,d,n,a,b,h;
ll maks;

void maksowanie(node* v,int L,int P){
    if(L > prawy or P < lewy){return;}
    if(L >= lewy and P <= prawy){
        maks = max(maks,v->val);
        return;
    }
    v->zepchnij();
    int S = (L+P)/2;
    maksowanie(v->L(),L,S);
    maksowanie(v->P(),S+1,P);
}

void powieksz(node* v,int L,int P){
    if(L > prawy or P < lewy){return;}
    if(L >= lewy and P <= prawy){
        v->ustaw(maks);
        return;
    }
    int S = (L+P)/2;
    powieksz(v->L(),L,S);
    powieksz(v->P(),S+1,P);
    v->val = max(v->L()->val,v->P()->val);
}

void wczytaj(){
    cin >> d >> n;
}

void rob(){
    while(n--){
        cin >> a >> b >> h;
        lewy = a;
        prawy = b-1;
        maks = 0;
        maksowanie(korzen,0,N);
        maks += h;
        powieksz(korzen,0,N);
    }
    cout << korzen->val << nl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    wczytaj();
    rob();
}