#include <iostream>
#include <cstdlib>
#include <cassert>

struct NodoListaIntDobleDato {
	int dato;
	unsigned int ocurrencias;
	NodoListaIntDobleDato* next;
};

struct _cabezalMultisetInt {
	NodoListaIntDobleDato* head;
	unsigned int size;
};

typedef _cabezalMultisetInt MultisetInt;

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

unsigned int ocurrencias(MultisetInt s, int e) {
	NodoListaIntDobleDato* current = s.head;
	while (current != nullptr) {
		if (current->dato == e) {
			return current->ocurrencias;
		}
		current = current->next;
	}
	return 0;
}

void crearMultisetInt(MultisetInt& s) {
	s.head = nullptr;
	s.size = 0;
}

void destruir(MultisetInt& s) {
	NodoListaIntDobleDato* current = s.head;
	while (current != nullptr) {
		NodoListaIntDobleDato* temp = current->next;
		delete current;
		current = temp;
	}
	s.head = nullptr;
	s.size = 0;
}

MultisetInt clon(MultisetInt s) {
	MultisetInt cloned;
	crearMultisetInt(cloned);
	NodoListaIntDobleDato* current = s.head;
	while (current != nullptr) {
		agregar(cloned, current->dato, current->ocurrencias);
		current = current->next;
	}
	return cloned;
}

void agregar(MultisetInt& s, int e, unsigned int ocurrencias) {
	NodoListaIntDobleDato* current = s.head;
	NodoListaIntDobleDato* prev = nullptr;
	while (current != nullptr && current->dato < e) {
		prev = current;
		current = current->next;
	}
	if (current != nullptr && current->dato == e) {
		current->ocurrencias += ocurrencias;
	}
	else {
		NodoListaIntDobleDato* newNode = new NodoListaIntDobleDato;
		newNode->dato = e;
		newNode->ocurrencias = ocurrencias;
		newNode->next = current;
		if (prev == nullptr) {
			s.head = newNode;
		}
		else {
			prev->next = newNode;
		}
	}
	s.size += ocurrencias;
}

void borrar(MultisetInt& s, int e) {
	NodoListaIntDobleDato* current = s.head;
	NodoListaIntDobleDato* prev = nullptr;
	while (current != nullptr && current->dato < e) {
		prev = current;
		current = current->next;
	}
	if (current != nullptr && current->dato == e) {
		if (prev == nullptr) {
			s.head = current->next;
		}
		else {
			prev->next = current->next;
		}
		s.size -= current->ocurrencias;
		delete current;
	}
}

bool pertenece(MultisetInt s, int e) {
	NodoListaIntDobleDato* current = s.head;
	while (current != nullptr && current->dato < e) {
		current = current->next;
	}
	return current != nullptr && current->dato == e;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt unionSet;
	crearMultisetInt(unionSet);
	NodoListaIntDobleDato* current1 = s1.head;
	NodoListaIntDobleDato* current2 = s2.head;
	while (current1 != nullptr && current2 != nullptr) {
		if (current1->dato < current2->dato) {
			agregar(unionSet, current1->dato, current1->ocurrencias);
			current1 = current1->next;
		}
		else if (current1->dato > current2->dato) {
			agregar(unionSet, current2->dato, current2->ocurrencias);
			current2 = current2->next;
		}
		else {
			agregar(unionSet, current1->dato, max(current1->ocurrencias, current2->ocurrencias));
			current1 = current1->next;
			current2 = current2->next;
		}
	}

	while (current1 != nullptr) {
		agregar(unionSet, current1->dato, current1->ocurrencias);
		current1 = current1->next;
	}

	while (current2 != nullptr) {
		agregar(unionSet, current2->dato, current2->ocurrencias);
		current2 = current2->next;
	}

	return unionSet;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt interseccionSet;
	crearMultisetInt(interseccionSet);
	NodoListaIntDobleDato* current1 = s1.head;
	NodoListaIntDobleDato* current2 = s2.head;
	while (current1 != nullptr && current2 != nullptr) {
		if (current1->dato < current2->dato) {
			current1 = current1->next;
		}
		else if (current1->dato > current2->dato) {
			current2 = current2->next;
		}
		else {
			agregar(interseccionSet, current1->dato, min(current1->ocurrencias, current2->ocurrencias));
			current1 = current1->next;
			current2 = current2->next;
		}
	}

	return interseccionSet;
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt diferenciaSet;
	crearMultisetInt(diferenciaSet);
	NodoListaIntDobleDato* current1 = s1.head;
	NodoListaIntDobleDato* current2 = s2.head;
	while (current1 != nullptr && current2 != nullptr) {
		if (current1->dato < current2->dato) {
			agregar(diferenciaSet, current1->dato, current1->ocurrencias);
			current1 = current1->next;
		}
		else if (current1->dato > current2->dato) {
			current2 = current2->next;
		}
		else {
			unsigned int diff_ocurrencias = current1->ocurrencias > current2->ocurrencias ? current1->ocurrencias - current2->ocurrencias : 0;
			if (diff_ocurrencias > 0) {
				agregar(diferenciaSet, current1->dato, diff_ocurrencias);
			}
			current1 = current1->next;
			current2 = current2->next;
		}
	}

	while (current1 != nullptr) {
		agregar(diferenciaSet, current1->dato, current1->ocurrencias);
		current1 = current1->next;
	}
	return diferenciaSet;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	NodoListaIntDobleDato* current1 = s1.head;
	NodoListaIntDobleDato* current2 = s2.head;
	while (current1 != nullptr && current2 != nullptr) {
		if (current1->dato < current2->dato) {
			return false;
		}
		else if (current1->dato > current2->dato) {
			current2 = current2->next;
		}
		else {
			if (current1->ocurrencias > current2->ocurrencias) {
				return false;
			}
			current1 = current1->next;
			current2 = current2->next;
		}
	}

	return current1 == nullptr;
}

int elemento(MultisetInt s) {
	assert(!esVacio(s));
	return s.head->dato;
}

bool esVacio(MultisetInt s) {
	return s.head == nullptr;
}

unsigned int cantidadElementos(MultisetInt s) {
	return s.size;
}

int main() {
	MultisetInt s;
	crearMultisetInt(s);
	agregar(s, 5, 2);
	agregar(s, 3, 1);
	agregar(s, 7, 3);
	agregar(s, 5, 1);
	borrar(s, 3);
	if (pertenece(s, 5)) {
		std::cout << "5 pertenece al conjunto" << std::endl;
	}
	if (pertenece(s, 3)) {
		std::cout << "3 pertenece al conjunto" << std::endl;
	}
	std::cout << "La cantidad de elementos en el conjunto es: " << cantidadElementos(s) << std::endl;

	MultisetInt s2;
	crearMultisetInt(s2);
	agregar(s2, 7, 1);
	agregar(s2, 5, 2);
	agregar(s2, 2, 1);

	MultisetInt unionSet = unionConjuntos(s, s2);
	MultisetInt interseccionSet = interseccionConjuntos(s, s2);
	MultisetInt diferenciaSet = diferenciaConjuntos(s, s2);

	std::cout << "La cantidad de elementos en el conjunto union es: " << cantidadElementos(unionSet) << std::endl;
	std::cout << "La cantidad de elementos en el conjunto interseccion es: " << cantidadElementos(interseccionSet) << std::endl;
	std::cout << "La cantidad de elementos en el conjunto diferencia es: " << cantidadElementos(diferenciaSet) << std::endl;

	destruir(s);
	destruir(s2);
	destruir(unionSet);
	destruir(interseccionSet);
	destruir(diferenciaSet);

	return 0;
}

