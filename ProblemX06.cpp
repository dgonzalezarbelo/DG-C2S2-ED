#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!cin) return false;
	unordered_map<string, vector<int>> m;
	for (int i = 1; i <= n; i++) {
		string aux;
		cin >> aux;
		m[aux].push_back(i);
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		int vez;
		string nombre;
		cin >> vez >> nombre;
		if (!m.count(nombre)) printf("NO JUEGA\n");
		else {
			if (m[nombre].size() < vez) printf("NO JUEGA\n");
			else printf("%d\n", m[nombre][vez - 1]);
		}
	}
	printf("---\n");
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}