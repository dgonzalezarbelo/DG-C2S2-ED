#include <iostream>
#include <vector>

const int MAX_ELEMS = 2000;

class Multiconjunto {
public:
	Multiconjunto() {
		this->num_elems = 0;
	}

	void anyadir(int elem) {	//O(n)
		if (num_elems < MAX_ELEMS) {
			int pos;
			if (buscar(elem, 0, num_elems, pos)) {
				elems[pos].multiplicidad++;
			}
			else {
				for (int i = num_elems; i > pos; i--) {
					elems[i] = elems[i - 1];
				}
				elems[pos] = { elem, 1 };
				num_elems++;
			}
		}
	}

	void eliminar(int elem) { //O(n)
		int pos;
		if (buscar(elem, 0, num_elems, pos)) {
			if (elems[pos].multiplicidad > 1) elems[pos].multiplicidad--;
			else {
				for (int i = pos; i < num_elems - 1; i++) {
					elems[i] = elems[i + 1];
				}
				num_elems--;
			}
		}
	}
	bool pertenece(int elem) const {	//O(log n)
		int pos;
		return buscar(elem, 0, num_elems, pos);
	}

	bool buscar(int elem, int ini, int fin, int & pos) const {	//O(log n)
		if (num_elems == 0) {
			pos = 0;
			return false;
		}
		if (ini >= fin - 1) {
			if (elems[ini].valor < elem) pos = ini + 1;
			else pos = ini;
			if (elems[ini].valor == elem) return true;
			else return false;
		}
		else {
			int m = (ini + fin - 1) / 2;
			if (elem <= elems[m].valor) return buscar(elem, ini, m + 1, pos);
			else return buscar(elem, m + 1, fin, pos);
		}
	}
private:
	struct Elem {
		int valor;
		int multiplicidad;
	};
	Elem elems[MAX_ELEMS];
	int num_elems;
};

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	int aux;
	Multiconjunto sol;
	std::vector <int> vsol(num), v(num);
	std::vector <char> salida(num);
	for (int i = 0; i < num; i++) {
		std::cin >> aux;
		sol.anyadir(aux);
		vsol[i] = aux;
	}
	for (int i = 0; i < num; i++) {
		std::cin >> aux;
		v[i] = aux;
	}
	for (int i = 0; i < num; i++) {
		if (v[i] == vsol[i]) {
			salida[i] = '#';
			sol.eliminar(v[i]);
		}
	}
	for (int i = 0; i < num; i++) {
		if (salida[i] != '#') {
			if (sol.pertenece(v[i])) {
				salida[i] = 'O';
				sol.eliminar(v[i]);
			} 
			else salida[i] = '.';
		}
	}
	for (int i = 0; i < num; i++) std::cout << salida[i];
	std::cout << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}