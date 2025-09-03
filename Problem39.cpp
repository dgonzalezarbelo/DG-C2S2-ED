#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

bool resuelveCaso() {
	int num;
	cin >> num;
	cin.get();
	if (!num) return false;
	map<string, vector<int>> m;
	string cad;
	string linea;
	vector<string> palabras;
	for (int i = 1; i <= num; i++) {
		getline(cin, linea);
		for (char c : linea) {
			if (c != ' ') cad += tolower(c);
			else {
				if (cad.size() > 2) {
					if (m.count(cad)) {
						if(m[cad][m[cad].size() - 1] < i) m[cad].push_back(i);
					}
					else {
						m[cad] = vector<int>(1, i);
						palabras.push_back(cad);
					}
				}
				cad = "";
			}
		}
		if (cad.size() > 2) {
			if (m.count(cad)) {
				if (m[cad][m[cad].size() - 1] < i) m[cad].push_back(i);
			}
			else {
				m[cad] = vector<int>(1, i);
				palabras.push_back(cad);
			}
		}
		cad = "";
	}
	sort(palabras.begin(), palabras.end());
	for (int i = 0; i < palabras.size(); i++) {
		cout << palabras[i] << ' ';
		cout << m[palabras[i]][0];
		for (int j = 1; j < m[palabras[i]].size(); j++) {
			cout << ' ' << m[palabras[i]][j];
		}
		cout << '\n';
	}
	cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}