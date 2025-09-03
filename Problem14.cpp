#include <iostream>
#include <queue>
bool resuelveCaso() {
    int N, salto;
    std::cin >> N >> salto;
    if (N == 0 && salto == 0) return false;
    int siguiente = 1;
    std::queue<int> q;
    for (int i = 1; i <= N; i++) {
        q.push(i);
    }
    bool eliminar = false;
    int i = 0;
    int ultimo;
    while (!q.empty()) {
        if (eliminar) {
            ultimo = q.front();
            q.pop();
            eliminar = false;
        }
        else {
            i++;
            q.push(q.front());
            q.pop();
            if (i % salto == 0) eliminar = true;
        }
    }
    printf("%d\n", ultimo);
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}