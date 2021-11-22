#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <regex>

#include "Validadores.hpp"

using namespace std;
namespace fs = std::filesystem;

class AdministradorUsuarios;

class Usuario {
	string usuario;
	int customer_ID;
public:
	Usuario(string usuario) : usuario(usuario) {
		fstream config(AdministradorUsuarios::get_ruta_config(), ios::in);
		string registro, campo;
		getline(config, registro);
		while (getline(config, registro)) {
			stringstream am(registro);
			getline(am, campo, ',');
			customer_ID = stoi(campo);
			getline(am, campo, ',');
			if (campo == usuario) break;
		}
	}
	Usuario(string usuario, int customer_ID) : usuario(usuario), customer_ID(customer_ID) {}

	static bool validar_usuario(string usuario) {
		return std::regex_match(usuario, Validador::Usuario);
	}

	string get_nombre() {
		return usuario;
	}
};

class AdministradorUsuarios {
	AdministradorUsuarios() {}

public:
	static fs::path get_ruta_config() {
		return fs::current_path() / "data" / "users.csv";
	}

	static Usuario* crear_usuario() {
		cout << "\nCreacion de cuenta nueva" << endl;
		string usuario;
		do {
			cout << "Usuario: ";
			cin >> usuario;
		} while (!Usuario::validar_usuario(usuario));
		return crear_usuario(usuario, cantidad_Customers() + 1);
	}

	static Usuario* crear_usuario(string usuario, int customer_ID) {
		fstream config(get_ruta_config(), ios::out | ios::app);
		config << customer_ID << "," << usuario << "\n";
		config.close();

		return new Usuario(usuario, customer_ID);
	}

	static bool existe_usuario(string usuario) {
		fstream config(get_ruta_config(), ios::in);
		string registro, campo;
		getline(config, registro);
		while (getline(config, registro)) {
			stringstream am(registro);
			getline(am, campo, ',');
			getline(am, campo, ',');
			if (campo == usuario) return true;
		}
		return false;
	}

	static int cantidad_Customers() {
		int cantidad;
		fstream config(get_ruta_config(), ios::in);
		string registro;
		getline(config, registro);
		while (getline(config, registro)) {
			++cantidad;
		}
		return cantidad;
	}

	static Usuario* iniciar_sesion() {
		cout << "\nInicio de sesion" << endl;
		string usuario;
		do {
			cout << "Usuario: ";
			cin >> usuario;
		} while (!Usuario::validar_usuario(usuario));

		if (!existe_usuario(usuario)) {
			cout << "Usuario no registrado." << endl;
			char opcion = 'n';
			do {
				cout << "\nDeseas crear tu cuenta? (S/N): ";
				cin >> opcion;
				opcion = tolower(opcion);
			} while (opcion != 's' && opcion != 'n');
			if (opcion == 'n') {
				exit(0);
			}
			return crear_usuario(usuario, cantidad_Customers() + 1);
		}

		return new Usuario(usuario);
	}
};
