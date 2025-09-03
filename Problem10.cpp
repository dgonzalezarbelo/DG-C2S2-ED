#include <iostream>
#include "list_linked_double.h"

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (!num) return false;
	ListLinkedDouble lista;
	int elem;
	while (num--) {
		std::cin >> elem;
		lista.push_back(elem);
	}
	lista.swap2by2();
	lista.display();
	std::cout << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}