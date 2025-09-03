/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1:
  Estudiante 2:

  Dad una explicación de la solución y justificad su coste.

  @ </answer> */


  // Añade los include que necesites
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <map>
#include <cassert>
#include <vector>
#include <set>
using namespace std;


// Implementa a continuación la clase Urgencias.
//@ <answer>

using paciente = string;
using gravedad = int;

class Urgencias {

public:
    Urgencias() {
        esperas.assign(4, {});
    }

    void nuevo_paciente(paciente p, gravedad g) {
        if (pacientes.count(p))
            throw domain_error("Paciente repetido");
        if (g < 1 || g > 3)
            throw domain_error("Gravedad incorrecta");
        esperas[g].push_back(p);
        pacientes[p] = { g, --esperas[g].end() };
    }

    int gravedad_actual(paciente e) const {
        if(!pacientes.count(e))
            throw domain_error("Paciente inexistente");
        return pacientes.at(e).g;
    }

    paciente siguiente() {
        paciente p;
        if (!esperas[3].empty())
            p = esperas[3].front();
        else if (!esperas[2].empty())
            p = esperas[2].front();
        else if (!esperas[1].empty())
            p = esperas[1].front();
        else
            throw domain_error("No hay pacientes");
        InfoPaciente info = pacientes.at(p);
        esperas[info.g].erase(info.itEspera);
        pacientes.erase(p);
        return p;
    }

    void mejora(paciente p) {
        auto it = pacientes.find(p);
        if (it == pacientes.end())
            throw domain_error("Paciente inexistente");
        InfoPaciente& info = it->second;
        esperas[info.g].erase(info.itEspera);
        if (--info.g == 0) {
            if(!setRecuperados.count(p))
                setRecuperados.insert(p);
            pacientes.erase(p);
        }
        else {
            esperas[info.g].push_front(p);
            info.itEspera = esperas[info.g].begin();
        }
    }

    list<paciente> recuperados() const {
        list<paciente> lista;
        for (auto p : setRecuperados)
            lista.push_back(p);
        return lista;
    }

private:
    struct InfoPaciente {
        InfoPaciente() {};
        InfoPaciente(gravedad g, list<paciente>::iterator it) : g(g), itEspera(it) {};
        gravedad g;
        list<paciente>::iterator itEspera;
    };
    unordered_map<paciente, InfoPaciente> pacientes;
    vector<list<paciente>> esperas;
    set<paciente> setRecuperados;
};




//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden, pac;
    int grav;
    cin >> orden;
    if (!cin)
        return false;

    Urgencias sala;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> pac >> grav;
                sala.nuevo_paciente(pac, grav);
            }
            else if (orden == "gravedad_actual") {
                cin >> pac;
                int g = sala.gravedad_actual(pac);
                cout << "La gravedad de " << pac << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                string p = sala.siguiente();
                cout << "Siguiente paciente: " << p << '\n';
            }
            else if (orden == "recuperados") {
                auto lista = sala.recuperados();
                cout << "Lista de recuperados:";
                for (auto& p : lista)
                    cout << ' ' << p;
                cout << '\n';
            }
            else if (orden == "mejora") {
                cin >> pac;
                sala.mejora(pac);
            }
            else {
                assert("OPERACION DESCONOCIDA" && false);
            }
        }
        catch (domain_error e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> orden;
    }
    cout << "---\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
