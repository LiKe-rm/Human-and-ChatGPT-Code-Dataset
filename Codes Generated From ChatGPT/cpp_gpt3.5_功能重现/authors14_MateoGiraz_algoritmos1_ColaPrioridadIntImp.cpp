#include <iostream>

struct Nodo {
    int valor;
    int prioridad;
    Nodo* siguiente;
    Nodo* anterior;
};

struct ColaPrioridadInt {
    Nodo* cabeza;
    Nodo* cola;
    unsigned int cantidad;
    unsigned int cota;
};

ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
    ColaPrioridadInt c;
    c.cabeza = nullptr;
    c.cola = nullptr;
    c.cantidad = 0;
    c.cota = cota;
    return c;
}

bool esVacia(ColaPrioridadInt c) {
    return c.cantidad == 0;
}

bool esLlena(ColaPrioridadInt c) {
    return c.cantidad >= c.cota;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
    return c.cantidad;
}

void encolar(ColaPrioridadInt& c, int e, int p) {
    if (esLlena(c)) {
        std::cout << "La cola de prioridad está llena. No se puede agregar el elemento." << std::endl;
        return;
    }

    Nodo* nuevo_nodo = new Nodo;
    nuevo_nodo->valor = e;
    nuevo_nodo->prioridad = p;
    nuevo_nodo->siguiente = nullptr;
    nuevo_nodo->anterior = nullptr;

    if (esVacia(c)) {
        c.cabeza = nuevo_nodo;
        c.cola = nuevo_nodo;
    } else {
        Nodo* actual = c.cabeza;
        while (actual != nullptr && actual->prioridad >= p) {
            actual = actual->siguiente;
        }

        if (actual == nullptr) {
            nuevo_nodo->anterior = c.cola;
            c.cola->siguiente = nuevo_nodo;
            c.cola = nuevo_nodo;
        } else if (actual->anterior == nullptr) {
            nuevo_nodo->siguiente = c.cabeza;
            c.cabeza->anterior = nuevo_nodo;
            c.cabeza = nuevo_nodo;
        } else {
            nuevo_nodo->siguiente = actual;
            nuevo_nodo->anterior = actual->anterior;
            actual->anterior->siguiente = nuevo_nodo;
            actual->anterior = nuevo_nodo;
        }
    }
    c.cantidad++;
}

int principio(ColaPrioridadInt c) {
    if (esVacia(c)) {
        std::cerr << "La cola de prioridad está vacía." << std::endl;
        exit(1);
    }
    return c.cabeza->valor;
}

int principioPrioridad(ColaPrioridadInt c) {
    if (esVacia(c)) {
        std::cerr << "La cola de prioridad está vacía." << std::endl;
        exit(1);
    }
    return c.cabeza->prioridad;
}

void desencolar(ColaPrioridadInt& c) {
    if (esVacia(c)) {
        std::cout << "La cola de prioridad está vacía. No se puede desencolar." << std::endl;
        return;
    }

    Nodo* temp = c.cabeza;
    c.cabeza = c.cabeza->siguiente;

    if (c.cabeza != nullptr) {
        c.cabeza->anterior = nullptr;
    } else {
        c.cola = nullptr;
    }

    delete temp;
    c.cantidad--;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
    ColaPrioridadInt copia = crearColaPrioridadInt(c.cota);
    Nodo* actual = c.cabeza;

    while (actual != nullptr) {
        encolar(copia, actual->valor, actual->prioridad);
        actual = actual->siguiente;
    }

    return copia;
}

void destruir(ColaPrioridadInt& c) {
    while (!esVacia(c)) {
        desencolar(c);
    }
}

int main() {
    ColaPrioridadInt mi_cola = crearColaPrioridadInt(5);
    encolar(mi_cola, 5, 1);
    encolar(mi_cola, 3, 3);
    encolar(mi_cola, 7, 0);
    encolar(mi_cola, 2, 4);

    std::cout << "Elemento en el frente de la cola: " << principio(mi_cola) << std::endl;
    std::cout << "Prioridad del elemento en el frente de la cola: " << principioPrioridad(mi_cola) << std::endl;

    ColaPrioridadInt copia_cola = clon(mi_cola);
    desencolar(mi_cola);

    std::cout << "Elemento en el frente de la cola después de desencolar: " << principio(mi_cola) << std::endl;

    std::cout << "Elemento en el frente de la copia de la cola: " << principio(copia_cola) << std::endl;

    destruir(mi_cola);
    destruir(copia_cola);

    return 0;
}

