#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

bool resuelveCaso() {
    // leer los datos de la entrada
    int horasReproduccion, horasYemas, tiempo;

    std::cin >> horasReproduccion;

    if (!std::cin)  // fin de la entrada
        return false;

    std::cin >> horasYemas >> tiempo;

    //deque<int> hongos;
    //deque <int> yemas;

    //hongos.push_back(horasReproduccion);

    deque<pair<int, int>> hongos; //numero, hora, 
    deque<pair<int, int>> yemas; //igual

    int i = horasReproduccion;

    hongos.push_back({ 1, horasReproduccion });

    while (i <= tiempo) {
        if (yemas.empty()) { // aqui manejo con t = tiempoReproduccion
            i = hongos.front().second;
            yemas.push_back({ 1, horasYemas + i });
            hongos.push_back({ 1, horasReproduccion + i });
            hongos.pop_front();
            i = min(yemas.front().second, hongos.front().second);
        }
        else {
            if (hongos.front().second == i && yemas.front().second != i) {

                int num_nuevas_yemas = hongos.front().first;
                yemas.push_back({ num_nuevas_yemas, i + horasYemas });
                hongos.push_back({ num_nuevas_yemas, i + horasReproduccion });
                hongos.pop_front();
            }
            else if (hongos.front().second != i && yemas.front().second == i) {
                int nuevos_hongos = yemas.front().first;
                yemas.push_back({ nuevos_hongos, i + horasYemas });
                hongos.push_back({ nuevos_hongos, i + horasReproduccion });
                yemas.pop_front();
            }
            else {
                int num_nuevas_yemas = hongos.front().first;
                int nuevos_hongos = yemas.front().first;
                yemas.push_back({ num_nuevas_yemas + nuevos_hongos, i + horasYemas });
                hongos.push_back({ num_nuevas_yemas + nuevos_hongos, i + horasReproduccion });
                yemas.pop_front();
                hongos.pop_front();
            }
            i = min(yemas.front().second, hongos.front().second);
        }
    }

    std::cout << hongos.size() + yemas.size() << std::endl;
	/*int N, M, T;
	cin >> N >> M >> T;
	if (!cin) return false;
	queue<pair<int, int>> nuevos, noNuevos;
	int tiempo = 0;
	int totales = 1;
	noNuevos.push({ N, 1 });
	tiempo = N;
	while (tiempo <= T) {
		int n = 0, nn = 0;
		if (noNuevos.front().first == tiempo) {
			n = noNuevos.front().second;
			nn = noNuevos.front().second;
			totales += noNuevos.front().second;
			noNuevos.pop();
		}
		if (!nuevos.empty() && nuevos.front().first == tiempo) {
			n += nuevos.front().second;
			nn += nuevos.front().second;
			totales += nuevos.front().second;
			nuevos.pop();
		}
		noNuevos.push({ tiempo + N, nn });
		nuevos.push({ tiempo + M, n });
		tiempo = min(noNuevos.front().first, nuevos.front().first);
	}
	cout << totales << '\n';
	*/
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}