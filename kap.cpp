#include <bits/stdc++.h>

#define MAX_N (2*(int)(1e5)+5)
#define max_ll (int)(1e9)+5
#define eb emplace_back

using namespace std;

using ll_pair = pair <long long, long long>;

long long calc(const ll_pair& lhs, const ll_pair& rhs){
    return min(abs(lhs.first - rhs.first),abs(lhs.second - rhs.second));
}

int n;
ll_pair position[MAX_N];
vector <long long> neighbours[MAX_N];
long long dist[MAX_N];
set <ll_pair> q;

void wczytaj(){
    ios_base::sync_with_stdio(0);
    cin >> n;

    for(int i = 0;i < n;i++) {
        int a, b;
        cin >> a >> b;
        position[i] = make_pair(a, b);
        dist[i] = max_ll;
    }
    dist[0] = 0;
}

int main() {

    wczytaj();

    vector<ll_pair> x, y;

    for(int i = 0;i < n;i++) {
        x.eb(make_pair(position[i].first, i));
        y.eb(make_pair(position[i].second, i));
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    for(int i = 0;i < n;i++) {
        if (i != 0) {
            neighbours[x[i].second].eb(x[i - 1].second);
            neighbours[y[i].second].eb(y[i - 1].second);
        }
        if (i != n - 1) {
            neighbours[x[i].second].eb(x[i + 1].second);
            neighbours[y[i].second].eb(y[i + 1].second);
        }
    }


    q.insert(make_pair(dist[0], 0));

    while (!q.empty()) {

        ll_pair current = *q.begin();
        q.erase(q.begin());
        auto cid = current.second;

        if (cid == n - 1){
            break;
        } else {
            for (auto x: neighbours[cid]) {
                auto tmp = dist[cid] + calc(position[cid], position[x]);
                if (dist[x] == max_ll) {
                    dist[x] = tmp;
                    q.insert(make_pair(dist[x], x));
                }
                else if (tmp < dist[x]) {
                    set<ll_pair>::iterator ix = q.find(make_pair(dist[x], x));
                    q.erase(ix);
                    dist[x] = tmp;
                    q.insert(make_pair(dist[x], x));
                }
            }
            dist[cid] = 0;
        }
    }

    cout << dist[n - 1] << '\n';
}