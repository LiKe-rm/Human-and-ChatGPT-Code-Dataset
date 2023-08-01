#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <cassert>
#include "PruebasColaPrioridadInt.h"

class ColaPrioridadInt {
public:
    ColaPrioridadInt(int capacidad) {
        colaPrioridad.reserve(capacidad);
    }

    void agregar(int valor, int prioridad) {
        colaPrioridad.push(std::make_pair(prioridad, valor));
    }

    bool estaLlena() const {
        return colaPrioridad.size() == colaPrioridad.capacity();
    }

    int tamano() const {
        return colaPrioridad.size();
    }

    ColaPrioridadInt* clonar() const {
        ColaPrioridadInt* copia = new ColaPrioridadInt(colaPrioridad.capacity());
        copia->colaPrioridad = colaPrioridad;
        return copia;
    }

    void eliminar(int valor) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> temp;
        while (!colaPrioridad.empty()) {
            if (colaPrioridad.top().second != valor) {
                temp.push(colaPrioridad.top());
            }
            colaPrioridad.pop();
        }
        colaPrioridad = temp;
    }

    void mostrar() const {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> copia = colaPrioridad;
        while (!copia.empty()) {
            std::cout << "[" << copia.top().second << ", " << copia.top().first << "] ";
            copia.pop();
        }
        std::cout << std::endl;
    }

    ~ColaPrioridadInt() {
        while (!colaPrioridad.empty()) {
            colaPrioridad.pop();
        }
    }

private:
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> colaPrioridad;
};

void pruebasColaDePrioridadIntNoAcotada() {
    ColaPrioridadInt cola(10);

    cola.agregar(5, 1);
    cola.agregar(2, 2);
    cola.agregar(8, 3);
    cola.agregar(9, 0);
    cola.agregar(3, 3);

    assert(cola.estaLlena() == false);
    std::cout << "Cantidad de elementos en la cola: " << cola.tamano() << std::endl;

    ColaPrioridadInt* copia = cola.clonar();
    std::cout << "Elementos en la cola original: ";
    cola.mostrar();
    std::cout << "Elementos en la cola clonada: ";
    copia->mostrar();

    copia->agregar(10, 4);
    copia->eliminar(3);
    std::cout << "Elementos en la cola original después de modificar la cola clonada: ";
    cola.mostrar();
    std::cout << "Elementos en la cola clonada después de las modificaciones: ";
    copia->mostrar();

    cola.eliminar(2);
    cola.eliminar(8);
    std::cout << "Elementos en la cola original después de eliminar algunos elementos: ";
    cola.mostrar();

    delete copia;
}

void pruebasColaPrioridadInt() {
    std::cout << "Iniciando pruebas de ColaPrioridadInt..." << std::endl;
    pruebasColaDePrioridadIntNoAcotada();
    std::cout << "Pruebas de ColaPrioridadInt finalizadas." << std::endl;
}

int main() {
    pruebasColaPrioridadInt();
    return 0;
}

