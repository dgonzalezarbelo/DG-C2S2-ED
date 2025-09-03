#include <iostream>
#include <queue>
#include <stack>
#include <string>

bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
		|| c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void resolver(std::queue<char> & q) {
	//Para deshacer el cambio de X' a X'' ponemos el primer elemento de otra cola y el segundo en una pila, el tercero en la otra cola y el cuarto en la pila...
	//Asi, cuando la cola original este vacia recuperamos todos los elementos de la otra cola (preservando el orden) y luego los de la pila (orden invertido)
	std::queue<char> qAux;
	std::stack<char> sAux;
	int i = 0;
	while (!q.empty()) {
		if (i % 2 == 0) {
			qAux.push(q.front());
			q.pop();
		}
		else {
			sAux.push(q.front());
			q.pop();
		}
		i++;
	}
	while (!qAux.empty()) {
		q.push(qAux.front());
		qAux.pop();
	}
	while (!sAux.empty()) {
		q.push(sAux.top());
		sAux.pop();
	}
	//Para deshacer el cambio de X a X' recorremos la cola de forma que si el primer elemento es una vocal la pasamos al final de una cola auxiliar (usaremos la misma de antes)
	//En caso contrario, pasamos todos los caracteres a una pila auxiliar (usaremos la misma de antes) hasta llegar a la siguiente vocal.
	//Tras esto, pasamos todos los elementos de la pila de vuelta a la cola auxiliar, de forma que ahora el orden es el inverso
	//Finalmente, asignamos a la cola original al auxiliar
	while (!q.empty()) {
		if (isVowel(q.front())) {
			while (!sAux.empty()) {
				qAux.push(sAux.top());
				sAux.pop();
			}
			qAux.push(q.front());
			q.pop();
		}
		else {
			sAux.push(q.front());
			q.pop();
		}
	}
	while (!sAux.empty()) {
		qAux.push(sAux.top());
		sAux.pop();
	}
	q = qAux;
}

bool resuelveCaso() {
	std::string cad;
	getline(std::cin, cad);
	if (!std::cin) return false;
	std::queue<char> q;
	for (int i = 0; i < cad.size(); i++) {
		q.push(cad[i]);
	}
	resolver(q);
	while (!q.empty()) {
		printf("%c", q.front());
		q.pop();
	}
	printf("\n");
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}