#include <iostream>
#include <cmath>

class Complejo {
public:
	Complejo() {
		this->pReal = 0;
		this->pImaginaria = 0;
	}

	Complejo(double a, double b) : pReal(a), pImaginaria(b) {

	}

	Complejo operator+(Complejo const & c) const {
		return Complejo(this->pReal + c.getParteReal(), this->pImaginaria + c.getParteIm());
	}

	Complejo operator*(Complejo const& c) const {
		return Complejo(this->pReal * c.getParteReal() - this->pImaginaria * c.getParteIm(), this->pReal * c.getParteIm() + this->pImaginaria * c.getParteReal());
	}

	double getParteReal() const {
		return this->pReal;
	}

	double getParteIm() const {
		return this->pImaginaria;
	}

	double modulo() const {
		return std::sqrt(this->pReal * this->pReal + this->pImaginaria * this->pImaginaria);
	}

private:
	double pReal;
	double pImaginaria;
};

bool resolver(Complejo const& c, int iteraciones) {
	bool diverge = false;
	int i = 1;
	Complejo z(0, 0);
	while (!diverge && i <= iteraciones) {
		z = z * z + c;
		if (z.modulo() > 2) diverge = true;
		i++;
	}
	return diverge;
}

void resuelveCaso() {
	double a, b;
	int iteraciones;
	std::cin >> a >> b >> iteraciones;
	Complejo c(a, b);
	resolver(c, iteraciones) ? std::cout << "NO\n" : std::cout << "SI\n";
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; i++) resuelveCaso();
	return 0;
}