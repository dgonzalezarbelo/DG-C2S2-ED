#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;

class Sistema {
public:

	Sistema() {};

	void nuevoLibro(string x, int n) {
		libros[x].cantidad += n;
	}

	void comprar(string x) {
		if (!libros.count(x))
			throw invalid_argument("Libro no existente");
		Libro& libro = libros.at(x);
		if (libro.cantidad == 0)
			throw out_of_range("No hay ejemplares");
		libro.cantidad--;
		if (libro.ventas > 0) {
			list<string>& lista = ventas[libro.ventas];
			lista.erase(libro.itVentas);
			if (lista.empty())
				ventas.erase(libro.ventas);
		}
		libro.ventas++;
		list<string>& lista = ventas[libro.ventas];
		lista.push_front(x);
		libro.itVentas = lista.begin();
	}

	bool estaLibro(string x) {
		return libros.count(x);
	}

	void elimLibro(string x) {
		if (libros.count(x)) {
			Libro libro = libros.at(x);
			if (libro.ventas > 0) {
				list<string>& lista = ventas[libro.ventas];
				lista.erase(libro.itVentas);
				if (lista.empty())
					ventas.erase(libro.ventas);
			}
			libros.erase(x);
		}
	}

	int numEjemplares(string x) {
		if (!libros.count(x))
			throw invalid_argument("Libro no existente");
		return libros[x].cantidad;
	}

	list<string> top10() {
		auto itVentas = ventas.begin();
		int i = 0;
		list<string> res;
		while (i < 10 && itVentas != ventas.end()) {
			list<string>& lista = itVentas->second;
			auto itLista = lista.begin();
			while (i < 10 && itLista != lista.end()) {
				res.push_back(*itLista);
				itLista++;
				i++;
			}
			itVentas++;
		}
		return res;
	}

private:
	struct Libro {
		Libro() {};
		Libro(int cantidad) : cantidad(cantidad), ventas(0) {};
		int cantidad = 0;
		int ventas = 0;
		list<string>::iterator itVentas;
	};
	unordered_map<string, Libro> libros;
	map<int, list<string>, greater<int>> ventas;
};

bool resuelveCaso() {
	int numOp;

	cin >> numOp;
	if (!cin) return false;

	Sistema amazon;

	string operacion, titulo;

	for (int i = 0; i < numOp; ++i) {
		cin >> operacion;
		cin.ignore(1); // saltar blanco
		if (operacion == "nuevoLibro") {
			int unidades;
			cin >> unidades;
			cin.ignore(1);
			getline(cin, titulo);
			amazon.nuevoLibro(titulo, unidades);
		}
		else if (operacion == "comprar") {
			getline(cin, titulo);
			try {
				amazon.comprar(titulo);
			}
			catch (out_of_range const& e) {
				cout << e.what() << '\n';
			}
			catch (invalid_argument const& e) {
				cout << e.what() << '\n';
			}
		}
		else if (operacion == "estaLibro") {
			getline(cin, titulo);
			if (amazon.estaLibro(titulo)) {
				cout << "El libro " << titulo << " esta en el sistema\n";
			}
			else {
				cout << "No existe el libro " << titulo << " en el sistema\n";
			}
		}
		else if (operacion == "elimLibro") {
			getline(cin, titulo);
			amazon.elimLibro(titulo);
		}
		else if (operacion == "numEjemplares") {
			getline(cin, titulo);
			if (amazon.estaLibro(titulo)) {
				cout << "Existen " << amazon.numEjemplares(titulo) << " ejemplares del libro " << titulo << '\n';
			}
			else {
				cout << "No existe el libro " << titulo << " en el sistema\n";
			}
		}
		else if (operacion == "top10") {
			cout << "TOP10\n";
			list<string> top10 = amazon.top10();
			auto it = top10.begin();
			while (it != top10.end()) {
				cout << "    " << *it << '\n';
				it++;
			}
		}
	}
	// fin del caso
	cout << "---\n";
	return true;

}

int main() {
	while (resuelveCaso());
	return 0;
}