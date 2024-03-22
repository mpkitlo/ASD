#include <bits/stdc++.h>

using namespace std;

const long long tree_size = (long long)(1<<16);
long long base = (long long)(1<<15);
long long n, k;
long long tab[20005];
long long tree[tree_size+100][15];

void wczytaj() {
    cin >> n >> k;
    for (long long i = 0; i < n; i++) {
        cin >> tab[i];
    }
}

void add(long long liczba, long long ile, long long inv) {
    liczba += base-1;
    while(liczba != 0){
        tree[liczba][inv] += ile;
        tree[liczba][inv] %= (long long)(1e9);
        liczba /= 2;
    }
}

void init() {
    for (long long i = 0; i < n; i++)
        tree[i + base][1] = 1;
    for (long long i = base - 1; i > 0; i--)
        tree[i][1] = tree[2 * i][1] + tree[2 * i + 1][1];
}

long long suma(long long a, long long b, long long ktore) {
    a += base-1;
    b += base+1;
    long long wynik = 0;

    while (a / 2 != b / 2) {
        if (a % 2 == 0) {
            wynik += tree[a + 1][ktore];
        }
        if (b % 2 == 1) {
            wynik += tree[b - 1][ktore];
        }
        a /= 2;
        b /= 2;
    }
    return wynik;
}

void dp(){
    long long ans = 0;
    long long v = 0;
    for(long long i = 0;i < n;i++){
        add(tab[i], 1, 1);
        for(long long j = 2;j <= k;j++){
            v = suma(tab[i], n, j-1);
            add(tab[i], v, j);
        }

        ans = (ans + v) % (long long)(1e9);
    }
    cout << ans << '\n';
}

void wypisz(long long ktore){
    long long jd = 1;
    while(jd < n){
        jd *= 2;
    }
    long long dzielnik = 1;
    while(jd >= 1){
        for(long long i = 0;i < jd;i++){
            cout << tree[i + (base/dzielnik)][ktore] << " ";
        }
        cout << '\n';
        jd /= 2;
        dzielnik *= 2;
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    wczytaj();
    dp();
    return 0;
}