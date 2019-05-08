#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define LL long long
#define INF 0x3f3f3f3f
#define MAXN 100005
#define MOD 998244353
using namespace std;
int main() {
    int n, m, i, j, k;
    int lenji[105][105];
    int lenou[105][105];
    scanf("%d %d", &n, &m);
    memset(lenji, INF, sizeof lenji);
    memset(lenou, INF, sizeof lenou);
    for (i = 1; i <= n; i++) {
        lenou[i][i] = 0;
    }
    for (i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        lenji[a][b] = 1;
        lenji[b][a] = 1;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= n; k++) {
                lenji[i][j] = min(lenji[i][j], lenji[i][k] + lenou[k][j]);
                lenji[i][j] = min(lenji[i][j], lenou[i][k] + lenji[k][j]);
                lenou[i][j] = min(lenou[i][j], lenou[i][k] + lenou[k][j]);
                lenou[i][j] = min(lenou[i][j], lenji[i][k] + lenji[k][j]);
                lenji[j][i] = lenji[i][j] = min(lenji[i][j], lenji[j][i]);
                lenou[j][i] = lenou[i][j] = min(lenou[i][j], lenou[j][i]);
            }
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= n; k++) {
                lenji[i][j] = min(lenji[i][j], lenji[i][k] + lenou[k][j]);
                lenji[i][j] = min(lenji[i][j], lenou[i][k] + lenji[k][j]);
                lenou[i][j] = min(lenou[i][j], lenou[i][k] + lenou[k][j]);
                lenou[i][j] = min(lenou[i][j], lenji[i][k] + lenji[k][j]);
                lenji[j][i] = lenji[i][j] = min(lenji[i][j], lenji[j][i]);
                lenou[j][i] = lenou[i][j] = min(lenou[i][j], lenou[j][i]);
            }
        }
    }
    int q;
    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        if (k % 2 == 1) {
            if (k >= lenji[a][b]) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        } else {
            if (k >= lenou[a][b]) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}