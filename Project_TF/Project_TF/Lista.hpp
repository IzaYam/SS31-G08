#pragma once
#include <time.h>
#include<fstream>
using namespace std;
template<typename T>
struct Block {
	//Agregado el valor hash del nodo
	int hash, nBloque, nonce;
	T elem;
	Block<T>* ant;
	Block<T>* sig;
	//Ahora te pide el nodo anterior para sacarle su hash y usarlo para la cosntruccion
	Block(Block* ant, T elemento, int nBloque = 0) : ant(ant), elem(elemento), sig(nullptr), nBloque(nBloque){
		//Llamamos metodo cuando construye
		setAtributos();
	}
	void setAtributos() {
		nonce = rand() % 89999 + 10000;
		if (ant == nullptr) hash = (nBloque + nonce + elem) % 10000000;
		else hash = (nBloque + nonce + elem + ant->hash) % 10000000;
		cout << hash << endl;
		//Esto es opcional, para que compruebes que los datos que salen son diferentes
			// Se hizo una prueba con "List<int> una_lista_de_enteros"
			ofstream archivo;
			archivo.open("prueba.txt", ios::app);
			archivo << hash<<endl;
			archivo.close();
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
			//Se agrego un nodo nulp al inicio
			inicio = fin = new Block<T>(nullptr,elem, size + 1);
			++size;
			return;
		}
		//Aca con el fin
		Block<T>* nuevo = new Block<T>(fin,elem, size + 1);
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
