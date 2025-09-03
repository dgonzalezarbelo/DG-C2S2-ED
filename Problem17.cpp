#include <iostream>
#include <stack>
#include <vector>

bool solve(std::vector<int> const& v) {
	std::stack <int> pila;
	pila.push(v[v.size() - 1]);
	int mejorMediano = -1;
	for (int i = v.size() - 2; i >= 0; i--) {
		if (v[i] < mejorMediano) return true;
		else {
			if (!pila.empty() && v[i] > pila.top()) {
				while (!pila.empty() && v[i] > pila.top()) {
					mejorMediano = pila.top();
					pila.pop();
				}
				pila.push(v[i]);
			}
			else if(v[i] < pila.top()) {
				pila.push(v[i]);
			}
		}
	}
	return false;
}

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (!std::cin) return false;
	std::vector<int> v(num);
	for (int& x : v) std::cin >> x;
	if (solve(v)) printf("ELEGIR OTRA\n");
	else printf("SIEMPRE PREMIO\n");
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}