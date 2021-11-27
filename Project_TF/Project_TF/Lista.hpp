#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include "AVL.hpp"

using namespace std;

template<typename T>
class Block {
public:
	int hash, nBloque, nonce;
	vector<T> elem;
	Block<T>* ant;
	Block<T>* sig;

	Block(Block<T>* ant, vector<T>& elemento, int nBloque = 0, int suma = 0)
		: ant(ant), elem(elemento), sig(nullptr), nBloque(nBloque) {
		nonce = rand() % 89999 + 10000;
		setAtributos(suma);
	}

	void setAtributos(int n) {
		if (ant == nullptr) hash = (nBloque + nonce + n) % 10000000;
		else hash = (nBloque + nonce + n + ant->hash) % 10000000;
		//cout << hash << endl;
		//Esto es opcional, para que compruebes que los datos que salen son diferentes
		/*ofstream archivo;
		archivo.open("prueba.txt", ios::app);
		archivo << hash << endl;
		archivo.close();*/
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

	void push_back(vector<T> elem, int n) {
		if (size == 0) {
			inicio = fin = new Block<T>(nullptr, elem, size + 1, n);
			++size;
			return;
		}

		Block<T>* nuevo = new Block<T>(fin, elem, size + 1, n);
		fin->sig = nuevo;
		nuevo->ant = fin;
		fin = nuevo;
		++size;
	}

	ArbolBinario<T>* crear_indice(function<int(T, T)> fn) {
		ArbolBinario<T>* arbol = new ArbolBinario<T>(fn);
		Block<T>* aux = inicio;
		while (aux != nullptr) {
			for (T& elem : aux->elem) {
				arbol->insertar(elem, aux);
			}
			aux = aux->sig;
		}
		return arbol;
	}

	void for_each(function<void(T&)> fn) {
		Block<T>* aux = inicio;
		while (aux != nullptr) {
			for (T& elem : aux->elem) {
				fn(elem);
			}
			aux = aux->sig;
		}
	}

	int get_size() {
		return size;
	}
};
