#include <iostream>
#include "list_linked_single.h"

void resuelveCaso() {
	ListLinkedSingle list;
	int num;
	std::cin >> num;
	while (num != 0) {
		list.push_back(num);
		std::cin >> num;
	}
	list.duplicate();
	list.display();
	std::cout << '\n';
}

int main() {
	int num;
	std::cin >> num;
	for (int i = 0; i < num; i++) resuelveCaso();
	return 0;
}