// PruebasListaOrdInt.h
#ifndef PRUEBAS_LISTA_ORD_INT_H
#define PRUEBAS_LISTA_ORD_INT_H

#include <iostream>

class ListaOrdInt {
public:
	ListaOrdInt();
	~ListaOrdInt();
	void agregar(int elem);
	int longitud() const;
	int minimo() const;
	int maximo() const;
	void eliminarMinimo();
	void eliminarMaximo();
	void eliminar(int elem);
	bool estaVacia() const;
	bool contiene(int elem) const;
	ListaOrdInt* clonar() const;
	void imprimir() const;

private:
	struct Nodo {
		int valor;
		Nodo* siguiente;
		Nodo(int val) : valor(val), siguiente(nullptr) {}
	};
	Nodo* cabeza;
	int _longitud;
};

#endif // PRUEBAS_LISTA_ORD_INT_H

// PruebasListaOrdInt.cpp
#include "PruebasListaOrdInt.h"

ListaOrdInt::ListaOrdInt() : cabeza(nullptr), _longitud(0) {}

ListaOrdInt::~ListaOrdInt() {
	Nodo* actual = cabeza;
	while (actual != nullptr) {
		Nodo* siguiente = actual->siguiente;
		delete actual;
		actual = siguiente;
	}
}

void ListaOrdInt::agregar(int elem) {
	Nodo* nuevo = new Nodo(elem);
	if (cabeza == nullptr || cabeza->valor > elem) {
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
	}
	else {
		Nodo* actual = cabeza;
		while (actual->siguiente != nullptr && actual->siguiente->valor < elem) {
			actual = actual->siguiente;
		}
		nuevo->siguiente = actual->siguiente;
		actual->siguiente = nuevo;
	}
	_longitud++;
}

int ListaOrdInt::longitud() const {
	return _longitud;
}

int ListaOrdInt::minimo() const {
	if (cabeza != nullptr) {
		return cabeza->valor;
	}
	throw std::runtime_error("Lista vacía");
}

int ListaOrdInt::maximo() const {
	if (cabeza != nullptr) {
		Nodo* actual = cabeza;
		while (actual->siguiente != nullptr) {
			actual = actual->siguiente;
		}
		return actual->valor;
	}
	throw std::runtime_error("Lista vacía");
}

void ListaOrdInt::eliminarMinimo() {
	if (cabeza != nullptr) {
		Nodo* temp = cabeza;
		cabeza = cabeza->siguiente;
		delete temp;
		_longitud--;
	}
}

void ListaOrdInt::eliminarMaximo() {
	if (cabeza != nullptr) {
		if (cabeza->siguiente == nullptr) {
			delete cabeza;
			cabeza = nullptr;
		}
		else {
			Nodo* actual = cabeza;
			while (actual->siguiente->siguiente != nullptr) {
				actual = actual->siguiente;
			}
			delete actual->siguiente;
			actual->siguiente = nullptr;
		}
		_longitud--;
	}
}

void ListaOrdInt::eliminar(int elem) {
	if (cabeza != nullptr) {
		if (cabeza->valor == elem) {
			Nodo* temp = cabeza;
			cabeza = cabeza->siguiente;
			delete temp;
			_longitud--;
		}
		else {
			Nodo* actual = cabeza;
			while (actual->siguiente != nullptr && actual->siguiente->valor < elem) {
				actual = actual->siguiente;
			}
			if (actual->siguiente != nullptr && actual->siguiente->valor == elem) {
				Nodo* temp = actual->siguiente;
				actual->siguiente = actual->siguiente->siguiente;
				delete temp;
				_longitud--;
			}
		}
	}
}

bool ListaOrdInt::estaVacia() const {
	return cabeza == nullptr;
}

bool ListaOrdInt::contiene(int elem) const {
	Nodo* actual = cabeza;
	while (actual != nullptr) {
		if (actual->valor == elem) {
			return true;
		}
		actual = actual->siguiente;
	}
	return false;
}

ListaOrdInt* ListaOrdInt::clonar() const {
	ListaOrdInt* clon = new ListaOrdInt();
	Nodo* actual = cabeza;
	while (actual != nullptr) {
		clon->agregar(actual->valor);
		actual = actual->siguiente;
	}
	return clon;
}

void ListaOrdInt::imprimir() const {
	Nodo* actual = cabeza;
	while (actual != nullptr) {
		std::cout << actual->valor << " ";
		actual = actual->siguiente;
	}
	std::cout << std::endl;
}

// Main.cpp
#include "PruebasListaOrdInt.h"

void pruebasListaOrdIntNoAcotada() {
	ListaOrdInt lista;
	lista.agregar(5);
	lista.agregar(3);
	lista.agregar(8);
	lista.agregar(2);
	lista.agregar(6);

	std::cout << "Lista: ";
	lista.imprimir();
	std::cout << "Longitud: " << lista.longitud() << std::endl;
	std::cout << "Minimo: " << lista.minimo() << std::endl;
	std::cout << "Maximo: " << lista.maximo() << std::endl;

	lista.eliminarMinimo();
	lista.eliminarMaximo();
	std::cout << "Lista despues de eliminar minimo y maximo: ";
	lista.imprimir();

	lista.eliminar(20); // No existe
	lista.eliminar(3);  // Existe
	std::cout << "Lista despues de eliminar 20 y 3: ";
	lista.imprimir();

	std::cout << "La lista esta vacia? " << (lista.estaVacia() ? "Si" : "No") << std::endl;
	std::cout << "La lista contiene 5? " << (lista.contiene(5) ? "Si" : "No") << std::endl;

	ListaOrdInt* clon = lista.clonar();
	std::cout << "Clon de la lista: ";
	clon->imprimir();
	delete clon;

	lista.eliminarMinimo();
	lista.eliminarMaximo();
	std::cout << "Lista despues de eliminar minimo y maximo nuevamente: ";
	lista.imprimir();

	lista.eliminarMinimo(); // Lista vacía
	lista.eliminarMaximo(); // Lista vacía
}

int main() {
	pruebasListaOrdIntNoAcotada();
	return 0;
}
