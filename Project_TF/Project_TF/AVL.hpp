#pragma once
#include <functional>

template<typename T>
struct Nodo {
	T elem;
	Nodo<T>* izq;
	Nodo<T>* izq;
	Nodo<T>* padre;
	Nodo(T elem, Nodo* padre = nullptr, Nodo* izq = nullptr, Nodo* der = nullptr) :
		elem(elem), padre(padre), izq(izq), der(der) {}
};
template <class T>
class AVL {
	enum Rama { izquierda, derecha };
	Nodo<T>* raiz;
	Nodo<T>* actual;
	int altura;
public:
	AVL() {}
	void insertar(T elem, function<bool(T&,T&)> comparar) {
		Nodo<T>* padre = nullptr;
		if (raiz == nullptr) {
			padre = raiz = actual = new Nodo<T>(elem);
		}
		// true izq - false der
		else if (comparar(elem, padre->elem)) {
			padre->izq = new Nodo<T>(elem, padre);
			balancear(padre,izquierda);
		}
		else if (!comparar(elem, padre->elem)) {
			padre->der = new Nodo<T>(elem, padre);
			balancear(padre, derecha);
		}
	}
	void balancear(Nodo<T>* subarbol, Rama rama) {

	}
};
