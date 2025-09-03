#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <cmath>

int buscar(std::vector <int> const& cad, int elem) {
	for (int i = 0; i < cad.size(); i++) {
		if (cad[i] == elem) return i;
	}
	return -1;
}

int solve(std::vector<std::queue<int>>& v, int k, std::vector<int> const& cad, int front) {
	if (k == 0) {
		if (v[k].empty() || v[k].front() > front) return -1;
		else {
			int mejor = v[k].front();
			v[k].pop();
			while (!v[k].empty() && v[k].front() < front) {
				mejor = v[k].front();
				v[k].pop();
			}
			return mejor;
		}
	}
	else {
		if (v[k].empty() || v[k].front() > front) return -1;
		else {
			int mejor = v[k].front();
			v[k].pop();
			while (!v[k].empty() && v[k].front() < front) {
				mejor = v[k].front();
				v[k].pop();
			}
			return solve(v, k - 1, cad, mejor);
		}
	}
}

bool resuelveCaso() {
	int num;
	int total, pos, aux;
	std::cin >> num >> total;
	if (!std::cin) return false;
	std::vector<int> cad(num);
	for (int& x : cad) std::cin >> x;
	std::vector <std::queue<int>> v(num);
	for (int i = 0; i < total; i++) {
		std::cin >> aux;
		pos = buscar(cad, aux);
		if (pos != -1) v[pos].push(i);
	}
	int mejor = INT_MAX;
	int posible;
	while (!v[v.size() - 1].empty()) {
		posible = solve(v, v.size() - 2, cad, v[v.size() - 1].front());
		if (posible != -1) {
			mejor = std::min(mejor, v[v.size() - 1].front() - posible + 1);
		}
		v[v.size() - 1].pop();
	}
	printf("%d\n", mejor);
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}