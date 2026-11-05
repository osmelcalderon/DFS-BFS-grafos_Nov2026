#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Matriz;
int dfs(int x, int y, Matriz& mapa) {   //x,y son coordenadas
    
    
    // Fuera de los límites(estado invalido)
    if (x < 0 || x >= mapa.size() || y < 0 || y >= mapa[x].size())
        return 0;

    // No pertenece al cráter o ya fue visitada(estado invalido)
    if (mapa[x][y] == 0)
        return 0;

    //marcar posiciones actuales como visitadas, pero antes guardar el valor
    int rocas = mapa[x][y];
           mapa[x][y] = 0;


    vector<int> coordX = {-1, 1, 0, 0};
    vector<int> coordY = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int new_x = x + coordX[i];
        int new_y = y + coordY[i];

        rocas += dfs(new_x, new_y,mapa);
        /*  ya esto lo ataje antes
        // Si está dentro de los límites
        if (new_x >= 0 && new_x < mapa.size() &&
            new_y >= 0 && new_y < mapa[new_x].size()) {

            rocas += dfs(new_x, new_y,mapa);
        }*/
    }

    return rocas;
}

int main() {
    int F, C;
    Matriz mapa;
    cin >> F >> C;

    mapa.resize(F, vector<int>(C));
    

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            cin >> mapa[i][j];
        }
    }

    int numeroCraters = 0;
    int mejorCraters = 0;
    int maxRocas = 0;

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {

            if (mapa[i][j] > 0 ) {

                numeroCraters++;

                int rocas = dfs(i, j, mapa);

                if (rocas > maxRocas) {
                    maxRocas = rocas;
                    mejorCraters = numeroCraters;
                }
            }
        }
    }

    cout << mejorCraters << " " << maxRocas << endl;

    return 0;
}