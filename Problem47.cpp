/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1:
  * Estudiante 2:
  *
  */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;

class ConteoVotos {
private:
    using Estado = string;
    using Partido = string;
public:
    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (estados.count(nombre))
            throw domain_error("Estado ya existente");
        estados.insert({ nombre, InfoEstado(num_compromisarios) });
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        auto it = estados.find(estado);
        if (it == estados.end())
            throw domain_error("Estado no encontrado");
        auto& itInfo = it->second;
        if (itInfo.partidosVotados.count(partido))
            itInfo.partidosVotados[partido] += num_votos;
        else
            itInfo.partidosVotados[partido] = num_votos;
        if (itInfo.ganador == "NINGUNO") {
            itInfo.ganador = partido;
            auto itPartido = partidosGanadores.find(partido);
            if (itPartido == partidosGanadores.end())
                partidosGanadores[partido] = itInfo.compromisarios;
            else
                itPartido->second += itInfo.compromisarios;
        }
        else if (itInfo.partidosVotados[partido] > itInfo.partidosVotados[itInfo.ganador]) {
            auto itAntiguoGanador = partidosGanadores.find(itInfo.ganador);
            itAntiguoGanador->second -= itInfo.compromisarios;
            if (itAntiguoGanador->second == 0) partidosGanadores.erase(itInfo.ganador);
            itInfo.ganador = partido;
            auto itPartido = partidosGanadores.find(partido);
            if (itPartido == partidosGanadores.end())
                partidosGanadores[partido] = itInfo.compromisarios;
            else
                itPartido->second += itInfo.compromisarios;
        }
    }

    string ganador_en(const string& estado) const {
        auto it = estados.find(estado);
        if (it == estados.end())
            throw domain_error("Estado no encontrado");
        return it->second.ganador;
    }

    vector<pair<string, int>> resultados() const {
        vector<pair<string, int>> ganadores;
        for (auto it = partidosGanadores.begin(); it != partidosGanadores.end(); it++) {
            ganadores.push_back(*it);
        }
        return ganadores;
    }

private:
    struct InfoEstado {
        InfoEstado(int compromisarios) : compromisarios(compromisarios), ganador("NINGUNO") {};
        unordered_map<Partido, int> partidosVotados;
        Partido ganador;
        int compromisarios;
    };
    unordered_map <Estado, InfoEstado> estados; //Asociamos a cada estado los votos de cada partido y el ganador actual
    map<Partido, int> partidosGanadores;
};


bool resuelveCaso() {
    string operacion, estado, partido;
    int compromisarios, votos;
    cin >> operacion;
    if (!cin)
        return false;

    ConteoVotos CV;

    while (operacion != "FIN") {
        try {
            if (operacion == "nuevo_estado") {
                cin >> estado >> compromisarios;
                CV.nuevo_estado(estado, compromisarios);
            }
            else if (operacion == "sumar_votos") {
                cin >> estado >> partido >> votos;
                CV.sumar_votos(estado, partido, votos);
            }
            else if (operacion == "ganador_en") {
                cin >> estado;
                auto ganador = CV.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << '\n';
            }
            else if (operacion == "resultados") {
                for (auto [estado, compromisarios] : CV.resultados()) {
                    cout << estado << ' ' << compromisarios << '\n';
                }
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main() {

    while (resuelveCaso()) {}

    return 0;
}
