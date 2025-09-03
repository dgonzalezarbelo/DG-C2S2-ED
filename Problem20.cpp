#include <iostream>
#include <string>
#include <list>

bool resuelveCaso() {
	std::string cad;
	getline(std::cin, cad);
	if (!std::cin) return false;
	std::list<char> lista;
	auto it = lista.begin();
	for (char c : cad) {
		if (c == '+') {
			it = lista.end();
		}
		else if (c == '-') {
			it = lista.begin();
		}
		else if (c == '*') {
			if (it != lista.end()) {
				++it;
			}
		}
		else if (c == '3') {
			if (it != lista.end()) {
				it = lista.erase(it);
			}
		}
		else {
			it = lista.insert(it, c);
			++it;
		}
	}
	for (char c : lista) printf("%c", c);
	printf("\n");
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}