#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <regex>

#include "Lista.hpp"
#include "Archivo.hpp"
#include "Validadores.hpp"

using namespace std;
namespace fs = std::filesystem;

class Usuario {
	string usuario;
	fs::path ruta_carpeta;
	Lista<Archivo*> archivos;

public:
	Usuario(string usuario)
		: usuario(usuario) {
		ruta_carpeta = crear_ruta_carpeta(usuario);
		leer_carpeta();
	}

	void leer_carpeta() {
		archivos.clear();
		for (const auto& file : fs::directory_iterator(ruta_carpeta)) {
			Archivo* archivo = new Archivo(file.path());
			archivos.push_back(archivo);
		}
	}

	static bool validar_usuario(string usuario) {
		return std::regex_match(usuario, Validador::Usuario);
	}

	static fs::path crear_ruta_carpeta(string usuario) {
		return fs::current_path() / "data" / usuario;
	}
};
