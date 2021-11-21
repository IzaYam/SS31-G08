#pragma once
#include <functional>
#include "Lista.hpp"

template<typename T, typename R, typename B>
struct Hoja {
	T elem;
	int FE; // factor equilibrio
	Hoja<T>* izq;
	Hoja<T>* der;
	Hoja<T>* padre;
	block<R>* Block;
	B<R>* registro;
	Hoja(T elem, Hoja* padre = nullptr, Hoja* izq = nullptr, Hoja* der = nullptr) :
		elem(elem), padre(padre), izq(izq), der(der),  {}
};

template <class T>
class AVL {
	enum Rama { izquierda, derecha };
	Hoja<T>* raiz;
	Hoja<T>* actual;
	int altura;
public:
	AVL() { raiz = actual = nullptr; }

	void insertar(T elem, function<bool(T&,T&)> comparar) {
		Hoja<T>* padre = nullptr;
		actual = raiz;
		// mover el padre hasta el actual, manteniendo un puntero al nodo padre
		while (actual != nullptr) {
			padre = actual;
			//true - der / false - izq
			// elem > actual->elem
			if (comparar(elem,actual->elem)) actual = actual->der;
			// elem < actual->elem
			else if (!comparar(elem, actual->elem)) actual = actual->izq;
		}
		if (padre == nullptr) raiz = new Hoja<T>(elem);
		//true - der / false - izq
		// elem < padre->elem
		else if (!comparar(elem,padre->elem)) {
			padre->izq = new Hoja<T>(elem, padre);
			balancear(padre, izquierda, true);
		}
		// elem > padre->elem
		else if (comparar(elem, padre->elem)) {
			padre->derecho = new Hoja<T>(elem, padre);
			balancear(padre, derecha, true);
		}
	}

	void balancear(Hoja<T>* nodo, Rama rama, bool agregar) {
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
	void RDD(Hoja<T>* nodo) {
		Hoja<T>* Padre = nodo->padre;
		Hoja<T>* P = nodo;
		Hoja<T>* Q = P->izq;
		Hoja<T>* R = Q->der;
		Hoja<T>* B = R->izq;
		Hoja<T>* C = R->der;

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
	void RDI(Nodo* nodo) {
		Nodo* Padre = nodo->padre;
		Nodo* P = nodo;
		Nodo* Q = P->derecho;
		Nodo* R = Q->izquierdo;
		Nodo* B = R->izquierdo;
		Nodo* C = R->derecho;

		if (Padre)
			if (Padre->derecho == nodo) Padre->derecho = R;
			else Padre->izquierdo = R;
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
	void RSD(Nodo* nodo) {
		Nodo* Padre = nodo->padre;
		Nodo* P = nodo;
		Nodo* Q = P->izq;
		Nodo* B = Q->der;

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
	void RSI(Nodo* nodo) {
		Nodo* Padre = nodo->padre;
		Nodo* P = nodo;
		Nodo* Q = P->der;
		Nodo* B = Q->izq;

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
	bool buscar(T elem, function<bool(T&, T&)> comparar) {
		actual = raiz;
		while (actual != nullptr) {
			if (elem == actual->elem) return true; 
			//elem > actual->elem
			else if (comparar(elem,actual->elem) actual = actual->der;
			//elem < actual->elem
			else if (!comparar(elem, actual->elem)) actual = actual->izq;
		}
		return false; // No está en árbol
	}
};
