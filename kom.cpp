#include <bits/stdc++.h>

using namespace std;


const int base = (int)(1<<20);

int n, k, l, a;


vector <int> tab_pom;
pair <int, long long> tree[(base<<1)+5];
int tab[(int)(5e5)+5];
pair <int,long long> wynik = {0,0};

void wczytaj(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> l;

    for(int i = 1;i <= n;i++){
        cin >> a;
        tab_pom.push_back(a);
    }

    sort(tab_pom.begin(),tab_pom.end());

    for(int i = 0;i < tab_pom.size();i++){
        tab[i+1] = tab_pom[i];
    }

}

void insert(int v,  pair <int, long long> value){
    v += base;
    while(v > 0){
        if(tree[v].first == 0 || (tree[v].first > value.first && value.first
                                                                 != 0)){
            tree[v] = value;
        } else if(tree[v].first == value.first){
            tree[v].second += value.second;
            tree[v].second %= (int)(1e9)+7;
        }
        v /= 2;
    }
}

void mini(int v,int a,int b,int p,int k, pair <int, long long> &mini_p) {
    if(b<p || k<a) return;
    else if(p<=a && b<=k){
        if(mini_p.first == 0 || (mini_p.first > tree[v].first && tree[v].first
                                                                 != 0)){
            mini_p = tree[v];
        } else if(tree[v].first == mini_p.first){
            mini_p.second += tree[v].second;
            mini_p.second %= (int)(1e9)+7;
        }
    }
    else{
        int l = v<<1, r = (v<<1)+1, mid = (a+b)>>1;

        mini(l, a, mid, p, k, mini_p);
        mini(r, mid+1, b, p, k, mini_p);
    }
}

int po_d(int indeks){
    int q = indeks;
    int p = tab[indeks];
    while(tab[q] <= p + k and q <= n){
        insert(q, {1,1});
        q++;
    }
    if(k >= l){
        return q;
    }
    else {
        while (tab[q] < p + l) {
            q++;
        }
        return q;
    }
}

pair<int, long long> jechana(int &a, int &b, int &c, int &d, int indeks){
    pair <int, long long> para1 = {0,0};
    pair <int, long long> para2 = {0,0};

    while(tab[b] <= tab[indeks]-l){b++;}
    if(tab[b] > tab[indeks]-l){b--;}
    while(tab[a] < tab[indeks]-k){a++;}
    while(tab[d] <= min(tab[a-1], tab[indeks]-l)){d++;}
    if(tab[d] > min(tab[a-1], tab[indeks]-l)){d--;}
    while(tab[c] < tab[a-1]-k){c++;}

    mini(1, 0, base-1, a , b, para1);
    mini(1, 0, base-1, c , d, para2);

    if(para1.first == 0){return para2;}
    if(para2.first == 0){return para1;}
    if(para1.first == para2.first){return {para1.first, (para1.second+para2
                .second)%(int)(1e9+7)};}
    if(para1.first < para2.first){return para1;}
    if(para2.first < para1.first){return para2;}
}

void dodaj_do_wyn(int indeks){
    pair <int, long long> para = {0,0};
    int it = indeks;
    while(tab[it-1] >= tab[indeks]-k){it--;}
    mini(1, 0 , base-1, it, indeks, para);
    wynik = para;
}

void gen_dp(){
    int indeks = 1;
    int a = 1, b = 1, c = 1, d = 1;
    pair <int, long long> para = {0,0};
    indeks = po_d(indeks);

    while(indeks <= n) {
        para  = jechana(a, b, c , d, indeks);
        if(para.first != 0){insert(indeks, {para.first+1,para.second});}
        indeks++;
    }

}

int main(){
    wczytaj();
    gen_dp();
    dodaj_do_wyn(n);
    cout << wynik.first << " " << wynik.second << '\n';
}