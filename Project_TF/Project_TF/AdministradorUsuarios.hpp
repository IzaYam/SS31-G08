#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <regex>

#include "Validadores.hpp"

using namespace std;
namespace fs = std::filesystem;

class Usuario {
	string usuario;
public:
	Usuario(string usuario) : usuario(usuario) {}

	static bool validar_usuario(string usuario) {
		return std::regex_match(usuario, Validador::Usuario);
	}

	string get_nombre() {
		return usuario;
	}
};

class AdministradorUsuarios {
	AdministradorUsuarios() {}

	static fs::path get_ruta_config() {
		return fs::current_path() / "data" / "usuarios.txt";
	}

public:
	static Usuario* crear_usuario() {
		cout << "\nCreacion de cuenta nueva" << endl;
		string usuario;
		do {
			cout << "Usuario: ";
			cin >> usuario;
		} while (!Usuario::validar_usuario(usuario));
		return crear_usuario(usuario);
	}

	static Usuario* crear_usuario(string usuario) {
		fstream config(get_ruta_config(), ios::out | ios::app);
		config << usuario << "\n";
		config.close();

		return new Usuario(usuario);
	}

	static bool existe_usuario(string usuario) {
		fstream config(get_ruta_config(), ios::in);
		string registro, campo;
		while (getline(config, registro)) {
			stringstream am(registro);
			getline(am, campo, '\n');
			if (campo == usuario) return true;
		}
		return false;
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
			return crear_usuario(usuario);
		}

		return new Usuario(usuario);
	}
};
