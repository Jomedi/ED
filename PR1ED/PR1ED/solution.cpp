/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  Introduce aquí los nombres de los componentes del grupo:

  Componente 1: Jorge Medina Carretero
  Componente 2: Diego Martínez Moro
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_ELEMS = 2000;


class Multiconjunto {
public:
    // Implementa las operaciones necesarias.
    // -------------------------------------------------------> No olvides el coste! <------------------------------------------------------

    Multiconjunto() { // constructor: crea un multiconjunto vacío
        num_elems = 0;
    }

    void anyadir(int elem) { // añade un elemento al multiconjunto Coste: O(n)
        int i = busquedaBinaria(0, num_elems, elem);
        if (i < num_elems) {
            if (elems[i].valor == elem)
                elems[i].multiplicidad++;
            else {
                if (num_elems < MAX_ELEMS) {
                    num_elems++; // AÑADIMOS UN ELEMENTO MÁS A LA LISTA
                    for (int j = num_elems - 1; j > i; j--) {
                        elems[j] = elems[j - 1];    // SE DESPLAZAN LOS VALORES DE LOS ELEMENTOS AL ELEMENTO SIGUIENTE Y LA ÚLTIMA POSICIÓN OCUPA UNA POSICIÓN QUE ANTES ERA VACÍA
                    }
                    elems[i].multiplicidad = 1;
                    elems[i].valor = elem;
                }
            }
        }
        else {
            if (num_elems < MAX_ELEMS) {
                num_elems++; // AÑADIMOS UN ELEMENTO MÁS A LA LISTA
                elems[i].multiplicidad = 1;
                elems[i].valor = elem;
            }
        }
    }

    void eliminar(int elem) { // elimina un elemento del multiconjunto. Coste: O(n)
        int i = busquedaBinaria(0, num_elems, elem);
        if (i < num_elems) {
            if (elems[i].valor == elem) {
                if (elems[i].multiplicidad > 1)
                    elems[i].multiplicidad--;
                else {
                    for (int j = i; j < num_elems; j++) {
                        elems[j] = elems[j + 1];    // SE SOBRESCRIBEN LOS VALORES DE LOS ELEMENTOS POR EL ELEMENTO SIGUIENTE Y EL ULTIMO ES SUSTITUIDO POR UNA POSICION CON UN STRUCT VACIO
                    }
                    num_elems--;
                }
            }
        }
    }

    bool pertenece(int elem) { // comprueba si un elemento está en el multiconjunto. Coste: O(log(num_elems))
        int i = busquedaBinaria(0, num_elems, elem);

        if (i < num_elems)
            if (elems[i].valor == elem)
                return true;
            
        return false;
    }

private:
    struct Elem {
        int valor;
        int multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    int num_elems;

    int busquedaBinaria(int ini, int fin, int c) { // realiza una búsqueda binaria del elemento c. Coste: O(log(num_elems))
        if (ini == fin - 1 || ini == fin) {
            if (elems[ini].valor >= c)
                return ini;
            else
                return fin;
        }
        else {
            int m = (fin + ini) / 2;
            if (elems[m].valor < c)
                return busquedaBinaria(m + 1, fin, c);
            else
                return busquedaBinaria(ini, m, c);
        }
    }
};


// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
bool tratar_caso() {
    // Implementar
    int n_elem;

    std::cin >> n_elem;

    if (n_elem != 0) {
        vector<int> secreto(n_elem), intento(n_elem);
        vector <char> solucion(n_elem);
        Multiconjunto m;
        int elem;

        for (int i = 0; i < n_elem; i++) {
            std::cin >> elem;
            m.anyadir(elem);
            secreto[i] = elem;
        }

        for (int i = 0; i < n_elem; i++) {
            std::cin >> elem;
            intento[i] = elem;
        }

        for (int i = 0; i < n_elem; i++) {
            if (secreto[i] == intento[i]) {
                solucion[i] = '#';
                m.eliminar(secreto[i]);
            }
            else
                solucion[i] = '.';
        }

        for (int i = 0; i < n_elem; i++) {
            elem = intento[i];
            if (solucion[i] == '.') {
                if (m.pertenece(elem)) {
                    solucion[i] = 'O';
                    m.eliminar(elem);
                }
            }
        }

        for (int i = 0; i < n_elem; i++) {
            cout << solucion[i];
        }

        cout << endl;
        return true;
    }
    else
        return false;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar en Windows si la consola se cierra inmediatamente
    // system("PAUSE");
#endif
    return 0;
}