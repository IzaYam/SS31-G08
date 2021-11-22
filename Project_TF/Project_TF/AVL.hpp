#pragma once

#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename T>
struct Hoja {
	Hoja<T>* left = nullptr;
	Hoja<T>* right = nullptr;
	T value;
	int height = -1;
	Hoja(T value) : value(value) {}
};

template <class T>
class BinaryTree {
	typedef function<int(T, T)> ComparerFn;
	typedef function<string(T)> StringifyFn;
	Hoja<T>* root;
	ComparerFn comparer;

public:
	BinaryTree(ComparerFn comp)
		: comparer(comp), root(nullptr) {}

	void Insert(T v) {
		_Insert(v, root);
	}

	void Print(StringifyFn printer) {
		_Print(printer, root);
	}

private:
	void _Print(StringifyFn& stringifier, Hoja<T>*& node, string space = "") {
		if (node->left != nullptr) {
			_Print(stringifier, node->left, space + "  ");
		}
		cout << space << stringifier(node->value);
		if (node->right != nullptr) {
			_Print(stringifier, node->right, space + "  ");
		}
	}

	void _Insert(T value, Hoja<T>*& node) {
		if (node == nullptr) {
			node = new Hoja<T>(value);
			return;
		}
		if (comparer(value, node->value) < 0) {
			_Insert(value, node->left);
		} else {
			_Insert(value, node->right);
		}
		Balance(node);
	}

	void Balance(Hoja<T>*& node) {
		int diff = Height(node->left) - Height(node->right);
		if (diff < -1) {
			int rrHeight = Height(node->right->right);
			int rlHeight = Height(node->right->left);
			if (rlHeight > rrHeight) {
				HoraryRotation(node->right);
			}
			return AntihoraryRotation(node);
		}
		if (diff > 1) {
			int llHeight = Height(node->left->left);
			int lrHeight = Height(node->left->right);
			if (lrHeight > llHeight) {
				AntihoraryRotation(node->left);
			}
			return HoraryRotation(node);
		}
		UpdateHeight(node);
	}

	void HoraryRotation(Hoja<T>*& node) {
		Hoja<T>* aux = node->left;
		node->left = aux->right;
		UpdateHeight(node);
		aux->right = node;
		UpdateHeight(aux);
		node = aux;
	}

	void AntihoraryRotation(Hoja<T>*& node) {
		Hoja<T>* aux = node->right;
		node->right = aux->left;
		UpdateHeight(node);
		aux->left = node;
		UpdateHeight(aux);
		node = aux;
	}

	void UpdateHeight(Hoja<T>*& node) {
		if (node != nullptr) {
			int rightHeight = Height(node->right);
			int leftHeight = Height(node->left);
			node->height = max(rightHeight, leftHeight) + 1;
		}
	}

	int Height(Hoja<T>*& node) {
		if (node == nullptr) return -1;
		return node->height;
	}
};
