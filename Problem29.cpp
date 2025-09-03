/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Juan Diego Barrado Daganzo
  Estudiante 2: Daniel González Arbelo

  Dad una explicación de la solución.

  Indicad aquí el coste del algoritmo y las recurrencias planteadas en
  el caso del árbol equilibrado, y en el caso del árbol degenerado.

  @ </answer> */


#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>


  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para resolver el problema.

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}


using namespace std;


// ----------------------------------------------------------------
// Define aquí la función pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas <answer> y </answer>

//@ <answer>

#include <cmath>

/*
La solucion es recursiva, basandose en cada nivel del arbol en las soluciones parciales de sus dos hijos.
En cada llamada devolvemos la mayor profundidad a la que se puede encontrar un nodo del arbol y la mejor solución
encontrada hasta el momento.
Calculando esto en ambos hijos del nodo actual, la mejor solución en este punto puede ser alguna de las dos calculadas
previamente o la nueva, resultante de hacer un camino de la hoja mas profunda de la izquierda a la hoja mas profunda de la derecha.
Calculamos la mejor solución entre estas tres y la devolvemos junto con la mayor profundidad de entre las dos calculadas (incrementada en uno).

Si el árbol es degenerado, se define el coste del algoritmo con la siguiente recurrencia:
T(n) = T(n - 1) + c = T(n - 2) + 2c = ... pertenece a O(n), siendo n el número de nodos del árbol.

Si el árbol está equilibardo, se define el coste del algoritmo con la siguiente recurrencia:
T(n) = 2T(n/2) + c = ... pertenece también a O(n)
*/

//Formato de la solucion: {mayorProfundidad, mejorSolución}
template <typename T> std::pair<int, int> solve(const BinTree<T>& tree) {
    if (tree.empty()) return { 0, 0 };
    else {
        auto i = solve(tree.left());
        auto d = solve(tree.right());
        int nuevaSol = std::max(i.first + 1 + d.first, std::max(i.second, d.second));
        return { std::max(i.first, d.first) + 1, nuevaSol };
    }
}

int max_hitos_visitados(const BinTree<int>& montanya) {
    auto sol = solve(montanya);
    return sol.second;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if (arbol.empty()) return false;
    cout << max_hitos_visitados(arbol) << '\n';
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
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}
