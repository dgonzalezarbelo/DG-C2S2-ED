#include <iostream>
#include <queue>
#include <stack>

void ordenNatural(std::queue<int>& q) {
    std::queue<int> positivos;  //Hacemos una cola auxiliar para los valores positivos para conservar el orden
    std::stack<int> negativos;  //Hacemos una pila auxiliar para los valores negativos para invertir el orden
    while (!q.empty()) {
        if (q.front() >= 0) positivos.push(q.front());
        else negativos.push(q.front());
        q.pop();
    }
    while (!negativos.empty()) {
        q.push(negativos.top());
        negativos.pop();
    }
    while (!positivos.empty()) {
        q.push(positivos.front());
        positivos.pop();
    }
}

bool resuelveCaso() {
    int num;
    std::cin >> num;
    if (!num) return false;
    std::queue<int> q;
    int aux;
    for (int i = 0; i < num; i++) {
        std::cin >> aux;
        q.push(aux);
    }
    ordenNatural(q);
    printf("%d", q.front());
    q.pop();
    while (!q.empty()) {
        printf(" %d", q.front());
        q.pop();
    }
    printf("\n");
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}