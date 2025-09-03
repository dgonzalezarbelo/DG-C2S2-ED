/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Juan Diego Barrado Daganzo
  Estudiante 2: Daniel González Arbelo


  Dad una explicación de la solución y justificad su coste.
  Para cada elemento de la entrada se hacen accesos y modificaciones en un unordered_map, que son operaciones con coste amostizado constante.
  Por tanto, el bucle hasta que termina entrada tiene coste lineal, es decir, tiene coste O(m), siendo m el número de alumnos.
  Luego se utiliza un vector auxiliar para ordenar los elementos para la salida, por lo que el coste es O(nlogn), siendo n el número de deportes.
  Por tanto, el algoritmo entero tiene coste O(m + nlogn), siendo m el número de alumnos y n el número de deportes.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Implementa a continuación la función que resuelve un caso de
// prueba. Puedes utilizar otras funciones auxiliares, pon su
// implementación debajo de la etiqueta <answer>.
//@ <answer>


bool resuelveCaso() {

	string aux;
	string deporte;
	cin >> aux;
	if (!cin) return false;
	unordered_map<string, int> deportes;
	unordered_map<string, string> personas;
	while (aux != "_FIN_") {
		if ('A' <= aux[0] && aux[0] <= 'Z') {
			deportes[aux] = 0;
			deporte = aux;
		}
		else {
			if (personas.count(aux)) {
				if(personas[aux] != deporte){
					if(personas[aux] != "NULO")
						deportes[personas[aux]]--;
					personas[aux] = "NULO";
				}
			}
			else {
				personas[aux] = deporte;
				deportes[deporte]++;
			}
		}
		cin >> aux;
	}
	vector<pair<string, int>> v;
	for (auto it = deportes.begin(); it != deportes.end(); it++) {
		v.push_back({ it->first, it->second });
	}
	sort(v.begin(), v.end(), [](pair<string, int> p1, pair<string, int> p2) {
		return p1.second > p2.second || p1.second == p2.second && p1.first < p2.first;
		});
	for (auto x : v) {
		cout << x.first << ' ' << x.second << '\n';
	}
	cout << "---\n";
	return true;
}


//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {

	while (resuelveCaso());

	return 0;
}
