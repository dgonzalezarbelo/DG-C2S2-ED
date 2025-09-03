#include <cassert>
#include <iostream>
#include <memory>
#include <cmath>
#include <string>

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

    int num_nodes() const {
        return num_nodes_from(root_node);
    }

    int num_leaves() const {
        return num_leaves_from(root_node);
    }

    int height() const {
        return height_from(root_node);
    }
private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

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

    int num_nodes_from(const NodePointer& root) const {
        if (root == nullptr) return 0;
        else return num_nodes_from(root->left) + num_nodes_from(root->right) + 1;
    }

    int num_leaves_from(const NodePointer& root) const {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 1;
        return num_leaves_from(root->left) + num_leaves_from(root->right);
    }

    int height_from(const NodePointer& root) const {
        if (root == nullptr) return 0;
        else return 1 + std::max(height_from(root->left), height_from(root->right));
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

template <typename T> T min(BinTree<T> const& t) { //Se analiza una unica vez cada nodo del árbol, por lo que el coste es lineal con respecto al número de nodos
    T sol = t.root();
    T i, d;
    if (!t.left().empty()) {
        i = min(t.left());
        if (i < sol) sol = i;
    } 
    if (!t.right().empty()) {
        d = min(t.right());
        if (d < sol) sol = d;
    }
    return sol;
}

template <typename T> T solve() {
    BinTree<T> t = read_tree<T>(std::cin);
    return min(t);
}

bool resuelveCaso() {
    char tipo;
    std::cin >> tipo;
    if (!std::cin) return false;
    if (tipo == 'N') std::cout << solve<int>() << '\n';
    else std::cout << solve<std::string>() << '\n';
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}