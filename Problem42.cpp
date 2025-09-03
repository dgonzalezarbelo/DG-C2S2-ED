#include <iostream>
#include <map>
using namespace std;

void resuelveCaso() {
	int capitulos;
	std::cin >> capitulos;
	std::map<int, int> m;
	int actual = 0, max = 0, aux, primero = -1;
	for (int i = 0; i < capitulos; i++) {
		std::cin >> aux;
		if (!m.count(aux)) {
			actual++;
		}
		else {
			if (m[aux] < primero) {
				actual++;
			}
			else {
				actual = i - m[aux];
				primero = m[aux] + 1;
			}
		}
		m[aux] = i;
		if (actual > max) max = actual;
	}
	std::cout << max << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int series;
	std::cin >> series;
	while(series--) resuelveCaso();
	return 0;
}