#include <iostream>
#include <stack>
#include <cassert>

class PilaInt {
public:
    PilaInt() = default;

    bool vacia() const {
        return pila.empty();
    }

    size_t tamano() const {
        return pila.size();
    }

    void push(int valor) {
        pila.push(valor);
    }

    int top() const {
        assert(!vacia());
        return pila.top();
    }

    void pop() {
        assert(!vacia());
        pila.pop();
    }

    PilaInt clonar() const {
        return PilaInt(*this);
    }

    ~PilaInt() = default;

private:
    std::stack<int> pila;
};

class PruebaConcreta {
public:
    void ver3(bool condicion, const std::string& mensaje) {
        if (!condicion) {
            std::cerr << "Fallo: " << mensaje << std::endl;
            fallos++;
        }
    }

    void mostrarResultados() {
        std::cout << "Total de fallos: " << fallos << std::endl;
    }

private:
    int fallos = 0;
};

void pruebasPilaInt() {
    PruebaConcreta prueba;

    // Crear una pila vacía
    PilaInt pila;
    prueba.ver3(pila.vacia(), "La pila debería estar vacía al inicio");
    prueba.ver3(pila.tamano() == 0, "La pila debería tener tamaño 0 al inicio");

    // Agregar elementos a la pila
    pila.push(1);
    pila.push(2);
    pila.push(3);
    prueba.ver3(!pila.vacia(), "La pila no debería estar vacía después de agregar elementos");
    prueba.ver3(pila.tamano() == 3, "La pila debería tener tamaño 3 después de agregar elementos");
    prueba.ver3(pila.top() == 3, "El elemento en la parte superior de la pila debería ser 3");

    // Remover elementos de la pila
    pila.pop();
    prueba.ver3(pila.tamano() == 2, "La pila debería tener tamaño 2 después de eliminar un elemento");
    prueba.ver3(pila.top() == 2, "El elemento en la parte superior de la pila debería ser 2");

    // Clonar la pila
    PilaInt pilaClonada = pila.clonar();
    prueba.ver3(pila.tamano() == pilaClonada.tamano(), "La pila clonada debería tener el mismo tamaño que la pila original");
    prueba.ver3(pila.top() == pilaClonada.top(), "La pila clonada debería tener el mismo elemento superior que la pila original");

    // Modificar la pila clonada y verificar que la pila original no se vea afectada
    pilaClonada.push(4);
    prueba.ver3(pilaClonada.tamano() == 3, "La pila clonada debería tener tamaño 3 después de agregar un elemento");
    prueba.ver3(pila.tamano() == 2, "El tamaño de la pila original no debería verse afectado después de agregar un elemento a la pila clonada");
    prueba.ver3(pila.top() == 2, "El elemento superior de la pila original no debería verse afectado después de agregar un elemento a la pila clonada");

    // Mostrar los resultados de las pruebas
    prueba.mostrarResultados();
}

int main() {
    pruebasPilaInt();
    return 0;
}