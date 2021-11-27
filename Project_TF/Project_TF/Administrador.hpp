#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include <sstream>

#include "Lista.hpp"
#include "AdministradorUsuarios.hpp"
#include "Menu.hpp"

using namespace std;
namespace fs = std::filesystem;

class Registro {
public:
	int transaction_id;
	int customer_id;
	int call_failure;
	int complains;
	int subscription_length;
	int frequency_use;

	Registro() {}

	string to_string() {
		string s = str(transaction_id) + "; " + str(customer_id) + "; " + str(call_failure) + "; ";
		s += (str(complains) + "; " + str(subscription_length) + "; " + str(frequency_use)) + "\n";
		return s;
	}

	friend ostream& operator<<(ostream& out, Registro& r) {
		out << r.to_string();
		return out;
	}

private:
	static string str(int n) {
		return std::to_string(n);
	}
};

class Administrador {
	Usuario* usuario_actual;
	Blockchain<Registro*> blockchain;
	ArbolBinario<Registro*>* call_failure_index = nullptr;
	ArbolBinario<Registro*>* subscription_length_index = nullptr;
	ArbolBinario<Registro*>* frequency_use_index = nullptr;

public:
	Administrador() {
		usuario_actual = nullptr;
	}

	void leer() {
		vector<Registro*> registros;

		fstream file("data\\dataset.csv", ios::in);

		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo.\n";
			exit(1);
		}

		string line;
		getline(file, line); // omitir el header

		while (getline(file, line)) {
			Registro* registro = new Registro();
			stringstream ss(line);
			string token;
			getline(ss, token, ',');
			registro->transaction_id = stoi(token);
			getline(ss, token, ',');
			registro->customer_id = stoi(token);
			getline(ss, token, ',');
			registro->call_failure = stoi(token);
			getline(ss, token, ',');
			registro->complains = stoi(token);
			getline(ss, token, ',');
			registro->subscription_length = stoi(token);
			getline(ss, token, ',');
			registro->frequency_use = stoi(token);
			registros.push_back(registro);
		}

		vector<Registro*> aux;
		int count = rand() % 11 + 1;
		int suma = 0;
		for (size_t i = 0; i < registros.size(); ++i) {
			aux.push_back(registros[i]);
			suma = registros[i]->call_failure + registros[i]->transaction_id + registros[i]->customer_id + registros[i]->complains + registros[i]->subscription_length + registros[i]->frequency_use;
			if (aux.size() > count) {
				blockchain.push_back(aux, suma);
				suma = 0;
				aux = vector<Registro*>();
				count = rand() % 11 + 1;
			}
		}
	}

	void crear_arboles() {
		call_failure_index = blockchain.crear_indice([](Registro* a, Registro* b) {
			if (a->call_failure < b->call_failure) return -1;
			if (a->call_failure > b->call_failure) return 1;
			return 0;
			});
		subscription_length_index = blockchain.crear_indice([](Registro* a, Registro* b) {
			if (a->subscription_length < b->subscription_length) return -1;
			if (a->subscription_length > b->subscription_length) return 1;
			return 0;
			});
		frequency_use_index = blockchain.crear_indice([](Registro* a, Registro* b) {
			if (a->frequency_use < b->frequency_use) return -1;
			if (a->frequency_use > b->frequency_use) return 1;
			return 0;
			});
	}

	void imprimir_arboles() {
		if (call_failure_index != nullptr) {
			call_failure_index->imprimir([](Registro* a) {
				return "Transaction: " + to_string(a->transaction_id) + ". " + to_string(a->call_failure) + "\n";
				});
		}
	}

	void menu_inicio() {
		Menu menu("\nBLOCKCHAIN\n");
		menu.crear_opcion("Iniciar sesion", [this]() {
			usuario_actual = AdministradorUsuarios::iniciar_sesion();
			menu_usuario();
			});
		menu.crear_opcion("Crear cuenta", [this]() {
			usuario_actual = AdministradorUsuarios::crear_usuario();
			menu_usuario();
			});
		menu.crear_opcion("Salir", []() {
			exit(0);
			});

		while (true) {
			menu.iniciar();
		}
	}

	void menu_usuario() {
		bool salir = false;

		string cabecera = "\nSesion iniciada: " + usuario_actual->get_nombre() + "\n";
		Menu menu(cabecera);
		menu.crear_opcion("Ver todas mis transacciones", [this]() {
			if (blockchain.get_size() == 0) {
				cout << endl << "No cuentas con ninguna transaccion." << endl;
				return;
			}
			cout << endl << "Listado de transacciones de " << usuario_actual->get_nombre() << ":" << endl;
			//mostrar datos de cada transaccion
			blockchain.for_each([this](Registro* a) {
				if (a->customer_id == usuario_actual->get_customer_ID()) {
					cout << "\nContenido de la transaccion numero " << a->transaction_id << ":\n\n";
					cout << *a;
				}
				});
			cout << endl;
			});
		menu.crear_opcion("Busqueda por: call failure", [this]() {
			int num;
			cout << "Ingresa numero a buscar: ";
			cin >> num;
			Registro* reg = new Registro();
			reg->call_failure = num;
			auto busqueda = call_failure_index->find(reg);
			delete reg;
			if (busqueda == nullptr) {
				cout << "No se encontro nada" << endl;
				return;
			}
			reg = *busqueda;
			cout << "\nContenido de la transaccion numero " << reg->transaction_id << ":\n\n";
			cout << *reg;
			});
		menu.crear_opcion("Busqueda por: subscription lenght", [this]() {
			int num;
			cout << "Ingresa numero a buscar: ";
			cin >> num;
			Registro* reg = new Registro();
			reg->subscription_length = num;
			auto busqueda = subscription_length_index->find(reg);
			delete reg;
			if (busqueda == nullptr) {
				cout << "No se encontro nada" << endl;
				return;
			}
			reg = *busqueda;
			cout << "\nContenido de la transaccion numero " << reg->transaction_id << ":\n\n";
			cout << *reg;
			});
		menu.crear_opcion("Busqueda por: frequency of use", [this]() {
			int num;
			cout << "Ingresa numero a buscar: ";
			cin >> num;
			Registro* reg = new Registro();
			reg->frequency_use = num;
			auto busqueda = frequency_use_index->find(reg);
			delete reg;
			if (busqueda == nullptr) {
				cout << "No se encontro nada" << endl;
				return;
			}
			reg = *busqueda;
			cout << "\nContenido de la transaccion numero " << reg->transaction_id << ":\n\n";
			cout << *reg;
			});
		menu.crear_opcion("Cerrar sesion", [this, &salir]() {
			delete usuario_actual;
			usuario_actual = nullptr;
			salir = true;
			});

		while (!salir) {
			menu.iniciar();
		}
	}
};
