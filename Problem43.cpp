#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!n) return false;
	bool bingo = false;
	map<int, vector<string>> m;
	map<string, int> cantidades;
	for (int i = 0; i < n; i++) {
		string nombre;
		cin >> nombre;
		int aux, total = 0;
		cin >> aux;
		while (aux) {
			m[aux].push_back(nombre);
			total++;
			cin >> aux;
		}
		cantidades[nombre] = total;
	}
	set<int> cantados;
	int bola;
	while (!bingo) {
		cin >> bola;
		if (!cantados.count(bola)) {
			cantados.insert(bola);
			for (string nombre : m[bola]) {
				if (--cantidades[nombre] == 0) bingo = true;
			}
		}
	}
	auto it = cantidades.begin();
	bool primero = true;
	while (it != cantidades.end()) {
		if (it->second == 0) {
			if (primero) primero = false;
			else cout << ' ';
			cout << it->first;
		}
		++it;
	}
	cout << '\n';
	return true;
}

int main() {
	while (resuelveCaso());
	return 0; 
}