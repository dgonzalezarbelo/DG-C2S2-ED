#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>

using namespace std;

bool resuelveCaso() {
	int personas, barcos;
	cin >> personas >> barcos;
	if (personas == 0 && barcos == 0) return false;
	unordered_map<string, int> mapaPersonas;
	unordered_map<string, list<string>> casillas;
	string persona;
	string pos;
	for (int i = 0; i < personas; i++) {
		cin >> persona;
		for (int j = 0; j < barcos; j++) {
			cin >> pos;
			casillas[pos].push_back(persona);
		}
		mapaPersonas[persona] = barcos;
	}
	int n;
	cin >> n;
	while (n--) {
		bool hundido = false;
		bool vencido = false;
		cin >> persona >> pos;
		auto it = casillas[pos].begin();
		while(it != casillas[pos].end()) {
			if (*it != persona) {
				if (--mapaPersonas[*it] == 0) vencido = true;
				hundido = true;
				it = casillas[pos].erase(it);
			}
			else {
				it++;
			}
		}
		if (vencido) cout << "VENCIDO\n";
		else if (hundido) cout << "HUNDIDO\n";
		else cout << "AGUA\n";
	}
	cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}