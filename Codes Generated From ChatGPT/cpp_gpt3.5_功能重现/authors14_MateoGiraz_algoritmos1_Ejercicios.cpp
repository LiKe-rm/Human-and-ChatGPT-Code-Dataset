#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <list>

struct NodoABInt {
    int valor;
    NodoABInt* izquierda;
    NodoABInt* derecha;
};

using ListaOrdInt = std::list<int>;
using PilaInt = std::stack<int>;
using MultisetInt = std::multiset<int>;
using ColaPrioridadInt = std::priority_queue<int, std::vector<int>, std::greater<int>>;

void aplanar(NodoABInt* a, ListaOrdInt& l) {
    if (a == nullptr) {
        return;
    }

    aplanar(a->izquierda, l);
    l.push_back(a->valor);
    l.sort();
    aplanar(a->derecha, l);
}

ListaOrdInt Enlistar(NodoABInt* a) {
    ListaOrdInt l;
    aplanar(a, l);
    return l;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2) {
    l1.merge(l2);
    l1.sort();
    l1.unique();
    return l1;
}

bool EstaContenida(PilaInt p1, PilaInt p2) {
    while (!p1.empty()) {
        bool found = false;
        int elem = p1.top();
        p1.pop();

        PilaInt temp;
        while (!p2.empty()) {
            if (p2.top() == elem) {
                found = true;
            }
            temp.push(p2.top());
            p2.pop();
        }

        while (!temp.empty()) {
            p2.push(temp.top());
            temp.pop();
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

ListaOrdInt ObtenerRepetidos(MultisetInt m) {
    ListaOrdInt repetidos;
    for (const auto& elem : m) {
        if (m.count(elem) > 1) {
            repetidos.push_back(elem);
        }
    }

    repetidos.sort();
    repetidos.unique();
    return repetidos;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2) {
    MultisetInt resultado;
    for (const auto& elem : m1) {
        if (m2.count(elem) == 0) {
            resultado.insert(elem);
        }
    }

    for (const auto& elem : m2) {
        if (m1.count(elem) == 0) {
            resultado.insert(elem);
        }
    }

    return resultado;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
    if (c.empty()) {
        return c;
    }

    int menor = c.top();
    ColaPrioridadInt resultado;

    while (!c.empty()) {
        if (c.top() <= menor) {
            menor = c.top();
            resultado.push(menor);
        }
        c.pop();
    }

    return resultado;
}

int main() {
    // 请在此处编写您的测试代码以验证上述函数的正确性。

    return 0;
}
