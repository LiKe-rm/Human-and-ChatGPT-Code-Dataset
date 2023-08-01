#include <iostream>
#include <queue>
#include <cassert>

class ColaInt {
public:
    ColaInt() = default;

    void encolar(int value) {
        queue.push(value);
    }

    void desencolar() {
        if (!queue.empty()) {
            queue.pop();
        }
    }

    int frente() const {
        if (!queue.empty()) {
            return queue.front();
        }
        return -1;
    }

    bool vacia() const {
        return queue.empty();
    }

    int tamano() const {
        return queue.size();
    }

    ColaInt clonar() const {
        return *this;
    }

    void vaciar() {
        std::queue<int> empty;
        std::swap(queue, empty);
    }

private:
    std::queue<int> queue;
};

void pruebasColaIntNoAcotada() {
    ColaInt cola;

    assert(cola.vacia());
    assert(cola.tamano() == 0);

    cola.encolar(1);
    assert(!cola.vacia());
    assert(cola.frente() == 1);

    assert(cola.tamano() == 1);

    cola.desencolar();
    assert(cola.vacia());
    assert(cola.tamano() == 0);

    cola.encolar(2);
    cola.encolar(3);

    ColaInt clon = cola.clonar();

    std::cout << "Clon: ";
    while (!clon.vacia()) {
        std::cout << clon.frente() << " ";
        clon.desencolar();
    }
    std::cout << std::endl;

    assert(clon.tamano() == 0);
    assert(cola.tamano() == 2);

    clon.encolar(4);
    clon.encolar(5);
    assert(clon.tamano() == 2);

    clon.desencolar();
    assert(clon.tamano() == 1);
    assert(clon.frente() == 5);

    clon.vaciar();
    assert(clon.vacia());
}

void pruebasColaInt() {
    pruebasColaIntNoAcotada();
}

int main() {
    pruebasColaInt();
    std::cout << "Todas las pruebas pasaron exitosamente." << std::endl;
    return 0;
}
