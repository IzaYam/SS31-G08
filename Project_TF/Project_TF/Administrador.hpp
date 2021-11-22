#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <functional>
#include <vector>
#include <list>

#include "Lista.hpp"
#include "AdministradorUsuarios.hpp"
#include "Archivo.hpp"
#include "Menu.hpp"

using namespace std;
namespace fs = std::filesystem;

class Administrador {
	Usuario* usuario_actual;
	Lista<Archivo*> transacciones;

public:
	Administrador() {
		usuario_actual = nullptr;
	}

	void menu_inicio() {
		Menu menu("\nBLOCKCHAIN MAL HECHO :)\n");
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
		menu.crear_opcion("Hacer una nueva transaccion", [this]() {
				
			});
		menu.crear_opcion("Ver todas mis transacciones", [this]() {
			if (transacciones.getsize() == 0) {
				cout << endl << "No cuentas con ninguna transaccion." << endl;
				return;
			}
			cout << endl << "Listado de transacciones de " << usuario_actual << ":" << endl;
			int num = 1;
			while (num >= transacciones.getsize()) {
				//mostrar datos y contenido de cada transaccion
				Archivo transaccion_objetivo(crear_ruta_carpeta(usuario) / to_string(transacciones.hash_por_posicion(num)));
				cout << "\nContenido de la transaccion numero " << num << ":\n\n";
				transaccion_objetivo.leer([](string& linea) { cout << linea << endl; });
				++num;
			}
			cout << endl;
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
	//void mostrar_transacciones() {
	//	if (transacciones.getsize() == 0) {
	//		cout << endl << "No cuentas con ninguna transaccion." << endl;
	//		return;
	//	}
	//	cout << endl << "Listado de transacciones de " << usuario << ":" << endl;
	//	int num = 1;
	//	while (num >= transacciones.getsize()) {
	//		//mostrar datos y contenido de cada transaccion
	//		Archivo transaccion_objetivo(crear_ruta_carpeta(usuario) / to_string(transacciones.hash_por_posicion(num)));
	//		cout << "\nContenido de la transaccion numero " << num << ":\n\n";
	//		transaccion_objetivo.leer([](string& linea) { cout << linea << endl; });
	//		++num;
	//	}
	//	cout << endl;
	//}
};
