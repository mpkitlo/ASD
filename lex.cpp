#include <bits/stdc++.h>
#define st first
#define nd second

using namespace std;

typedef pair<long long, long long> hash_t;

constexpr size_t MAX_N = 300000;
constexpr hash_t q = make_pair(3919, 4051);

string s;
int n, m;

hash_t hashes[MAX_N];
hash_t pref[MAX_N + 1];

void init() {
   hashes[0] = make_pair(1, 1);

    for (size_t i = 1; i < MAX_N; ++i) {
       hashes[i].st = (hashes[i - 1].st * 5813) % q.st;
       hashes[i].nd = (hashes[i - 1].nd * 5101) % q.nd;
    }
}

hash_t get_hash(size_t b, size_t e) {
    hash_t result;

    if (pref[e].st < pref[b].st) {
        result.st = (((pref[e].st + q.st) - pref[b].st) *hashes[q.st - 1 - (b % (q.st - 1))].st) % q.st;
    } else {
        result.st = ((pref[e].st - pref[b].st) *hashes[q.st - 1 - (b % (q.st - 1))].st) % q.st;
    }

    if (pref[e].nd < pref[b].nd) {
        result.nd = (((pref[e].nd + q.nd) - pref[b].nd) *hashes[q.nd - 1 - (b % (q.nd - 1))].nd) % q.nd;
    } else {
        result.nd = ((pref[e].nd - pref[b].nd) *hashes[q.nd - 1 - (b % (q.nd - 1))].nd) % q.nd;
    }

    return result;
}

int compere(size_t a, size_t b, size_t c, size_t d) {
    size_t diff1 = b - a, diff2 = d - c;
    size_t begin = 0, end = diff2;

    if (diff1 < end) {
        end = diff1;
    }

    if (get_hash(a, a + end) == get_hash(c, c + end)) {

        if (diff1 > diff2) {

            return 1;
        }
        if (diff1 < diff2) {

            return -1;
        }

        return 0;
    }

    while (end - 1 != begin) {

        size_t it = (end + begin) / 2;

        if (get_hash(a, a + it) == get_hash(c, c + it))
            begin = it;
        else
            end = it;
    }

    char res1 = s[a + begin];
    char res2 = s[c + begin];

    if (res1 > res2) {
        return 1;
    } if (res1 < res2) {
        return -1;
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    init();
    cin >> n >> m >> s;

    pref[0] = make_pair(0, 0);

    for (size_t i = 1; i <= n; ++i) {
        pref[i] = make_pair((pref[i - 1].st + s[i - 1] * hashes[i - 1].st) % q.st,(pref[i - 1].nd + s[i - 1] * hashes[i - 1].nd) % q.nd);
    }

    while (m--) {
        size_t a, b, c, d;
        cin >> a >> b >> c >> d;

        a -= 1;
        c -= 1;

        int res = compere(a, b, c, d);

        if (res == 1) {
            cout << ">" << '\n';
        } else if (res == -1) {
            cout << "<" << '\n';
        } else {
            cout << "=" << '\n';
        }

    }
}