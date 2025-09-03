/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo puedes
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no ser� corregida.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  /*@ <answer>

   Introduce el nombre y apellidos de los/as componentes del grupo:

   Estudiante 1: Juan Diego Barrado Daganzo
   Estudiante 2: Daniel Gonz�lez Arbelo


   Dad una explicaci�n de la soluci�n y justificad su coste.

   La soluci�n es muy similar al problema de la linterna.
   Para cada elemento queremos buscar un elemento mayor a su izquierda.
   Para ello recorremos el vector de derecha a izquierda, guardando elementos en una pila.
   Al principio guardamos en la pila el primer elemento, porque no sabemos aun si hay un elemento mayor a la izquierda.
   Para cada elemento, comprobamos si es mayor que el top() de la pila, en cuyo caso le hemos encontrado a ese
   elemento otro mayor, as� que lo quitamos de la pila. Como este mismo elemento puede ser mayor que otros apilados,
   seguimos quitando elementos en la pila hasta que encontremos uno mayor que el actual o quede vac�a.
   Para cada elemento que sacamos de la pila guardamos en un vector (sol) la altura del primer elemento mayor.
   Finlamente, metemos el elemento actual en la pila, para buscarle m�s adelante uno mayor.

   El coste de la soluci�n es lineal, porque a pesar de haber un bucle dentro de otro, 
   para cada elemento se hacen solo dos operaciones como m�ximo: meterlo y sacarlo de la cola,
   luego el coste amortizado es lineal.

   @ </answer> */


#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

bool resuelveCaso() {
	int num;
	cin >> num;
	if (num == -1) return false;
	vector<int> v;
	while (num != -1) {
		v.push_back(num);
		cin >> num;
	}
	vector<int> sol(v.size(), -1);
	stack<pair<int, int>> pila;
	pila.push({v[v.size() - 1], v.size() - 1 });
	for (int i = v.size() - 2; i >= 0; i--) {
		if (v[i] <= pila.top().first) pila.push({ v[i], i });
		else {
			while (!pila.empty() && v[i] > pila.top().first) {
				sol[pila.top().second] = v[i];
				pila.pop();
			}
			pila.push({ v[i], i });
		}
	}
	for (int i = 0; i < v.size(); i++) {
		if (sol[i] == -1) printf("NO HAY\n");
		else printf("%d\n", sol[i]);
	}
	printf("---\n");
	return true;
}

//@ </answer>

// �No modificar nada debajo de esta l�nea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
