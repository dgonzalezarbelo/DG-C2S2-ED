#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void resuelveCaso() {
	string equipo, problema, veredicto;
	int tiempo;
	unordered_map<string, unordered_map<string, pair<bool, int>>> problemas;
	unordered_map<string, pair<int, int>> equipos; // Equipo -> Tiempo, conseguidos
	cin >> equipo;
	while (equipo != "FIN") {
		cin >> problema >> tiempo >> veredicto;
		if (!equipos.count(equipo)) equipos[equipo] = {0, 0};
		if (veredicto == "AC") {
			if (!problemas[problema].count(equipo)) {
				problemas[problema].insert({ equipo, {true, 0} });
				equipos[equipo].first += problemas[problema][equipo].second + tiempo;
				equipos[equipo].second++;
			}
			else {
				if (!problemas[problema][equipo].first) {
					problemas[problema][equipo].first = true;
					equipos[equipo].first += problemas[problema][equipo].second + tiempo;
					equipos[equipo].second++;
				}
			}
		}
		else {
			if (!problemas[problema].count(equipo)) {
				problemas[problema].insert({ equipo, {false, 20} });
			}
			else {
				problemas[problema][equipo].second += 20;
			}
		}
		cin >> equipo;
	}
	vector<tuple<string, int, int>> v;
	auto it = equipos.begin();
	while (it != equipos.end()) {
		v.push_back({ it->first, it->second.first, it->second.second });
		it++;
	}
	sort(v.begin(), v.end(), [](tuple<string, int, int> const& t1, tuple<string, int, int> const& t2) {
		return (get<2>(t1) > get<2>(t2) || get<2>(t1) == get<2>(t2) && get<1>(t1) < get<1>(t2)
			|| get<2>(t1) == get<2>(t2) && get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2));
		});
	for (int i = 0; i < v.size(); i++) {
		cout << get<0>(v[i]) << ' ' << get<2>(v[i]) << ' ' << get<1>(v[i]) << '\n';
	}
	cout << "---\n";
}

int main() {
	int n;
	cin >> n;
	while (n--) resuelveCaso();
	return 0;
}