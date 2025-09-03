/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>.
  *
  * Tampoco está permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos: ALBERTO VERDEJO
  //@ </answer>

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
using namespace std;

// Elige el tipo representante adecuado para el TAD OficinaEmpleo
// e implementa sus operaciones.
// Puedes añadir métodos o funciones privadas si lo consideras conveniente.
// Justifica la elección de los tipos y el coste de las operaciones.
//@ <answer>

using nombre = string;
using empleo = string;

class OficinaEmpleo {

public:

    void altaOficina(nombre const& nom, empleo const& emp) {
        auto it = personas.find(nom);
        if (it != personas.end()) {
            InfoPersona& persona = it->second;
            if (!persona.empleos.count(emp)) {
                empleos[emp].push_back(nom);
                persona.empleos[emp] = --empleos[emp].end();
            }
        }
        else {
            InfoPersona persona;
            empleos[emp].push_back(nom);
            persona.empleos[emp] = --empleos[emp].end();
            personas[nom] = persona;
        }
    }

    nombre ofertaEmpleo(empleo emp) {
        auto it = empleos.find(emp);
        if (it == empleos.end())
            throw domain_error("No existen personas apuntadas a este empleo");
        nombre nom = empleos[emp].front();
        InfoPersona& persona = personas.at(nom);
        for (auto empleo : persona.empleos) {
            empleos[empleo.first].erase(empleo.second);
            if (empleos[empleo.first].empty())
                empleos.erase(empleo.first);
        }
        personas.erase(nom);
        return nom;
    }

    vector<empleo> listadoEmpleos(nombre nom) const {
        auto persona = personas.find(nom);
        if (persona == personas.end())
            throw domain_error("Persona inexistente");
        vector<empleo> v;
        for (auto empleo : persona->second.empleos) {
            v.push_back(empleo.first);
        }
        return v;
    }

private:
    struct InfoPersona {
        InfoPersona() {};
        map<empleo, list<nombre>::iterator> empleos;
    };
    unordered_map<nombre, InfoPersona> personas;
    unordered_map<empleo, list<nombre>> empleos;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden, nom, emp;
    cin >> orden;
    if (!cin)
        return false;

    OficinaEmpleo paro;

    while (orden != "FIN") {
        try {
            if (orden == "altaOficina") {
                cin >> nom >> emp;
                paro.altaOficina(nom, emp);
            }
            else if (orden == "ofertaEmpleo") {
                cin >> emp;
                auto afortunado = paro.ofertaEmpleo(emp);
                cout << emp << ": " << afortunado << '\n';
            }
            else if (orden == "listadoEmpleos") {
                cin >> nom;
                auto caps = paro.listadoEmpleos(nom);
                cout << nom << ":";
                for (auto c : caps) {
                    cout << ' ' << c;
                }
                cout << '\n';
            }
        }
        catch (domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> orden;
    }
    cout << "---\n";
    return true;
}


int main() {

    while (resuelveCaso());

    return 0;
}

/*
 altaOficina Carlota administracion
 altaOficina Carlota secretariado
 altaOficina Carlota recursosHumanos
 altaOficina Juan administracion
 altaOficina Juan riesgosLaborales
 ofertaEmpleo administracion
 altaOficina Beatriz administracion
 altaOficina Beatriz jardineria
 altaOficina Beatriz biblioteca
 ofertaEmpleo administracion
 listadoEmpleos Carlota
 altaOficina Carlota informatica
 altaOficina Beatriz informatica
 listadoEmpleos Beatriz
 ofertaEmpleo informatica
 ofertaEmpleo informatica
 ofertaEmpleo informatica
 ofertaEmpleo biblioteca
 FIN
 ofertaEmpleo informatica
 altaOficina Ivan informatica
 altaOficina Ivan administracion
 listadoEmpleos Ivan
 ofertaEmpleo informatica
 ofertaEmpleo administracion
 listadoEmpleos Ivan
 FIN


 */
