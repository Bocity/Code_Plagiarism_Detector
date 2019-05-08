#include <cctype>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
vector<int> road;
int kase = 0;
vector<int> d;

int findMin(vector<int> b) {
    unsigned long long int min = 1000000000;
    int K = -1;
    for (int k = 0; k < b.size(); ++k) {
        if (b[k] == 0) {
            continue;
        }
        if (b[k] < min) {
            min = b[k];
            K = k;
        }
    }

    if (road[K] == 0 || road[K] > kase + min) {
        road[K] = kase + min;
    }
    d.push_back(K);
    for (int i = 0; i < b.size(); ++i) {
        for (int j = 0; j < d.size(); j++) {
            if (i != d[j] && b[i] != 0 && road[i] > kase + b[i]) {
                road[i] = b[i] + kase;
            }
        }
    }
    kase += min; // 1 2

    return K;
}
int main() {
    vector<vector<int>> v, z;
    vector<int> dis, a;
    int q = 0;
    int n = 0, m = 0, k = 0, u = 0, V = 0, l = 0;
    cin >> n >> m >> k;
    vector<int> g;
    for (int i = 0; i < n; ++i) {
        g.push_back(0);
    }
    for (int x = 0; x < n; ++x) // 0
    {
        v.push_back(g);
    }

    for (int i = 0; i < n; ++i) {
        road.push_back(0);
    }

    for (int i = 0; i < k; ++i) // 0 1 2
    {
        cin >> q;
        a.push_back(q - 1); // a 宝藏城市 1 3 4
    }

    for (int j = 0; j < m; ++j) {
        cin >> u >> V >> l;
        v[u - 1][V - 1] = l;
        v[V - 1][u - 1] = l;
    }
    z = v;

    int h = 0;
    for (int i = 0; i < n; ++i) {
        d.push_back(0);
    }
    for (int i = 0; i < k; ++i) // 3
    {
        h = findMin(v[a[i]]); // 0
        for (int j = 0; j < n; ++j) {
            v[j][a[i]] = 0;
            v[j][h] = 0;
        }

        while (h != -1) {
            // int o=h;
            h = findMin(v[h]); // 0 3
            for (int j = 0; j < n; ++j) {
                v[j][h] = 0;
            }
        }
        long int Min = 1000000000;
        for (int p = 0; p < k; ++p) {
            if (road[a[p]] < Min && p != i) {
                Min = road[a[p]];
            }
        }

        for (int s = 0; s < n; ++s) {
            cout << "**" << road[s] << " ";
        }
        cout << endl;

        dis.push_back(Min);
        kase = 0;
        road.clear();
        for (int f = 0; f < n; ++f) {
            road.push_back(0);
        }
        d.clear();
        for (int i = 0; i < n; ++i) {
            d.push_back(0);
        }
        v = z;
    }
    for (int i = 0; i < k; ++i) {
        cout << dis[i] << " ";
    }

    return 0;
}