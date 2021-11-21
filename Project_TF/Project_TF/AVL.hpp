#pragma once
#include <functional>
#include "Lista.hpp"

template<typename T, typename R, typename C>
struct Hoja {
	T elem;
	int FE; // factor equilibrio

	//Hoja tiene 3 templates asi que faltaban ponerlos, asi en todas
	Hoja<T,R,C>* izq;
	Hoja<T,R,C>* der;
	Hoja<T,R,C>* padre;

	//Trabajemos con "Block" no "block" Apuntamos a un Block de registros
	Block<R>* Block;
	// Apuntamos a un solo registro
	R* registro;
	//Esto no lo toque
	Hoja(T elem, Hoja* padre = nullptr, Hoja* izq = nullptr, Hoja* der = nullptr) :
		elem(elem), padre(padre), izq(izq), der(der) {}
};

template<typename T, typename R, typename C>
class AVL {
	enum Rama { izquierda, derecha };
	// Aqui tambien añadimos los 3 templates
	Hoja<T, R, C>* raiz;
	Hoja<T, R, C>* actual;
	int altura;
public:
	AVL() { raiz = actual = nullptr; }

	void insertar(T elem, function<bool(T&, T&)> comparar) {
		Hoja<T, R, C>* padre = nullptr;
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
		if (padre == nullptr) raiz = new Hoja<T>(elem);
		//true - der / false - izq
		// elem < padre->elem
		else if (!comparar(elem, padre->elem)) {
			padre->izq = new Hoja<T>(elem, padre);
			balancear(padre, izquierda, true);
		}
		// elem > padre->elem
		else if (comparar(elem, padre->elem)) {
			padre->derecho = new Hoja<T>(elem, padre);
			balancear(padre, derecha, true);
		}
	}

	void balancear(Hoja<T, R, C>* nodo, Rama rama, bool agregar) {
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
	void RDD(Hoja<T, R, C>* nodo) {
		Hoja<T, R, C>* Padre = nodo->padre;
		Hoja<T, R, C>* P = nodo;
		Hoja<T, R, C>* Q = P->izq;
		// Cambie el R por el J, era mas facil cambiar solo el template xddd
		Hoja<T, R, C>* J = Q->der;
		Hoja<T, R, C>* B = J->izq;
		// Cambiamos el C por el D para evitar colision con los templates, repito, era mas sencillo cambiar el template uu
		Hoja<T, R, C>* D = J->der;

		if (Padre) {
			if (Padre->der == nodo) Padre->der = J;
			else Padre->izq = J;
		}
		else raiz = J;

		Q->der = B;
		P->izq = D;
		J->izq = Q;
		J->der = P;

		J->padre = Padre;
		P->padre = Q->padre = J;
		if (B) B->padre = Q;
		if (D) D->padre = P;

		switch (J->FE) {
		case -1: Q->FE = 0; P->FE = 1; break;
		case 0:  Q->FE = 0; P->FE = 0; break;
		case 1:  Q->FE = -1; P->FE = 0; break;
		}
		J->FE = 0;
	}

	// Rotación doble a izquierdas
	void RDI(Hoja<T, R, C>* nodo) {
		// Lo mismo por aca, Recordar que "J" es "R" en realidad, habria que cambiarlo
		Hoja<T, R, C>* Padre = nodo->padre;
		Hoja<T, R, C>* P = nodo;
		Hoja<T, R, C>* Q = P->derecho;
		Hoja<T, R, C>* J = Q->izquierdo;
		Hoja<T, R, C>* B = J->izquierdo;
		Hoja<T, R, C>* D = J->derecho;

		if (Padre)
			if (Padre->derecho == nodo) Padre->derecho = J;
			else Padre->izquierdo = J;
		else raiz = J;

		P->der = B;
		Q->izq = D;
		J->izq = P;
		J->der = Q;

		J->padre = Padre;
		P->padre = Q->padre = J;
		if (B) B->padre = P;
		if (D) D->padre = Q;

		switch (J->FE) {
		case -1: P->FE = 0; Q->FE = 1; break;
		case 0:  P->FE = 0; Q->FE = 0; break;
		case 1:  P->FE = -1; Q->FE = 0; break;
		}
		J->FE = 0;
	}

	// Rotación simple a derecha
	void RSD(Hoja<T, R, C>* nodo) {
		//Aqui si no hice nada creo
		Hoja<T, R, C>* Padre = nodo->padre;
		Hoja<T, R, C>* P = nodo;
		Hoja<T, R, C>* Q = P->izq;
		Hoja<T, R, C>* B = Q->der;

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
	void RSI(Hoja<T, R, C>* nodo) {
		// Aqui tampoco
		Hoja<T, R, C>* Padre = nodo->padre;
		Hoja<T, R, C>* P = nodo;
		Hoja<T, R, C>* Q = P->der;
		Hoja<T, R, C>* B = Q->izq;

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
			
			//Aqui faltaba un parentesis!!!!!!!
			else if (comparar(elem, actual->elem)) actual = actual->der;
				//elem < actual->elem
			else if (!comparar(elem, actual->elem)) actual = actual->izq;
		}
		return false; // No está en árbol
	}
};
