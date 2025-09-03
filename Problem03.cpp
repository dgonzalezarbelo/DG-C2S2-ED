#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

class Hora {
public:

	Hora() {}

	Hora(int hora, int min, int seg) {
		this->seg = seg % 60;
		this->min = (min + (seg / 60)) % 60;
		this->hora = hora + (min + (seg / 60)) / 60;
	}

	Hora operator + (Hora const& hora1) const {
		Hora hora(this->hora + hora1.getHora(), this->min + hora1.getMin(), this->seg + hora1.getSeg());
	}

	bool operator < (Hora const& hora1) const {
		if (this->hora > hora1.hora) return false;
		else if (this->hora == hora1.hora) {
			if (this->min > hora1.min) return false;
			else if (this->min == hora1.min) {
				if (this->seg < hora1.seg) return true;
				else return false;
			}
			else return true;
		}
		else return true;
	}

	void setHora(int hora) {
		this->hora = hora;
	}

	void setMin(int min) {
		this->min = min;
	}

	void setSeg(int seg) {
		this->seg = seg;
	}

	int getHora() const {
		return this->hora;
	}

	int getMin() const {
		return this->min;
	}

	int getSeg() const {
		return this->seg;
	}

private:
	int hora;
	int min;
	int seg;

};

class Pelicula {
public:
	Pelicula(){}
	Pelicula(Hora ini, Hora d, std::string titulo) : tIni(ini.getHora(), ini.getMin(), ini.getSeg()), 
		duracion(d.getHora(), d.getMin(), d.getSeg()), 
		tFin({ini.getHora() + d.getHora(), ini.getMin() + d.getMin(), ini.getSeg() + d.getSeg()}) {
		this->titulo = titulo;
	}

	Hora getIni() const {
		return this->tIni;
	}

	Hora getDuracion() const {
		return this->duracion;
	}

	Hora getFin() const {
		return this->tFin;
	}

	std::string getTitulo() const {
		return this->titulo;
	}

private:
	Hora tIni;
	Hora duracion;
	Hora tFin;
	std::string titulo;
};

std::istream& operator >> (std::istream& in, Hora& hora) {
	int h, m, s;
	char aux;
	in >> h >> aux >> m >> aux >> s;
	hora.setHora(h);
	hora.setMin(m);
	hora.setSeg(s);
	return in;
}

std::ostream& operator << (std::ostream& out, Hora const& hora) {
	out << std::setfill('0') << std::setw(2) << hora.getHora() << ":" << std::setw(2) << hora.getMin() << ":" << std::setw(2) << hora.getSeg();
	return out;
}

struct ComparaPeli {
	bool operator()(Pelicula const& p1, Pelicula const& p2) {
		if (p1.getFin() < p2.getFin()) return true;
		else if (p2.getFin() < p1.getFin()) return false;
		else return p1.getTitulo() < p2.getTitulo();
	}
};

bool resuelveCaso() {
	int num;
	std::cin >> num;
	if (num == 0) return false;
	std::vector <Pelicula> v(num);
	Hora ini, d;
	std::string titulo;
	for (int i = 0; i < num; i++) {
		std::cin >> ini >> d;
		std::cin.ignore(2, ' ');
		std::getline(std::cin, titulo);
		v[i] = { ini, d, titulo };
	}
	std::sort(v.begin(), v.end(), ComparaPeli());
	for (int i = 0; i < num; i++) {
		std::cout << v[i].getFin() << ' ' << v[i].getTitulo() << '\n';
	}
	std::cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}