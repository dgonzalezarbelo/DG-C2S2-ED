
#include "list_linked_double.h"
class Persona {
private:
    std::string nombre;
    int edad;
public:

    Persona(){}

    Persona(std::string nombre, int edad) {
        this->nombre = nombre;
        this->edad = edad;
    }

    std::string getNombre() const { 
        return this->nombre; 
    }
    
    int getEdad() const { 
        return this->edad; 
    }
};



bool resuelveCaso() {
    int N, inf, sup;
    std::cin >> N >> inf >> sup;
    if (N == 0 && inf == 0 && sup == 0) return false;
    ListLinkedDouble<Persona> list;
    std::string nombre;
    int edad;
    for (int i = 0; i < N; i++) {
        std::cin >> edad;
        std::cin.get();
        std::getline(std::cin, nombre);
        Persona persona(nombre, edad);
        list.push_back(persona);
    }
    list.remove_if([inf, sup](Persona persona) { return persona.getEdad() >= inf && persona.getEdad() <= sup; });
    auto it = list.cbegin();
    while (it != list.cend()) {
        Persona persona = *it;
        std::cout << persona.getNombre() << '\n';
        it++;
    }
    std::cout << "---\n";
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}