#pragma once
template<typename T>
struct block {
	T elem;
	block<T>* ant;
	block<T>* sig;
	block(T elem) { this->elem = elem; }
};
template <class T>
class Lista {
	block<T>* inicio;
	block<T>* fin;
	int size;
public:
	Lista() {
		inicio = fin = nullptr;
		size = 0;
	}
	
	void push_back(T elem) {
		if (size == 0) {
			inicio = fin = new block<T>(elem);
			++size;
			return;
		}
		block<T>* nuevo = new block<T>(elem);
		fin->sig = nuevo;
		nuevo->ant = fin;
		fin = nuevo;
		++size;

	}

	void clear() {
		if (size == 0) return;
		block<T>* aux;
		while (inicio != nullptr) {
			aux = inicio;
			inicio = inicio->sig;
			delete aux;
		}
		inicio = fin = nullptr;
		size = 0;
	}
};
