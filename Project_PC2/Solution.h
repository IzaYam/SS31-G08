#include <iostream>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template<class valor, class key>
class HashEntidad {
private:
	key key_;
	valor value_;
public:
	HashEntidad(key key, valor value) {
		this->key_ = key;
		this->value_ = value;
	}
	key getKey() { return key_; }
	valor getValue() { return value_; }
};


template<class valor, class key>
class HashTable {
private:
	HashEntidad<valor, key>** tabla;
	int n_elementos;
	int max;

public:

	HashTable(int tamanho = 128) {
		this->max = tamanho;
		tabla = new HashEntidad<valor, key>*[tamanho];
		for (int i = 0; i < tamanho; ++i) {
			tabla[i] = nullptr;
		}
		n_elementos = 0;
	}
	~HashTable()
	{
		for (int i = 0; i < max; ++i) {
			if (tabla[i] != nullptr) {
				delete tabla[i];
			}
		}
		delete[] tabla;
	}
	void insertar(key key_, valor value) {
		int base, step;
		int hash = key_ % max;
		if (n_elementos == max)return;
		base = key_ % max;
		hash = base;
		step = 0;
		while (tabla[hash] != nullptr)
		{
			hash = (base + step) % max;
			step++;
		}
		tabla[hash] = new HashEntidad<valor, key>(key_, value);
		n_elementos++;
	}
	int size() {
		return max;
	}
	int sizeactual() {
		return n_elementos;
	}
	int buscar(key key) {
		int step = 0;
		int i, base;
		i = base = key % max;
		while (true)
		{
			if (tabla[i] == nullptr)return -1;
			else if (tabla[i]->getKey() == key) {
				return i;
			}
			else step++;
			i = (base + step) % max;
		}
	}
	void print() {
		for (int i = 1; i < max; i++)
		{
			cout << "Key: " << tabla[i]->getKey() << " Valor: " << tabla[i]->getValue();
		}
	}
	// METODOS 
	void For_each(int Inicio, int fin) {
		for (int i = Inicio; i < fin; i++)
		{
			cout << "Key: " << tabla[i]->getKey() << " Valor: " << tabla[i]->getValue();
		}
	}
	void Partition(int Inicio, int fin, function<bool(int)>f) {
		vector<valor> vec;
		for (int i = Inicio; i < fin; i++)
		{
			if (f(tabla[i]->getValue().getCustomerID())) {
				vec.push_back(tabla[i]->getValue());
			}
		}
		for (int i = 0; i < vec.size(); i++)
		{
			cout << vec[i] << " ";
		}
	}
	void Find_if(int Inicio, int fin, function<bool(int)>f) {
		for (int i = Inicio; i < fin; i++)
		{
			if (f(tabla[i]->getValue().AgeGroup())) {
				cout << (tabla[i]->getValue());
				break;
			}
		}
	}
	void Find_first_of(int Inicio, int fin) {
		//El primer objeto del hashtable que tenga el mismo Grupo de edad que otro
		bool encontrado = false;
		for (int j = Inicio; j < fin; j++) {
			for (size_t i = j + 1; i < fin - 1; i++) {
				if (tabla[j]->getValue().AgeGroup() == tabla[i]->getValue().AgeGroup()) {
					encontrado = true;
					cout << "El objeto " << tabla[j]->getValue() << " tiene el mismo grupo de edad que el objeto \n"
						<< tabla[i]->getValue() << "el cual es " << tabla[i]->getValue().AgeGroup() << endl;
					break;
				}
			}if (encontrado)
				break;
		}
	}
	void copy_if(int Inicio, int fin, function<bool(int)>f) {
		vector<valor> vec;
		for (int i = Inicio; i < fin; i++)
		{
			if (f(tabla[i]->getValue().GetSeconds_Use())) {
				vec.push_back(tabla[i]->getValue());
			}
		}
		cout << "Los que tienen menos de 1000 segundos de uso son : " << endl;
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i] << " ";
		}
	}
	void adjacent_find(int Inicio, int fin) {
		for (int j = Inicio; j < fin; j++) {
			for (size_t i = j + 1; i < fin - 1; i++) {
				if (tabla[j]->getValue() == tabla[i]->getValue()) {
					cout << "El objeto " << tabla[j]->getValue() << " tiene el mismo valor que el objeto \n" << tabla[i]->getValue() << endl;
					break;
				}
				else
				{
					cout << "no se encontraron dos objetos exactamente igual en la hashtable" << endl;
				}
			}
		}
	}
};