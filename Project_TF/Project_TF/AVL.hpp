#pragma once
#include <functional>
#include "Lista.hpp"

// Solo 2 templates
	// E para el elemento, T para el Registro
template<typename E, typename T>
struct Hoja {
	E elem;
	int FE; // factor equilibrio
	Hoja<E, T>* izq;
	Hoja<E, T>* der;
	Hoja<E, T>* padre;
	//Trabajemos con "Block" no "block" Apuntamos a un Block de registros
	Block<T>* bloquePadre;
	// El Registro que apuntamos, tipo T
	T* registro;
	Hoja(E elem, Hoja* padre = nullptr, Hoja* izq = nullptr, Hoja* der = nullptr) :
		elem(elem), padre(padre), izq(izq), der(der) {}
};

template<typename E, typename T>
class AVL {
	enum Rama { izquierda, derecha };
	Hoja<E, T>* raiz;
	Hoja<E, T>* actual;
	int altura;
public:
	AVL() { raiz = actual = nullptr; }

	void insertar(T elem, function<bool(T&, T&)> comparar) {
		Hoja<E, T>* padre = nullptr;
		actual = raiz;
		// mover el padre hasta el actual, manteniendo un puntero al nodo padre
		while (actual != nullptr) {
			padre = actual;
			//true - der / false - izq
			// elem > actual->elem
			if (comparar(elem, actual->elem)) actual = actual->der;
			// elem < actual->elem
			else if (!comparar(elem, actual->elem)) actual = actual->izq;
		}
		if (padre == nullptr) raiz = new Hoja<E, T>(elem);
		//true - der / false - izq
		// elem < padre->elem
		else if (!comparar(elem, padre->elem)) {
			padre->izq = new Hoja<E, T>(elem, padre);
			balancear(padre, izquierda, true);
		}
		// elem > padre->elem
		else if (comparar(elem, padre->elem)) {
			padre->der = new Hoja<E, T>(elem, padre);
			balancear(padre, derecha, true);
		}
	}

	void balancear(Hoja<E, T>* nodo, Rama rama, bool agregar) {
		bool salir = false;
		while (nodo != nullptr && !salir) {
			if (agregar)
				if (rama == izquierda) nodo->FE--;
				else nodo->FE++;
			if (nodo->FE == 0) salir = true; // La altura de las rama que empieza en nodo no ha variado
			else if (nodo->FE == -2) { // Rotar a derecha
				if (nodo->izq->FE == 1) RDD(nodo);
				else RSD(nodo);
				salir = true;
			}
			else if (nodo->FE == 2) {  // Rotar a izquierda
				if (nodo->der->FE == -1) RDI(nodo);
				else RSI(nodo);
				salir = true;
			}
			if (nodo->padre != nullptr) {
				if (nodo->padre->der == nodo) rama = derecha;
				else rama = izquierda;
			}
			nodo = nodo->padre;
		}
	}

	// Rotación doble a derecha
	void RDD(Hoja<E, T>* nodo) {
		Hoja<E, T>* Padre = nodo->padre;
		Hoja<E, T>* P = nodo;
		Hoja<E, T>* Q = P->izq;
		Hoja<E, T>* R = Q->der;
		Hoja<E, T>* B = R->izq;
		Hoja<E, T>* C = R->der;

		if (Padre) {
			if (Padre->der == nodo) Padre->der = R;
			else Padre->izq = R;
		}
		else raiz = R;

		Q->der = B;
		P->izq = C;
		R->izq = Q;
		R->der = P;

		R->padre = Padre;
		P->padre = Q->padre = R;
		if (B) B->padre = Q;
		if (C) C->padre = P;

		switch (R->FE) {
		case -1: Q->FE = 0; P->FE = 1; break;
		case 0:  Q->FE = 0; P->FE = 0; break;
		case 1:  Q->FE = -1; P->FE = 0; break;
		}
		R->FE = 0;
	}

	// Rotación doble a izquierdas
	void RDI(Hoja<E, T>* nodo) {
		Hoja<E, T>* Padre = nodo->padre;
		Hoja<E, T>* P = nodo;
		Hoja<E, T>* Q = P->der;
		Hoja<E, T>* R = Q->izq;
		Hoja<E, T>* B = R->izq;
		Hoja<E, T>* C = R->der;

		if (Padre)
			if (Padre->der == nodo) Padre->der = R;
			else Padre->izq = R;
		else raiz = R;

		P->der = B;
		Q->izq = C;
		R->izq = P;
		R->der = Q;

		R->padre = Padre;
		P->padre = Q->padre = R;
		if (B) B->padre = P;
		if (C) C->padre = Q;

		switch (R->FE) {
		case -1: P->FE = 0; Q->FE = 1; break;
		case 0:  P->FE = 0; Q->FE = 0; break;
		case 1:  P->FE = -1; Q->FE = 0; break;
		}
		R->FE = 0;
	}

	// Rotación simple a derecha
	void RSD(Hoja<E, T>* nodo) {
		Hoja<E, T>* Padre = nodo->padre;
		Hoja<E, T>* P = nodo;
		Hoja<E, T>* Q = P->izq;
		Hoja<E, T>* B = Q->der;

		if (Padre)
			if (Padre->der == P) Padre->der = Q;
			else Padre->izq = Q;
		else raiz = Q;

		P->izq = B;
		Q->der = P;

		P->padre = Q;
		if (B) B->padre = P;
		Q->padre = Padre;

		P->FE = 0;
		Q->FE = 0;
	}

	// Rotación simple a izquierda
	void RSI(Hoja<E, T>* nodo) {
		Hoja<E, T>* Padre = nodo->padre;
		Hoja<E, T>* P = nodo;
		Hoja<E, T>* Q = P->der;
		Hoja<E, T>* B = Q->izq;

		if (Padre)
			if (Padre->der == P) Padre->der = Q;
			else Padre->izq = Q;
		else raiz = Q;

		P->der = B;
		Q->izq = P;

		P->padre = Q;
		if (B) B->padre = P;
		Q->padre = Padre;

		P->FE = 0;
		Q->FE = 0;
	}

	//bool temporalmente, cambiar para que devuelva el nodo o valor o etc.
	void buscar(T elem, function<bool(T&, T&)> comparar) {
		actual = raiz;
		while (actual != nullptr) {
			if (elem == actual->elem) cout << "Si está en árbol"; //return true;
			//elem > actual->elem
			else if (comparar(elem, actual->elem)) actual = actual->der;
				//elem < actual->elem
			else if (!comparar(elem, actual->elem)) actual = actual->izq;
		}
		cout << "No está en árbol";
		//return false; // No está en árbol
	}
};
