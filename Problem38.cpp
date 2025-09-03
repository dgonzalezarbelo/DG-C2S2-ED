#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool resuelveCaso() {
	int n;
	cin >> n;
	cin.get();
	if (!n) return false;
	vector<string> alumnos;
	map<string, int> m;
	string nombre, calificacion;
	while (n--) {
		getline(cin, nombre);
		getline(cin, calificacion);
		if (!m.count(nombre)) {
			alumnos.push_back(nombre);
			if (calificacion == "CORRECTO") {
				m[nombre] = 1;
			}
			else m[nombre] = -1;
		}
		else {
			if (calificacion == "CORRECTO") {
				m[nombre]++;
			}
			else m[nombre]--;
		}
	}
	sort(alumnos.begin(), alumnos.end());
	for (string s : alumnos) {
		if (m[s] != 0) {
			cout << s << ", " << m[s] << '\n';
		}
	}
	cout << "---\n";
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	while (resuelveCaso());
	return 0;
}