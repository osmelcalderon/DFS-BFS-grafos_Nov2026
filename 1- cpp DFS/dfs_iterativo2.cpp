#include <bits/stdc++.h>
using namespace std;

using Mapa = vector<vector<char>>;
using Padres = vector<vector<pair<int, int>>>;
using Direccion = vector<vector<char>>;

// L, R, U, D
int coordX[4] = {0, 0, -1, 1};
int coordY[4] = {-1, 1, 0, 0};

char movimiento[4] = {'L', 'R', 'U', 'D'};

bool esValida(int fila, int columna, const Mapa &mapa) {
    return fila >= 0 && fila < mapa.size() &&
           columna >= 0 && columna < mapa[fila].size();
}

bool dfs(int fila, int columna,
         Mapa &mapa,
         Padres &padre,
         Direccion &direccion) {

    stack<pair<int, int>> pila;
    pila.push({fila, columna});

    mapa[fila][columna] = '#';

    while (!pila.empty()) {

        auto [filaActual, columnaActual] = pila.top();
        pila.pop();

        for (int i = 0; i < 4; i++) {

            int new_f = filaActual + coordX[i];
            int new_c = columnaActual + coordY[i];

            if (!esValida(new_f, new_c, mapa))
                continue;

            if (mapa[new_f][new_c] != '.' &&
                mapa[new_f][new_c] != 'B')
                continue;




            //Padres     → "¿de dónde vine?"
            // Guardamos de dónde venimos
            padre[new_f][new_c] = {filaActual, columnaActual}; //guarda un solo padre

            // Direccion  → "¿qué movimiento hice para llegar aquí?"
            // Guardamos el movimiento
            direccion[new_f][new_c] = movimiento[i]; // guardas un solo char

            // ¿Llegamos a B?
            if (mapa[new_f][new_c] == 'B') {
                return true;
            }

            // Marcamos visitado
            mapa[new_f][new_c] = '#';

            // Metemos en la pila
            pila.push({new_f, new_c});
        }
    }

    return false;
}

int main() {

    int n, m;
    cin >> n >> m;

    Mapa mapa(n, vector<char>(m));

    Padres padre(n, vector<pair<int, int>>(m));  //(m, {-1, -1}));

    Direccion direccion(n, vector<char>(m)); // (m, ' '));

    int inicioFila = 0;
    int inicioColumna = 0;

    int filaB = 0;
    int columnaB = 0;

    // Leer mapa
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            cin >> mapa[i][j];

            if (mapa[i][j] == 'A') {
                inicioFila = i;
                inicioColumna = j;
            }

            if (mapa[i][j] == 'B') {
                filaB = i;
                columnaB = j;
            }
        }
    }

    // DFS
    bool encontrado = dfs(
        inicioFila,
        inicioColumna,
        mapa,
        padre,
        direccion
    );

    if (!encontrado) {
        cout << "NO\n";
        return 0;
    }

    // Reconstruir camino desde B hasta A
    string camino;

    //solo se detiene cuando las dos coordenadas han llegado a A.
    //las coordenadas se retroalimentan del padre.  las coordenadas se van actualizando usando el padre.
    //"Estoy en esta casilla → busca quién es su padre → ahora muévete a esa casilla."
    while (filaB != inicioFila || columnaB != inicioColumna) { 
        camino += direccion[filaB][columnaB];
        filaB = padre[filaB][columnaB].first;
        columnaB = padre[filaB][columnaB].second;
    }


    // B -> A, por eso invertimos.... Como veniamos conformandola desde B hasta A, ahora tenemos q invertir la cadena de A hasta B
    reverse(camino.begin(), camino.end());

    cout << "YES\n";
    cout << camino.size() << '\n';
    cout << camino << '\n';
}


/*

DFS → encuentra un camino, no necesariamente el más corto.
BFS → encuentra el camino más corto en este tipo de mapa.
Tu LDDRRRUURRD de 11 pasos puede ser un camino válido, pero no es el óptimo.
El LDDRRRRRU de 9 pasos es el que BFS encontraría primero.


A . .
# # .
. . B

Coordenadas:
(0,0) (0,1) (0,2)
  A     .     .

(1,0) (1,1) (1,2)
  #     #     .

(2,0) (2,1) (2,2)
  .     .     B



//ponen en cada coordenada quien es su padre, y los demas los deja en 0
Padres padre = {
    { {0,0}, {0,0}, {0,1} },
    { {0,0}, {0,0}, {0,2} },
    { {0,0}, {0,0}, {1,2} }
};


Direccion direccion = {
    { '\0', 'R', 'R' },
    { '\0', '\0', 'D' },
    { '\0', '\0', 'D' }
};


DFS + backtracking → puedes encontrar el camino más corto.

Pero BFS es mucho más natural y eficiente para este problema, porque en un mapa donde cada movimiento cuesta 1, BFS encuentra el mínimo directamente.

Si quieres hacerlo específicamente con tu mismo código, tus Padres, Direccion, coordX, coordY y movimiento, podemos transformarlo a DFS + backtracking sin cambiar toda tu estructura.





recursivo backtraking
bool dfs(int f, int c) {
    if (mapa[f][c] == 'B')
        return true;

    mapa[f][c] = '#';

    for (int i = 0; i < 4; i++) {
        int nf = f + coordX[i];
        int nc = c + coordY[i];

        if (esValida(nf, nc, mapa) &&
            (mapa[nf][nc] == '.' || mapa[nf][nc] == 'B')) {

            padre[nf][nc] = {f, c};
            direccion[nf][nc] = movimiento[i];

            if (dfs(nf, nc))
                return true;
        }
    }

    return false;
}

*/