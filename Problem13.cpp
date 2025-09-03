/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Pila mediante listas enlazadas simples.
  */

#ifndef __STACK_LINKEDLIST_H
#define __STACK_LINKEDLIST_H

#include <cassert>
#include <iostream>
#include <string>

template <typename T> class StackLinkedList {
public:
    StackLinkedList() : top_node(nullptr) {}
    StackLinkedList(const StackLinkedList& other)
        : top_node(copy_nodes_from(other.top_node)) {}

    ~StackLinkedList() { free_nodes_from(top_node); }

    StackLinkedList& operator=(const StackLinkedList& other) {
        if (this != &other) {
            free_nodes_from(top_node);
            top_node = copy_nodes_from(other.top_node);
        }
        return *this;
    }

    void push(const T& elem) { top_node = new Node{ elem, top_node }; }

    void pop() {
        assert(top_node != nullptr);
        Node* target = top_node;
        top_node = top_node->next;
        delete target;
    }

    T& top() {
        assert(top_node != nullptr);
        return top_node->value;
    }

    const T& top() const {
        assert(top_node != nullptr);
        return top_node->value;
    }

    bool empty() const { return (top_node == nullptr); }

private:
    struct Node {
        T value;
        Node* next;
    };

    Node* copy_nodes_from(Node* other);
    void free_nodes_from(Node* other);

    Node* top_node;
};

template <typename T>
typename StackLinkedList<T>::Node*
StackLinkedList<T>::copy_nodes_from(Node* other) {
    if (other == nullptr) {
        return nullptr;
    }
    else {
        Node* first = new Node{ other->value, nullptr };
        Node* last = first;
        Node* current = other->next;
        while (current != nullptr) {
            Node* new_node = new Node{ current->value, nullptr };
            last->next = new_node;
            current = current->next;
            last = new_node;
        }
        return first;
    }
}

template <typename T> void StackLinkedList<T>::free_nodes_from(Node* other) {
    Node* current = other;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

#endif

bool buscarApertura(char apertura, StackLinkedList<char> & stack, int & abiertos) {
    bool encontrada = false, seguir = true;
    while (!encontrada && !stack.empty() && seguir) {
        if (stack.top() == '(' || stack.top() == '{' || stack.top() == '[') {
            if (apertura == stack.top()) {
                encontrada = true;
                abiertos--;
            } 
            else seguir = false;
        }
        stack.pop();
    }
    return encontrada;
}

bool resuelveCaso() {
    std::string cad;
    getline(std::cin, cad);
    if (!std::cin) return false;
    StackLinkedList<char> stack;
    char letra;
    bool equilibrada = true;
    int abiertos = 0;
    for (int i = 0; i < cad.size() && equilibrada; i++) {
        letra = cad[i];
        if (letra == '(' || letra == '{' || letra == '[') {
            abiertos++;
            stack.push(letra);
        }
        else if (letra == ')') equilibrada = buscarApertura('(', stack, abiertos);
        else if (letra == '}') equilibrada = buscarApertura('{', stack, abiertos);
        else if (letra == ']') equilibrada = buscarApertura('[', stack, abiertos);
        else stack.push(letra);
    }
    equilibrada = equilibrada && (abiertos == 0);
    equilibrada ? std::cout << "SI\n" : std::cout << "NO\n";
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}