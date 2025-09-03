#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <list>

template <typename T>
void mostrar_lista(std::list<T> const& lista, char inicio) {
    std::cout << inicio;
    for (auto it = lista.begin(); it != lista.end(); it++) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

template <typename T, typename U>
void leer_diccionario(std::map<T, U>& mapa) {
    std::string linea;
    getline(std::cin, linea); // se lee completamente una línea
    std::stringstream ss(linea); // para poder extraer de una a una las palabras
    T clave;
    U valor;
    while (ss >> clave) { // una vuelta por cada palabra de la línea
        ss >> valor;
        mapa[clave] = valor;
    }
}

void resuelveCaso() {
    std::map<std::string, int> original, nuevo;
    std::string linea;
    std::string palabra;
    int num;
    leer_diccionario(original);
    leer_diccionario(nuevo);
    bool cambio = false;
    auto it1 = original.begin();
    auto it2 = nuevo.begin();
    std::list<std::string> anyadidos, quitados, cambiados;
    while (it1 != original.end() && it2 != nuevo.end()) {
        if (it1->first == it2->first) {
            if (it1->second != it2->second) {
                cambiados.push_back(it1->first);
                cambio = true;
            }
            it1++;
            it2++;
        }
        else {
            if (it1->first < it2->first) {
                quitados.push_back(it1->first);
                ++it1;
            }
            else {
                anyadidos.push_back(it2->first);
                ++it2;
            }
            cambio = true;
        }
    }
    while (it1 != original.end()) {
        quitados.push_back(it1->first);
        cambio = true;
        ++it1;
    }
    while (it2 != nuevo.end()) {
        anyadidos.push_back(it2->first);
        cambio = true;
        ++it2;
    }
    if (!cambio) {
        std::cout << "Sin cambios\n";
    }
    else {
        if (!anyadidos.empty()) {
            mostrar_lista(anyadidos, '+');
        }
        if (!quitados.empty()) {
            mostrar_lista(quitados, '-');
        }
        if (!cambiados.empty()) {
            mostrar_lista(cambiados, '*');
        }
    }
    std::cout << "---\n";
}

int main() {
    int n;
    std::cin >> n;
    std::cin.get();
    while (n--) resuelveCaso();
    return 0;
}