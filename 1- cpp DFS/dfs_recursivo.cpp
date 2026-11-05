#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Matriz;

void dfs(int u, Matriz& grafo, vector<bool>& visitado) {

    visitado[u] = true;

    cout << u << " ";

    for (int v : grafo[u]) {

        if (!visitado[v]) {
            dfs(v, grafo, visitado);
        }
    }
}

int main() {

    int N, M;
    cin >> N >> M;

    Matriz grafo(N);

    for (int i = 0; i < M; i++) {

        int X, Y;
        cin >> X >> Y;

        grafo[X].push_back(Y);
    }

    vector<bool> visitado(N, false);

    dfs(0, grafo, visitado);

    return 0;
}
