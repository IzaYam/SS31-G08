#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include "AVL.hpp"

using namespace std;

template<typename T>
struct Block {
	int hash, nBloque, nonce;
	vector<T> elem;
	Block<T>* ant;
	Block<T>* sig;

	Block(Block<T>* ant, vector<T>& elemento, int nBloque = 0)
		: ant(ant), elem(elemento), sig(nullptr), nBloque(nBloque) {
		nonce = rand() % 89999 + 10000;
		setAtributos();
	}

	void setAtributos() {
		if (ant == nullptr) hash = (nBloque + nonce) % 10000000;
		else hash = (nBloque + nonce + ant->hash) % 10000000;
		//cout << hash << endl;
		//Esto es opcional, para que compruebes que los datos que salen son diferentes
		// Se hizo una prueba con "List<int> una_lista_de_enteros"
		ofstream archivo;
		archivo.open("prueba.txt", ios::app);
		archivo << hash << endl;
		archivo.close();
	}
};

template <class T>
class Blockchain {
	Block<T>* inicio;
	Block<T>* fin;
	int size;
public:
	Blockchain() {
		inicio = fin = nullptr;
		size = 0;
	}

	void push_back(vector<T> elem) {
		if (size == 0) {
			inicio = fin = new Block<T>(nullptr, elem, size + 1);
			++size;
			return;
		}

		Block<T>* nuevo = new Block<T>(fin, elem, size + 1);
		fin->sig = nuevo;
		nuevo->ant = fin;
		fin = nuevo;
		++size;
	}

	BinaryTree<T>* crear_indice(function<int(T, T)> fn) {
		BinaryTree<T>* arbol = new BinaryTree<T>(fn);
		Block<T>* aux = inicio;
		while (aux != nullptr) {
			for (T& elem : aux->elem) {
				arbol->Insert(elem);
			}
			aux = aux->sig;
		}
		return arbol;
	}

	void clear() {
		if (size == 0) return;
		Block<T>* aux = nullptr;
		while (inicio != nullptr) {
			aux = inicio;
			inicio = inicio->sig;
			delete aux;
		}
		inicio = fin = nullptr;
		size = 0;
	}

	int get_size() {
		return size;
	}

	int hash_por_posicion(size_t p) {
		Block<T>* aux = inicio;
		size_t pos = 0;
		if (pos > size && pos < 0) {
			while (pos < p) {
				aux = aux->sig;
				++pos;
			}
			return aux->hash;
		}
		exit(1);
	}
};
