#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct struttura {
    float distanza;
    float magnitudo;
    string nome;
    string costellazione;
    string colore;
};

int compara_1(const void *a, const void *b) {
    struttura *struttura_a = (struttura *)a;
    struttura *struttura_b = (struttura *)b;

    if (struttura_a->magnitudo < struttura_b->magnitudo) return -1;
    if (struttura_a->magnitudo > struttura_b->magnitudo) return 1;
    if (struttura_a->distanza < struttura_b->distanza) return -1;
    if (struttura_a->distanza > struttura_b->distanza) return 1;
    return 0;
}

int compara_2(const void *a, const void *b) {
    // 根据需要修改比较方法
}

int compara_3(const void *a, const void *b) {
    // 根据需要修改比较方法
}

int compara_4(const void *a, const void *b) {
    // 根据需要修改比较方法
}

void stampa_struttura(struttura *stelle, int num_stelle) {
    for (int i = 0; i < num_stelle; i++) {
        cout << "Nome: " << stelle[i].nome << endl;
        cout << "Distanza: " << stelle[i].distanza << endl;
        cout << "Magnitudo: " << stelle[i].magnitudo << endl;
        cout << "Costellazione: " << stelle[i].costellazione << endl;
        cout << "Colore: " << stelle[i].colore << endl;
        cout << endl;
    }
}

int ricerca_binaria(struttura *stelle, int num_stelle, const string &nome) {
    int inizio = 0;
    int fine = num_stelle - 1;

    while (inizio <= fine) {
        int mezzo = (inizio + fine) / 2;
        if (stelle[mezzo].nome == nome) return mezzo;
        if (stelle[mezzo].nome < nome) inizio = mezzo + 1;
        else fine = mezzo - 1;
    }

    return -1;
}

int main() {
    struttura stelle[] = {
        // 创建八个不同的星体
    };

    int num_stelle = sizeof(stelle) / sizeof(stelle[0]);

    qsort(stelle, num_stelle, sizeof(struttura), compara_1);
    cout << "Stelle ordinate per magnitudo e distanza:" << endl;
    stampa_struttura(stelle, num_stelle);

    // 按照其他排序方式排序
    // ...

    string nome_cercato = "Sirio";
    int posizione = ricerca_binaria(stelle, num_stelle, nome_cercato);

    if (posizione != -1) {
        cout << "Informazioni sulla stella " << nome_cercato << ":" << endl;
        cout << "Nome: " << stelle[posizione].nome << endl;
        cout << "Distanza: " << stelle[posizione].
            distanza << endl;
        cout << "Magnitudo: " << stelle[posizione].magnitudo << endl;
        cout << "Costellazione: " << stelle[posizione].costellazione << endl;
        cout << "Colore: " << stelle[posizione].colore << endl;
    } else {
        cout << "La stella " << nome_cercato << " non e' stata trovata." << endl;
    }

    return 0;
}