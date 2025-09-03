/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Juan Diego Barrado Daganzo
  Estudiante 2: Daniel González Arbelo


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>

  /*
    Implementación de la clase BinTree para representar árboles binarios.
   */

template<class T>
class BinTree {
public:

    BinTree() : root_node(nullptr) { }

    BinTree(const T& elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


    bool empty() const {
        return root_node == nullptr;
    }

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

    void display(std::ostream& out) const {
        display_node(root_node, out);
    }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right) : elem(elem), left(left), right(right) { }

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

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 *
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream& in) {
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

/*
 * Analizador léxico del lenguaje
 */

class Lexer {
public:
    Lexer(std::istream& in) : in(in) { }

    std::string peek() {
        if (next != "") {
            return next;
        }
        else {
            next = read_next();
            return next;
        }
    }

    std::string get() {
        std::string result = peek();
        next = "";
        return result;
    }

private:
    std::istream& in;

    std::string read_next() {
        std::ostringstream result;
        char current;
        in >> current;
        while (iswspace(current)) {
            in >> current;
        }


        if (isdigit(current)) {
            result << current;
            while (isdigit(in.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (isalpha(current)) {
            result << current;
            while (isalnum(in.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
            result << current;
        }
        else if (current == ':') {
            result << current;
            in >> current;
            if (current != '=') throw std::domain_error(std::string("invalid token: :") + current);
            result << current;
        }
        else {
            throw std::domain_error(std::string("invalid_token: ") + current);
        }

        return result.str();
    }



private:
    std::string next;
};

/*
 * Analizador sintáctico del lenguaje
 */


class Parser {
public:
    Parser(std::istream& in) : l(in) { }

    BinTree<std::string> parse() {
        return S();
    }

private:
    Lexer l;

    bool is_identifier(const std::string& token) {
        return (!token.empty() && isalpha(token[0]));
    }

    bool is_identifier_or_number(const std::string& token) {
        return (!token.empty() && isalnum(token[0]));
    }


    BinTree<std::string> S() {
        std::string identifier = l.get();
        if (!is_identifier(identifier)) throw std::domain_error(std::string("identifier expected, found ") + identifier);

        std::string equal = l.get();
        if (equal != ":=") throw std::domain_error(std::string(":= expected, found ") + equal);

        BinTree<std::string> rhs = E();

        std::string semicolon = l.get();
        if (semicolon != ";") throw std::domain_error(std::string("; expected, found ") + semicolon);

        return { { identifier }, ":=", rhs };
    }

    BinTree<std::string> E() {
        BinTree<std::string> term = T();
        return Ep(term);
    }

    BinTree<std::string> Ep(const BinTree<std::string>& left) {
        std::string op = l.peek();
        if (op == "+" || op == "-") {
            l.get();
            BinTree<std::string> term = T();
            return Ep({ left, op, term });
        }
        else {
            return left;
        }
    }

    BinTree<std::string> T() {
        BinTree<std::string> factor = F();
        return Tp(factor);
    }

    BinTree<std::string> Tp(const BinTree<std::string>& left) {
        std::string op = l.peek();
        if (op == "*") {
            l.get();
            BinTree<std::string> factor = F();
            return Tp({ left, "*", factor });
        }
        else {
            return left;
        }
    }

    BinTree<std::string> F() {
        std::string next = l.get();
        if (is_identifier_or_number(next)) {
            return { next };
        }
        else if (next == "(") {
            BinTree<std::string> inner = E();
            std::string closing = l.get();
            if (closing != ")") throw std::domain_error(std::string(") expected, found ") + closing);
            return inner;
        }
        else {
            throw std::domain_error(std::string("number or identifier expected, found ") + next);
        }
    }
};

/*
 * Función que lee una sentencia y devuelve su árbol sintáctico.
 */

BinTree<std::string> parse(std::istream& in) {
    return Parser(in).parse();
}

#include <map>
using namespace std;

/* ======================================================================
 * Escribe tu solución entre las etiquetas "answer" que se muestran a
 * continuación.
 *
 * No es necesario añadir ni modificar ningún método de las clases
 * anteriores, pero puedes implementar las funciones auxiliares
 * que necesites.
 * ====================================================================== */
 /*@ <answer> */

bool isnum(string cad) {
    return isdigit(cad[0]);
}

/*
En la funcíon comprobamos primero si la raíz del árbol es un signo de operación, en cuyo caso devolvemos el resultado de la
operación aplicada sobre el resultado de la funcíon en el hijo izquierdo y derecho del árbol.
En caso de no ser una operación, comprobamos si es un número, en cuyo caso devolvemos su valor.
Si no, la única opción es que sea una variable, en cuyo caso devolvemos el valor asociado a esa variable en el mapa.

El coste de este algoritmo en el caso peor es n*logn, siendo n el número de nodos.
Este es el coste en el caso peor porque la única operación cuyo coste no es constante es la búsqueda en el mapa, que se da 
para cada variable almacenada en el árbol. El caso peor es cuando el árbol es completo, puesto que las variables son siempre
hojas del árbol, por lo que en este caso habría n/2 hojas, por lo que el coste del algoritmo pertenece al orden de O(n/2 * logn),
que es O(nlogn)

Aclaración: El coste de isnum es constante y el de stoi lo consideramos constante porque las cadenas tienen menos de 10 caractéres.
*/

int solve(map<string, int> const& map, BinTree<string> const& tree) {
    if (tree.root() == "+") return solve(map, tree.left()) + solve(map, tree.right());
    else if (tree.root() == "-") return solve(map, tree.left()) - solve(map, tree.right());
    else if (tree.root() == "*") return solve(map, tree.left()) * solve(map, tree.right());
    else if (isnum(tree.root())) return stoi(tree.root());
    else return map.at(tree.root());
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;
    map<string, int> map;
    /*
    Para cada línea de la entrada, la variable a asignar es el hijo izquierdo del árbol y el valor es el hijo derecho.
    Por tanto, asignamos en el mapa el valor de las operaciones sobre el hijo derecho al hijo izquierdo.

    Cada caso tiene coste O(MlogN), con N el número de nodos del árbol (el número de nodos del hijo derecho es N - 2), 
    porque el algoritmo solve es de coste O(NlogN) y la búsqueda en el mapa para la asignación es logarítmica, 
    por lo que en conjunto es O(NlogN).

    Considerando S el número máximo de nodos en cada asignación, el coste de la solucíon total es O(M*SlogS),
    siendo M el número de asignaciones.
    */
    for (int i = 0; i < N; i++) {
        BinTree<string> tree = parse(cin);
        map[tree.left().root()] = solve(map, tree.right());
    }
    auto it = map.begin();
    while (it != map.end()) {
        cout << it->first << " = " << it->second << '\n';
        ++it;
    }
    cout << "---\n";
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
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}

/*

 3
 x := 3;
 y := 5;
 z := x + y;
 2
 b := 5 + 6 * 3;
 a := b - 1;
 3
 x := 1;
 x := x * 2;
 x := x * 2;
 0
 */
