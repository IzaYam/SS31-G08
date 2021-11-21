#pragma once
template<typename T>
struct Block {
	int nBloque, nonce;
	T elem;
	Block<T>* ant;
	Block<T>* sig;
	Block(T elemento, int nBloque) : elem(elemento), ant(nullptr), sig(nullptr), nBloque(nBloque) {
		nonce = rand() % 9999999 + 1;
	}
};
template <class T>
class Lista {
	Block<T>* inicio;
	Block<T>* fin;
	int size;
public:
	Lista() {
		inicio = fin = nullptr;
		size = 0;
	}
	
	void push_back(T elem) {
		if (size == 0) {
			inicio = fin = new Block<T>(elem, size+1);
			++size;
			return;
		}
		Block<T>* nuevo = new Block<T>(elem, size+1);
		fin->sig = nuevo;
		nuevo->ant = fin;
		fin = nuevo;
		++size;
	}

	void clear() {
		if (size == 0) return;
		Block<T>* aux;
		while (inicio != nullptr) {
			aux = inicio;
			inicio = inicio->sig;
			delete aux;
		}
		inicio = fin = nullptr;
		size = 0;
	}
};
