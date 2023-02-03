/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aquí los nombres de los componentes del grupo:

    Componente 1: JORGE MEDINA CARRETERO
    Componente 2: DIEGO MARTÍNEZ MORO
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>

using namespace std;

enum class Categoria { Primero, Segundo, Postre };

struct Plato {
    Categoria categoria;
    string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream& operator<<(ostream& out, const Plato& plato) {
    switch (plato.categoria) {
    case Categoria::Primero:
        out << "1";
        break;
    case Categoria::Segundo:
        out << "2";
        break;
    case Categoria::Postre:
        out << "P";
        break;
    }
    out << " " << plato.nombre;
    return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------


//Indica el coste en función del parámetro de entrada
void ordenar_menu(list<Plato>& platos) {
    auto it = platos.begin();
    auto it2 = ++platos.begin();



    for (int i = 0; i < platos.size() - 1; i++) {
        if (it2->categoria == Categoria::Primero && it->categoria == Categoria::Segundo) {
            Plato p = *it2;
            it2 = platos.erase(it2);
            platos.insert(it, p);
        }
        else if (it->categoria == Categoria::Postre) {
            Plato p = *it;
            it = platos.erase(it);
            platos.insert(platos.end(), p);
            it2++;
        }
        else {
            it++;
            it2++;
        }
    }
}   


bool tratar_caso() {
    int n;
    cin >> n;

    if (n == 0)
        return false;

    while (n != 0) {

        list<Plato> platos;
        char entrada;

        for (int i = 0; i < n; i++) {

            Plato plato;
            cin >> entrada;

            if (entrada == 'P')
                plato.categoria = Categoria::Postre;
            else if (entrada == '1')
                plato.categoria = Categoria::Primero;
            else if (entrada == '2')
                plato.categoria = Categoria::Segundo;


            char espace[1];
            cin.getline(espace, 1, ' ');

            char aux[1000];
            cin.getline(aux, 1000, '\n');

            plato.nombre = aux;

            platos.push_back(plato);
        }

        ordenar_menu(platos);

        for (auto it = platos.begin(); it != platos.end(); it++) {
            cout << *it << endl;
        }

        cout << "---" << endl;

        cin >> n;
        if (n == 0)
            return false;
    }
    // Introduce aquí el código para tratar un caso de prueba.
    // Devuelve false si ya no hay más casos de prueba que leer,
    // true en caso contrario.
    return true;
}


//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}