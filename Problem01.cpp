#include <iostream>
#include <iomanip>
#include <vector>

class Hora {
public:

	Hora() {}

	Hora(int hora, int min, int seg) {
		this->hora = hora;
		this->min = min;
		this->seg = seg;
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

int resolver(std::vector <Hora> const& trenes, Hora const& hora, int ini, int fin) {
	if (ini >= fin - 1) {
		if (trenes[ini] < hora) return ini + 1;
		else return ini;
	}
	else {
		int m = (ini + fin - 1) / 2;
		if (trenes[m] < hora) return resolver(trenes, hora, m + 1, fin);
		else return resolver(trenes, hora, ini, m + 1);
	}
}

bool resuelveCaso() {
	int numTrenes, numHoras;
	std::cin >> numTrenes >> numHoras;
	if (numTrenes == 0 && numHoras == 0) return false;
	std::vector <Hora> trenes(numTrenes), horas(numHoras);
	for (int i = 0; i < numTrenes; i++) std::cin >> trenes[i];
	for (int i = 0; i < numHoras; i++) std::cin >> horas[i];
	int pos;
	for (int i = 0; i < numHoras; i++) {
		pos = resolver(trenes, horas[i], 0, trenes.size());
		if(pos == trenes.size()) std::cout << "NO\n";
		else std::cout << trenes[pos] << '\n';
	} 
	std::cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}