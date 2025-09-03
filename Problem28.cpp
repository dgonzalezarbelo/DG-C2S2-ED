#include <cassert>
#include <iostream>
#include <memory>
#include <cmath>

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

template <typename T> int height(const BinTree<T>& tree) {
    if (tree.empty()) {
        return 0;
    }
    else {
        return 1 + std::max(height(tree.left()), height(tree.right()));
    }
}

template <typename T> bool balanced(const BinTree<T>& tree) {
    return balanced_height(tree).first;
}

template <typename T>
std::pair<bool, int> balanced_height(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { true, 0 };
    }
    else {
        auto [bal_left, height_left] = balanced_height(tree.left());
        auto [bal_right, height_right] = balanced_height(tree.right());
        bool balanced =
            bal_left && bal_right && abs(height_left - height_right) <= 1;
        int height = 1 + std::max(height_left, height_right);
        return { balanced, height };
    }
}

template<typename T>
std::pair<int, int> nivel_hojas(const BinTree<T>& arbol) {  // {nivel mas bajo de hoja, numero de hojas en ese nivel}
    if (arbol.empty()) return { 0, 0 };
    else {
        std::pair<int, int> i;
        std::pair<int, int> d;
        if (!arbol.left().empty() && !arbol.right().empty()) {
            i = nivel_hojas(arbol.left());
            d = nivel_hojas(arbol.right());
            if (i.first == d.first) {
                if (i.first == -1) return { -1, -1 };
                else return { i.first + 1, i.second + d.second };
            }
            else {
                if (std::abs(i.first - d.first) > 1) {
                    return { -1, -1 };
                }
                else {
                    if (i.first > d.first) {
                        if (d.second == 1) return { -1, -1 };
                        else return { i.first + 1, i.second };
                    }
                    else {
                        if (i.second == 1) return { -1, -1 };
                        else return { d.first + 1, d.second };
                    }
                }
            }
        }
        else if (!arbol.left().empty()) {
            i = nivel_hojas(arbol.left());
            if (i.first == -1) return { -1, -1 };
            else return { i.first + 1, i.second };
        }
        else if (!arbol.right().empty()) {
            d = nivel_hojas(arbol.right());
            if (d.first == -1) return { -1, -1 };
            else return { d.first + 1, d.second };
        }
        else return { 0, 1 };
    }
}

template <typename T>
bool es_estable(const BinTree<T>& arbol) {
    return nivel_hojas(arbol).first != -1;
}

void resuelveCaso() {
    BinTree<int> tree = read_tree<int>(std::cin);
    if (es_estable(tree)) printf("SI\n");
    else printf("NO\n");
}

int main() {
    int num;
    std::cin >> num;
    while (num--) resuelveCaso();
    return 0;
}