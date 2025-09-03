/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Juan Diego Barrado Daganzo
  Estudiante 2: Daniel Gonz�lez Arbelo

  Dad una explicaci�n de la soluci�n y justificad su coste.

  @ </answer> */


  // A�ade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <map>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una direcci�n desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

// Implementa a continuaci�n la clase Desierto.
//@ <answer>

class Desierto {
public:
    //Usamos tres mapas: uno que relaciona cada nombre con sus coordenadas, uno que relaciona un entero x con los enteros y
    //tales que la posicion (x, y) est� ocupada y uno que hace lo mismo que este pero relacionando las y con las x
    //Esto nos permite, para una componente fija, obtener todas las torres que comparten esa componente
    //Como nos piden buscar torres en ciertas direcciones, estos mapas est�n ordenados
    //Guardamos tambien iteradores para disminuir costes de ciertas operaciones, evitando tener que hacer b�squedas
    Desierto() { }

    //El coste es O(log n + log m), siendo n el n�mero de torres con segunda componente = y,
    //y siendo m el n�mero de torres con segunda componente = x ,
    //  puesto que al hacer torres[nombre].xFijaIt = ... se est� haciendo inserci�n en un mapa ordenado, y lo mismo
    //en la siguiente l�nea, y el resto de operaciones tiene coste constante, pues el mapa torres es unordered_map
    void anyadir_torre(const string& nombre, int x, int y) {
        if (torres.count(nombre))
            throw domain_error("Torre ya existente");
        if (xFija.count(x) && xFija[x].count(y))
            throw domain_error("Posicion ocupada");
        torres[nombre] = { x, y };
        torres[nombre].xFijaIt = xFija[x].insert({ y, nombre }).first;
        torres[nombre].yFijaIt = yFija[y].insert({ x, nombre }).first;
    }

    //El coste es O(log n + log m), siendo n el n�mero de torres con segunda componente = y,
    //y siendo m el n�mero de torres con segunda componente = x , por el mismo motivo que el anterior, puesto que se est� aplicando erase en un mapa ordenado, cuyo coste
    //de b�squeda es O(log n)
    void eliminar_torre(const string& nombre) {
        if (!torres.count(nombre))
            throw domain_error("Torre no existente");
        InfoTorre t = torres[nombre];
        xFija[t.x].erase(t.y);
        yFija[t.y].erase(t.x);
        torres.erase(nombre);
    }
    
    //El coste es O(log n), siendo n el n�mero de torres con segunda componente = y, 
    //puesto que se hace b�squeda en un unordered_map, cuyo coste de b�squeda es O(1), y luego,
    //en el caso peor, se hace b�squeda en un map, cuyo coste de b�squeda es O(log n)
    pair<bool, string> torre_en_posicion(int x, int y) const { 
        if (xFija.count(x)) {
            auto it = xFija.at(x).find(y);
            if (it == xFija.at(x).end())
                return { false, "" };
            else return { true, it->second };
        }
        else return { false, "" };
    }

    //El coste es O(1), puesto que solo se hace b�squeda en un unordered_map
    pair<int, int> posicion(const string& nombre) const {
        if (!torres.count(nombre))
            throw domain_error("Torre no existente");
        return { torres.at(nombre).x, torres.at(nombre).y };
    }

    //El coste es O(1), puesto que, como para cada torre guardamos sus iteradores a los mapas,
    //simplemente se tiene que incrementar o decrementar un iterador
    string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
        if (!torres.count(nombre))
            throw domain_error("Torre no existente");
        InfoTorre t = torres.at(nombre);
        if (dir == Direccion::Norte) {
            auto it = t.xFijaIt;
            it++;
            if (it == xFija.at(t.x).end())
                throw domain_error("No hay torres en esa direccion");
            else return it->second;
        }
        else if (dir == Direccion::Sur) {
            auto it = t.xFijaIt;
            if (it == xFija.at(t.x).begin())
                throw domain_error("No hay torres en esa direccion");
            else return (--it)->second;
        }
        else if (dir == Direccion::Este) {
            auto it = t.yFijaIt;
            it++;
            if (it == yFija.at(t.y).end())
                throw domain_error("No hay torres en esa direccion");
            else return it->second;
        }
        else if (dir == Direccion::Oeste) {
            auto it = t.yFijaIt;
            if (it == yFija.at(t.y).begin())
                throw domain_error("No hay torres en esa direccion");
            else return (--it)->second;
        }
    }

private:
    // A�ade aqu� los atributos que conforman la representaci�n
    // interna del TAD
    //
    // Tambi�n puedes a�adir m�todos auxiliares privados
    struct InfoTorre {
        InfoTorre() {};
        InfoTorre(int x, int y) : x(x), y(y) {};
        int x;
        int y;
        map<int, string>::iterator xFijaIt;
        map<int, string>::iterator yFijaIt;
    };
    unordered_map<string, InfoTorre> torres;
    unordered_map<int, map<int, string>> xFija;
    unordered_map<int, map<int, string>> yFija;
    

};



//@ </answer>
// �No modificar nada debajo de esta l�nea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string inst, nombre; int x, y; Direccion dir;
    cin >> inst;
    if (!cin) return false;
    Desierto desierto;
    while (inst != "FIN") {
        try {
            if (inst == "anyadir_torre") {
                cin >> nombre >> x >> y;
                desierto.anyadir_torre(nombre, x, y);
            }
            else if (inst == "eliminar_torre") {
                cin >> nombre;
                desierto.eliminar_torre(nombre);
            }
            else if (inst == "posicion") {
                cin >> nombre;
                auto [x, y] = desierto.posicion(nombre);
                cout << x << ' ' << y << '\n';
            }
            else if (inst == "torre_en_posicion") {
                cin >> x >> y;
                auto [hay, nombre] = desierto.torre_en_posicion(x, y);
                if (hay) cout << "SI " << nombre << '\n';
                else cout << "NO\n";
            }
            else {
                cin >> nombre >> dir;
                nombre = desierto.torre_mas_cercana(nombre, dir);
                cout << nombre << '\n';
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
        }
        cin >> inst;
    }
    cout << "---\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
