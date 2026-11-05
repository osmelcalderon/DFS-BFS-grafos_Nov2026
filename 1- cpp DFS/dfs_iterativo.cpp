#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;

using Mapa = vector<vector<char>>;
using Padres = vector<vector<pair<int, int>>>; //este es para guardar el recorrido hasta B
//typedef vector<vector<char>> Direccion;
using Direccion = vector<vector<char>>;


// Movimientos: izquierda, derecha, arriba, abajo
int coordX[4] = {0, 0, -1, 1};
int coordY[4] = {-1, 1, 0, 0};

//
char movimiento[4] = {'L', 'R', 'U', 'D'}; //el camino tal cual lo pide el ejercicio

bool esValida(int fila, int columna, const Mapa &mapa) {
    return fila >= 0 && fila < mapa.size() &&
           columna >= 0 && columna < mapa[fila].size();
}

bool dfs(int fila, int columna,  Mapa &mapa, Padres &padre, Direccion &direccion ) {
    stack<pair<int,int>> pila;
    pila.push({fila, columna});

    mapa[fila][columna] = '#';     // Marcamos el inicio como visitado
    while (!pila.empty()) {
        auto [filaActual, columnaActual] = pila.top(); // Sacamos la posición de arriba de la pila
        pila.pop();

        for (int i = 0; i < 4; i++) { // Revisamos los 4 movimientos

            int new_f = filaActual + coordX[i];
            int new_c = columnaActual+ coordY[i];

            // Si está dentro del mapa y es un espacio libre
            if (esValida(new_f, new_c, mapa) && (mapa[new_f][new_c] == '.' || mapa[new_f][new_c] == 'B')) {

                     
                    // Guardamos de dónde venimos
                    padre[new_f][new_c] = {filaActual, columnaActual};

                    // Guardamos el movimiento que hicimos
                    direccion[new_f][new_c] = movimiento[i];


                // Llegamos al vértice que estamos buscando B
                
                if (mapa[new_f][new_c] == 'B') {
                    return true;
                    /*
                    al encontrar B, necesito saber cómo llegue hasta B.
                    por tanto 
                    1ro guardar de dónde vino cada casilla y luego reconstruyo el camino char movimiento[4] = {'L', 'R', 'U', 'D'};
                        */

                }

                mapa[new_f][new_c] = '#'; // marcar como pared antes de meterlo
                pila.push({new_f, new_c});  // Metemos la nueva posición en la pila
            
            }
        }
    }
    return false;


}


int main() {

    int n, m;
   

    cin >> n >> m; // n= altura del mapa, m= ancho del mapa

    // Crear mapa de n x m
    Mapa mapa(n, vector<char>(m));
   
    
    /*este es para guardar el recorrido hasta B
    Por ejemplo, si llegamos a: (2,4) desde:  (2,3)
       guardamos: padre[2][4] = {2, 3}; // es decir 
    */
    Padres padre(n, vector<pair<int, int>>(m));
    //Direccion direccion; //(n, vector<char>(m)); // este es para guardar direccion pero con formato: LDDRRRRRU

    Direccion direccion(n, vector<char>(m)); // este es para guardar direccion pero con formato: LDDRRRRRU





    int inicioFila = 0;
    int inicioColumna = 0;

    int filaB = 0;
    int columnaB = 0;
    
    // Leer el mapa
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            cin >> mapa[i][j];  //entrada del mapa

            if (mapa[i][j] == 'A') {  //guardo la posicion A (inicio) 
                inicioFila = i;
                inicioColumna = j;
            }

            if (mapa[i][j] == 'B') {
                filaB = i;
                columnaB = j;
            }

        }
    }

    // Ejecutar DFS desde    ---  A (inicio) 
    //padre y direccion son variables q se pasan por referencia, para recoger valores del DFS
    bool encontrado = dfs(inicioFila, inicioColumna, mapa, padre, direccion);



/*
    if (!encontrado) {
        cout << "NO\n";
        return 0;
    }

           for(auto& x:direccion) cout<<string(x.begin(),x.end())<<'\n';



¿Qué significa cada parte?
f.begin() → apunta al primer elemento de f.
f.end() → apunta justo después del último elemento.
string(...) → construye un string usando todos los caracteres entre esos dos puntos.
*/

/*

    // Reconstruir camino desde B hasta A
    string camino;

    int filaActual = filaB;
    int columnaActual = columnaB;

    while (filaActual != inicioFila ||
           columnaActual != inicioColumna) {

        camino += direccion[filaActual][columnaActual];

        auto [filaPadre, columnaPadre] =
            padre[filaActual][columnaActual];

        filaActual = filaPadre;
        columnaActual = columnaPadre;
    }

    // Como reconstruimos B -> A, invertimos
    reverse(camino.begin(), camino.end());

    cout << "YES\n";
    cout << camino.size() << '\n';
    cout << camino << '\n';

*/




    return 0;
}


    //printf("%s %d %s", *b - A ? "NO" : "YES", k, a);

