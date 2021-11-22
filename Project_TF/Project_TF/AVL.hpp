#pragma once

#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename T>
struct Hoja {
	Hoja<T>* izq = nullptr;
	Hoja<T>* der = nullptr;
	T valor;
	int altura = -1;
	Hoja(T valor) : valor(valor) {}
};

template <class T>
class ArbolBinario {
	typedef function<int(T, T)> CompararFn;
	typedef function<string(T)> StringifyFn;
	Hoja<T>* raiz;
	CompararFn comparar;

public:
	ArbolBinario(CompararFn comp)
		: comparar(comp), raiz(nullptr) {}

	void insertar(T v) {
		_insertar(v, raiz);
	}

	void imprimir(StringifyFn impresora) {
		_imprimir(impresora, raiz);
	}

private:
	void _imprimir(StringifyFn& stringifier, Hoja<T>*& nodo, string espacio = "") {
		if (nodo->izq != nullptr) {
			_imprimir(stringifier, nodo->izq, espacio + "  ");
		}
		cout << espacio << stringifier(nodo->valor);
		if (nodo->der != nullptr) {
			_imprimir(stringifier, nodo->der, espacio + "  ");
		}
	}

	void _insertar(T valor, Hoja<T>*& nodo) {
		if (nodo == nullptr) {
			nodo = new Hoja<T>(valor);
			return;
		}
		if (comparar(valor, nodo->valor) < 0) {
			_insertar(valor, nodo->izq);
		} else {
			_insertar(valor, nodo->der);
		}
		balancear(nodo);
	}

	void balancear(Hoja<T>*& nodo) {
		int diff = altura(nodo->izq) - altura(nodo->der);
		if (diff < -1) {
			int rrAltura = altura(nodo->der->der);
			int rlAltura = altura(nodo->der->izq);
			if (rlAltura > rrAltura) {
				rotacion_derecha(nodo->der);
			}
			return rotacion_izquierda(nodo);
		}
		if (diff > 1) {
			int llAltura = altura(nodo->izq->izq);
			int lrAltura = altura(nodo->izq->der);
			if (lrAltura > llAltura) {
				rotacion_izquierda(nodo->izq);
			}
			return rotacion_derecha(nodo);
		}
		actualizar_altura(nodo);
	}

	void rotacion_derecha(Hoja<T>*& nodo) {
		Hoja<T>* aux = nodo->izq;
		nodo->izq = aux->der;
		actualizar_altura(nodo);
		aux->der = nodo;
		actualizar_altura(aux);
		nodo = aux;
	}

	void rotacion_izquierda(Hoja<T>*& nodo) {
		Hoja<T>* aux = nodo->der;
		nodo->der = aux->izq;
		actualizar_altura(nodo);
		aux->izq = nodo;
		actualizar_altura(aux);
		nodo = aux;
	}

	void actualizar_altura(Hoja<T>*& nodo) {
		if (nodo != nullptr) {
			int AlturaDer = altura(nodo->der);
			int AlturaIzq = altura(nodo->izq);
			nodo->altura = max(AlturaDer, AlturaIzq) + 1;
		}
	}

	int altura(Hoja<T>*& nodo) {
		if (nodo == nullptr) return -1;
		return nodo->altura;
	}
};
