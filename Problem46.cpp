#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

class Autoescuela {
	using Profesor = std::string;
	using Alumno = std::string;

public:
	Autoescuela() {

	}

	void alta(Alumno A, Profesor P) {
		auto it = alumnos.find(A);
		if (it == alumnos.end()) {
			alumnos.insert({ A, InfoAlumno(P, 0) });
			profesores[P].insert(A);
		}
		else {
			int puntos = it->second.puntos;
			Profesor antiguoProfesor = it->second.profesor;
			profesores[antiguoProfesor].erase(A);
			profesores[P].insert(A);
			it->second.profesor = P;
		}
	}

	bool es_alumno(Alumno A, Profesor P) {
		return profesores[P].count(A);
	}

	int puntuacion(Alumno A) {
		auto it = alumnos.find(A);
		if (it == alumnos.end())
			throw std::domain_error("El alumno A no esta matriculado");
		return it->second.puntos;
	}

	void actualizar(Alumno A, int N) {
		auto it = alumnos.find(A);
		if (it == alumnos.end())
			throw std::domain_error("El alumno A no esta matriculado");
		it->second.puntos += N;
	}

	std::list<Alumno> examen(Profesor P, int N) {
		std::list<Alumno> ret;
		auto it = profesores[P].begin();
		auto end = profesores[P].end();
		while (it != end) {
			Alumno a = *it;
			if (alumnos[a].puntos >= N) {
				ret.push_back(a);
			}
			++it;
		}
		return ret;
	}

	void aprobar(Alumno A) {
		auto it = alumnos.find(A);
		if (it == alumnos.end())
			throw std::domain_error("El alumno A no esta matriculado");
		Profesor p = it->second.profesor;
		alumnos.erase(it);
		profesores[p].erase(A);
	}

private:
	struct InfoAlumno {
		InfoAlumno() {};
		InfoAlumno(Profesor profesor, int puntos) : profesor(profesor), puntos(puntos) {};
		Profesor profesor;
		int puntos;
	};
	std::unordered_map<Profesor, std::set<Alumno>> profesores;
	std::unordered_map<Alumno, InfoAlumno> alumnos;
};

using namespace std;
bool resuelveCaso() {
	std::string orden, alumno, profesor;
	int punt;
	std::cin >> orden;
	if (!std::cin)
		return false;

	Autoescuela XD;	//No hagas caso a esto

	while (orden != "FIN") {
		try {
			if (orden == "alta") {
				cin >> alumno >> profesor;
				XD.alta(alumno, profesor);
			}
			else if (orden == "es_alumno") {
				cin >> alumno >> profesor;
				if (XD.es_alumno(alumno, profesor))
					cout << alumno << " es alumno de " << profesor << '\n';
				else
					cout << alumno << " no es alumno de " << profesor << '\n';
			}
			else if (orden == "examen") {
				cin >> profesor >> punt;
				list<std::string> alumnos = XD.examen(profesor, punt);
				cout << "Alumnos de " << profesor << " a examen:\n";
				auto it = alumnos.begin();
				while (it != alumnos.end()) {
					cout << *it << '\n';
					++it;
				}
			}
			else if (orden == "puntuacion") {
				cin >> alumno;
				punt = XD.puntuacion(alumno);
				cout << "Puntuacion de " << alumno << ": " << punt << '\n';
			}
			else if (orden == "actualizar") {
				cin >> alumno >> punt;
				XD.actualizar(alumno, punt);
			}
			else if (orden == "aprobar") {
				cin >> alumno;
				XD.aprobar(alumno);
			}
			else {
				//Nada
			}
		}
		catch (std::domain_error& e) {
			std::cout << "ERROR" << '\n';
		}
		std::cin >> orden;
	}
	std::cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}