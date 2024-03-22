#include <bits/stdc++.h>

using namespace std;

struct Node{
    int wart,lazy,czy_zep;
};

const int S = 1<<21;
int base = (1<<20);
Node drzewo[S+5];

void zepchnij(int node){
    if(drzewo[node].czy_zep == 1){
        for(int i:{(node<<1),(node<<1)+1}){
            drzewo[i].wart = drzewo[node].lazy/2;
            drzewo[i].lazy = drzewo[node].lazy/2;
            drzewo[i].czy_zep = 1;
        }
        drzewo[node].lazy = 0;
        drzewo[node].czy_zep = 0;
    }
}

void zamien_0(int v,int a,int b,int p,int k,int x){
    if(b<p || k<a)return;
    else if(p<=a && b<=k){
        drzewo[v].wart = 0;
        drzewo[v].lazy = 0;
        drzewo[v].czy_zep = 1;
    }
    else{
        int l = v<<1, r = (v<<1)+1, mid = (a+b)>>1;

        zepchnij(v);

        zamien_0(l,a,mid,p,k,x);
        zamien_0(r,mid+1,b,p,k,x);

        drzewo[v].wart = drzewo[l].wart + drzewo[r].wart;
    }
}

void zamien_1(int v,int a,int b,int p,int k,int x){
    if(b<p || k<a)return;
    else if(p<=a && b<=k){
        drzewo[v].wart = x * (b-a+1);
        drzewo[v].lazy = x * (b-a+1);
        drzewo[v].czy_zep = 1;
    }
    else{
        int l = v<<1, r = (v<<1)+1, mid = (a+b)>>1;

        zepchnij(v);

        zamien_1(l,a,mid,p,k,x);
        zamien_1(r,mid+1,b,p,k,x);

        drzewo[v].wart = drzewo[l].wart + drzewo[r].wart;
    }
}

long long suma(int v,int a,int b,int p,int k){
    if(b<p || k<a) return 0;
    else if(p<=a && b<=k) return drzewo[v].wart;
    else{
        int l = v<<1, r = (v<<1)+1, mid = (a+b)>>1;

        zepchnij(v);

        return suma(l, a, mid, p, k) + suma(r, mid+1, b, p, k);
    }
}
int main(){
    int n,m,a,b;
    char c;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0;i < m;i++){
        cin >> a >> b >> c;
        if(c == 'C'){
            zamien_0(1,0,base-1,a,b,-1);
            cout << suma(1,0,base-1,0,n) << '\n';
        }
        else{
            zamien_1(1,0,base-1,a,b,1);
            cout << suma(1,0,base-1,0,n) << '\n';
        }
    }
}