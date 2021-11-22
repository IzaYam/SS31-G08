#include "Lista.hpp"
#include "AVL.hpp"

struct Registro {
	string usuario;
	string destinatario;
	double monto;
	double tipo_cambio;
	Registro(string usuario, string destinatario, double monto, double tipo_cambio)
		: usuario(usuario), destinatario(destinatario), monto(monto), tipo_cambio(tipo_cambio) {}
};

int main() {
	Blockchain<Registro*> blockchain;
	vector<Registro*> block1;
	block1.push_back(new Registro("Aaron", "userA", 100, 4.05));
	block1.push_back(new Registro("Gabriel", "userC", 50, 4.05));
	block1.push_back(new Registro("Christian", "userA", 10, 4.05));
	blockchain.push_back(block1);
	vector<Registro*> block2;
	block2.push_back(new Registro("Estefano", "userC", 25, 4.10));
	block2.push_back(new Registro("Mathias", "userA", 15, 4.10));
	blockchain.push_back(block2);
	auto arbol = blockchain.crear_indice([](Registro* a, Registro* b) {
		return a->usuario.compare(b->usuario);
		});
	arbol->Print([](Registro* a) {
		return a->usuario + "; " + a->destinatario + "; " + to_string(a->monto) + "; " + to_string(a->tipo_cambio) + "\n";
		});
}
