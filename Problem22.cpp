/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Daniel González Arbelo
  Estudiante 2:


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

/*
El algoritmo comprueba secuencialmente que para cada par de filas (i, i + 1), la fila i + 1 es igual a la fila i excepto que
desplazada. Esto significa que el primer elemento de la fila i es el segundo elemento de la i + 1, el segundo elemento
de la fila i es el tercer elemento de la fila i + 1, etc. y así con todos los elementos de la fila i excepto el ultimo.
Para ello recorremos filas desde la primera a la ultima comprobando precisamente que el elemento j de la fila i es igual 
al elemento j + 1 de la fila i + 1. Si en algún punto del recorrido no se da la coincidencia el algoritmo termina.

Como cada elemento de la matriz se comprueba solo dos veces, el coste del algoritmo es lineal con respecto al tamaño de la matriz,
es decir, si la matriz es de tamaño mxn, el coste pertenece a O(mxn)
*/

bool es_toeplitz(const list<list<int>>& matriz) {
    auto itLista2 = matriz.begin();
    for (int i = 1; i < matriz.size(); i++) {
        auto itLista1 = itLista2++;
        auto it1 = itLista1->begin();
        auto it2 = itLista2->begin();
        it2++;
        while (it2 != itLista2->end()) {
            if (*it1 != *it2) return false;
            it1++;
            it2++;
        }
    }
    return true;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

list<int> leer_fila() {
    list<int> result;
    int num;
    cin >> num;
    while (num != 0) {
        result.push_back(num);
        cin >> num;
    }
    return result;
}

list<list<int>> leer_matriz() {
    list<list<int>> result;
    list<int> fila_actual = leer_fila();
    while (!fila_actual.empty()) {
        result.push_back(fila_actual);
        fila_actual = leer_fila();
    }

    return result;
}

bool resuelveCaso() {
    list<list<int>> m = leer_matriz();
    if (m.empty()) return false;

    if (es_toeplitz(m)) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}
