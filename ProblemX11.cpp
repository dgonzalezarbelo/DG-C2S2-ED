 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <list>

using namespace std;


class Spitter {
	using id = int;
	using hashtag = string;
public:

	Spitter() { }

	void nueva_publicacion(int id, const string& texto, const vector<string>& hashtags) {
		if (publicaciones.count(id))
			throw domain_error("Identificador duplicado");
		InfoPublicacion info;
		info.texto = texto;
		for (auto h : hashtags) {
			info.hashtags.insert(h);
			this->mapaHashtags[h]++;
		}
		info.itRecientes = recientes.insert(recientes.begin(), texto);
		publicaciones[id] = info;
	}

	void borrar_publicacion(int id) {
		if (publicaciones.count(id)) {
			InfoPublicacion& info = publicaciones.at(id);
			for (auto h : info.hashtags) {
				mapaHashtags[h]--;
			}
			recientes.erase(info.itRecientes);
			publicaciones.erase(id);
		}
	}

	vector<string> mas_recientes(int n) const {
		vector<string> v;
		if (n > 0) {
			for (auto r : recientes) {
				v.push_back(r);
				if (v.size() == n) break;
			}
		}
		return v;
	}

	vector<string> hashtags(int id) const {
		vector<string> v;
		auto it = publicaciones.find(id);
		if (it == publicaciones.end())
			throw domain_error("Publicacion no existente");
		InfoPublicacion info = it->second;
		for (auto h : info.hashtags) {
			v.push_back(h);
		}
		return v;
	}

	void anyadir_hashtag(int id, const string& hashtag) {
		auto it = publicaciones.find(id);
		if (it == publicaciones.end())
			throw domain_error("Publicacion no existente");
		InfoPublicacion& info = it->second;
		if(info.hashtags.insert(hashtag).second)
			mapaHashtags[hashtag]++;
	}

	int popularidad(const string& hashtag) const {
		if (mapaHashtags.count(hashtag)) return mapaHashtags.at(hashtag);
		else return 0;
	}

private:
	struct InfoPublicacion {
		InfoPublicacion() {};
		string texto;
		set<hashtag> hashtags;
		list<string>::iterator itRecientes;
	};
	unordered_map<id, InfoPublicacion> publicaciones;
	unordered_map<hashtag, int> mapaHashtags;
	list<string> recientes;
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
	string operacion;
	cin >> operacion;
	if (!cin) return false;
	Spitter spitter;
	while (operacion != "FIN") {
		try {
			if (operacion == "nueva_publicacion") {
				int id;
				string texto;
				cin >> id;
				cin.get();
				getline(cin, texto);
				string linea;
				getline(cin, linea); // se lee completamente una línea
				stringstream ss(linea); // para poder extraer de una a una las palabras
				string h;
				vector<string> hashtags;
				while (ss >> h) { // una vuelta por cada palabra de la línea
					hashtags.push_back(h);
				}
				spitter.nueva_publicacion(id, texto, hashtags);
			}
			else if (operacion == "mas_recientes") {
				int n;
				cin >> n;
				auto lista = spitter.mas_recientes(n);
				cout << "Las " << lista.size() << " publicaciones mas recientes:\n";
				for (auto t : lista)
					cout << "   " << t << '\n';
			}
			else if (operacion == "hashtags") {
				int id;
				cin >> id;
				auto lista = spitter.hashtags(id);
				for (auto h : lista) {
					cout << h << ' ';
				}
				cout << '\n';
			}
			else if (operacion == "popularidad") {
				string hashtag;
				cin >> hashtag;
				cout << spitter.popularidad(hashtag) << '\n';
			}
			else if (operacion == "borrar_publicacion") {
				int id;
				cin >> id;
				spitter.borrar_publicacion(id);
			}
			else if (operacion == "anyadir_hashtag") {
				int id;
				string hashtag;
				cin >> id >> hashtag;
				spitter.anyadir_hashtag(id, hashtag);
			}
		}
		catch (domain_error& e) {
			cout << "ERROR: " << e.what() << '\n';
		}
		cin >> operacion;
	}
	cout << "---\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

