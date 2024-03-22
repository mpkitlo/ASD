#include <bits/stdc++.h>
#define pb push_back
#define st first
#define nd second
#define nl '\n'

using namespace std;

int n, q, a_i, v, x, it = 1;
char znak;

const int MAX_N = (int)1e5*2+5;
const int base = (int)(1<<20);

map<long long, int> tree[(base<<1)+5];

vector<int> G[MAX_N];
int rev[MAX_N];

long long color[MAX_N];
bool vis[MAX_N];
pair<int, int> przedzialy[MAX_N];

void dfs(int v){
    vis[v] = true;
    przedzialy[v].st = it++;

    for(auto i: G[v]){
        if(!vis[i]){
            dfs(i);
        }
    }
}

void dfs2(int v){
    vis[v] = true;

    for(auto i: G[v]){
        if(!vis[i]){
            dfs2(i);
        }
    }

    if(G[v].empty()){
        przedzialy[v].nd = przedzialy[v].st;
    } else {
        przedzialy[v].nd = przedzialy[G[v][G[v].size()-1]].nd;
    }
}

void insert(int node, long long cur_color, long long prev_color){

    node += base;

    if(prev_color != -1){
        tree[node].erase(prev_color);
    }
    tree[node][cur_color]++;
    node /= 2;

    while(node > 0){
        if(prev_color != -1){
            if(tree[node][prev_color] == 1){
                tree[node].erase(prev_color);
            } else {
                tree[node][prev_color]--;
            }
        }
        tree[node][cur_color]++;
        node /= 2;
    }
}


void czy(int node, int a, int b, int p, int k, map<long long, int> &spr){
    if(b<p || k<a) return;
    else if(p<=a && b<=k){
        for(auto i: tree[node]){
            spr[i.st] += i.nd;
        }
    } else {
        int l = node<<1, r = (node<<1)+1, mid = (a+b)>>1;

        czy(l, a, mid, p, k, spr);
        czy(r, mid+1, b, p , k, spr);
    }
}


void wczytaj(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;

    for(int i = 1;i < n;i++){
        cin >> a_i;
        G[a_i].pb(i+1);
        rev[i+1] = (a_i);
    }

    dfs(1);
    for(int i = 0;i < MAX_N;i++){
        vis[i] = false;
    }
    dfs2(1);

    for(int i = 1;i <= n;i++){
        cin >> color[i];
        insert(przedzialy[i].st, color[i], -1);
    }


    for(int i = 0;i < q;i++){
        cin >> znak;
        if(znak =='z'){
            cin >> v >> x;
            insert(przedzialy[v].st, x, color[v]);
            color[v] = x;
        } else {
            cin >> v;
            map<long long, int> spr;
            czy(1, 0, base-1, przedzialy[v].st, przedzialy[v].nd, spr);
            if(spr.size() > 2){
                cout << "NIE" << nl;
            } else if(spr.size() == 1){
                cout << "TAK" << nl;
            } else if(spr.size() == 2){
                string wynik = "NIE";
                for(auto i: spr){
                    if(i.nd == 1){
                        wynik = "TAK";
                    }
                }
                cout << wynik << nl;
            }
        }
    }
}

int main(){
    wczytaj();
}