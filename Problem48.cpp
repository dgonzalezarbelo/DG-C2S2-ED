#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <list>
using namespace std;

class CarnetPuntos {
public:
    CarnetPuntos() {
        this->cuantos_por_puntos.assign(16, 0);
        this->cuales_por_puntos.assign(16, list<std::string>());
    };

    void nuevo(std::string dni) {
        if (this->conductores.count(dni))
            throw std::domain_error("Conductor duplicado");
        this->conductores[dni].first = 15;
        this->cuantos_por_puntos[15]++;
        this->cuales_por_puntos[15].push_front(dni);
        this->conductores[dni].second = this->cuales_por_puntos[15].begin();
    }

    void quitar(std::string dni, int puntos) {
        if (!this->conductores.count(dni))
            throw std::domain_error("Conductor inexistente");
        int anterioresPuntos = this->conductores[dni].first;
        int nuevosPuntos = std::max(anterioresPuntos - puntos, 0);
        this->conductores[dni].first = nuevosPuntos;
        if (anterioresPuntos != nuevosPuntos) {
            this->cuantos_por_puntos[anterioresPuntos]--;
            this->cuantos_por_puntos[nuevosPuntos]++;
            this->cuales_por_puntos[anterioresPuntos].erase(this->conductores[dni].second);
            this->cuales_por_puntos[nuevosPuntos].push_front(dni);
            this->conductores[dni].second = this->cuales_por_puntos[nuevosPuntos].begin();
        }
    }

    void recuperar(std::string dni, int puntos) {
        if (!this->conductores.count(dni))
            throw std::domain_error("Conductor inexistente");
        int anterioresPuntos = this->conductores[dni].first;
        int nuevosPuntos = std::min(anterioresPuntos + puntos, 15);
        this->conductores[dni].first = nuevosPuntos;
        if (anterioresPuntos != nuevosPuntos) {
            this->cuantos_por_puntos[anterioresPuntos]--;
            this->cuantos_por_puntos[nuevosPuntos]++;
            this->cuales_por_puntos[anterioresPuntos].erase(this->conductores[dni].second);
            this->cuales_por_puntos[nuevosPuntos].push_front(dni);
            this->conductores[dni].second = this->cuales_por_puntos[nuevosPuntos].begin();
        }
    }

    int consultar(std::string dni) {
        if (!this->conductores.count(dni))
            throw std::domain_error("Conductor inexistente");
        return this->conductores[dni].first;
    }

    int cuantos_con_puntos(int puntos) {
        if (puntos < 0 || puntos > 15)
            throw std::domain_error("Puntos no validos");
        return this->cuantos_por_puntos[puntos];
    }

    std::list<std::string> lista_por_puntos(int puntos) {
        if (puntos < 0 || puntos > 15)
            throw std::domain_error("Puntos no validos");
        return this->cuales_por_puntos[puntos];
    }

private:
    std::vector<int> cuantos_por_puntos;
    std::unordered_map<std::string, pair<int, list<std::string>::iterator>> conductores;
    std::vector<std::list<std::string>> cuales_por_puntos;
};

using namespace std;
bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    CarnetPuntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else if (orden == "lista_por_puntos") {
                cin >> punt;
                std::list<std::string> lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                auto it = lista.begin();
                while (it != lista.end()) {
                    cout << " " << *it;
                    it++;
                }
                cout << '\n';
            }
            else // por aquí no pasa
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error& e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}