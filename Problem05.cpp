/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificación fuera de esas etiquetas no será corregida.
  */

  /*@ <answer>
   *  Estudiante 1: Nombre y Apellidos: Juan Diego Barrado Daganzo
   *  Estudiante 2: Nombre y Apellidos: Daniel Gonzalez Arbelo
   *@ </answer> */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

/*@ <answer> */

class Polinomio {
private:
    struct monomio {
        int coef;
        int exp;
        monomio(int coef, int exp) : coef(coef), exp(exp) { };
    };

    std::vector <monomio> polinomio;

    bool buscar(int exp, int ini, int fin, int& pos) const {
        if (polinomio.size() == 0) {
            pos = 0;
            return false;
        }
        if (ini >= fin - 1) {
            if (polinomio[ini].exp < exp) pos = ini + 1;
            else pos = ini;
            if (polinomio[ini].exp == exp) return true;
            else return false;
        }
        else {
            int m = (ini + fin - 1) / 2;
            if (exp <= polinomio[m].exp) return buscar(exp, ini, m + 1, pos);
            else return buscar(exp, m + 1, fin, pos);
        }

    }

    void insertar(monomio elem, int pos) {
        if (polinomio.size() == 0) polinomio.push_back(elem);
        else {
            monomio ultimo = polinomio[polinomio.size() - 1];
            polinomio.push_back(ultimo);
            for (int i = polinomio.size() - 1; i > pos; i--) {
                polinomio[i] = polinomio[i - 1];
            }
            polinomio[pos] = elem;
        }
    }

public:
    void sumaMono(int coef, int exp) {
        int pos;
        monomio monom(coef, exp);
        if (buscar(exp, 0, this->polinomio.size(), pos))
            this->polinomio[pos].coef += coef;
        else
            insertar(monom, pos);
    }

    int64_t evalua(int valor) const {
        int64_t res = 0;
        for (int i = polinomio[polinomio.size() - 1].exp, j = polinomio.size() - 1; i >= 0; i--) {
            if (j >= 0 && polinomio[j].exp == i) {
                res = res * valor + polinomio[j].coef;
                j--;
            }
            else res *= valor;
        }
        return res;
    }
};


bool resuelveCaso() {
    int coef, exp;
    cin >> coef >> exp;

    if (!cin)
        return false;

    // leemos el polinomio, monomio a monomio
    Polinomio poli;
    while (coef != 0 || exp != 0) {
        poli.sumaMono(coef, exp);
        cin >> coef >> exp;
    }

    int N;
    cin >> N;
    while (N--) {
        // evaluamos para un nuevo valor
        int valor;
        cin >> valor;
        cout << poli.evalua(valor);
        if (N) cout << ' ';
    }
    cout << '\n';
    return true;
}

/*@ </answer> */

int main() {

#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Comentar si no se trabaja en Visual Studio
    system("PAUSE");
#endif

    return 0;
}


