#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

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

std::pair<int, int> mult7Accesible(std::vector<int> const& primos, BinTree<int> const& tree) {
    if (tree.empty()) return { -1, -1 };
    else if (tree.root() % 7 == 0) {
        if (tree.root() != 7) return { tree.root(), 1 };
        else return { -1, -1 };
    } 
    else {
        bool primo = std::binary_search(primos.begin(), primos.end(), tree.root());
        if (!primo) {
            std::pair<int, int> sol1 = mult7Accesible(primos, tree.left());
            std::pair<int, int> sol2 = mult7Accesible(primos, tree.right());
            if (sol1.first != -1 && sol2.first != -1) {
                if (sol1.second <= sol2.second) return { sol1.first, sol1.second + 1 };
                else return { sol2.first, sol2.second + 1 };
            }
            else if (sol1.second > 0) return { sol1.first, sol1.second + 1 };
            else if (sol2.second > 0) return { sol2.first, sol2.second + 1 };
            else return { -1, -1 };
        }
        else return { -1, -1 };
    }
}

void resuelveCaso(std::vector<int> const& primos) {
    BinTree<int> tree = read_tree<int>(std::cin);
    std::pair<int, int> sol = mult7Accesible(primos, tree);
    if (sol.first == -1) printf("NO HAY\n");
    else printf("%d %d\n", sol.first, sol.second);
}

int main() {
    int num;
    std::cin >> num;
    std::vector<int> primos;
    primos.push_back(2);
    bool primo = true;
    for (int i = 3; i < 5000; i = i + 2) {
        primo = true;
        for (int j = 0; j < primos.size() && primo; j++) {
            if (i % primos[j] == 0) primo = false;
        }
        if (primo) primos.push_back(i);
    }
    while (num--) resuelveCaso(primos);
    return 0;
}