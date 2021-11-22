#pragma once
 
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <functional>
#include <regex>

#include "Lista.hpp"
#include "Validadores.hpp"

using namespace std;
namespace fs = std::filesystem;

class Archivo {
	fs::path ruta;

public:
	Archivo(fs::path ruta) : ruta(ruta) {}
	Archivo(fs::path ruta, fs::path carpeta_padre) {
		this->ruta = carpeta_padre / ruta;
	}

	fs::path get_ruta() {
		return ruta;
	}

	void leer(function<void(string&)> fun) {
		std::fstream archivo(ruta, ios::in);
		if (archivo.is_open()) {
			string str;
			while (getline(archivo, str)) {
				fun(str);
			}
		}
		archivo.close();
	}

	bool escribir(string& contenido) {
		std::fstream archivo(ruta, ios::out | ios::app);
		if (!archivo.is_open()) return false;
		archivo << contenido;
		archivo.close();
		return true;
	}
};
