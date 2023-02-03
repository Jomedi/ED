/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Utiliza las librerías de la STL en esta práctica.

   No te olvides del coste.
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1: Diego Martínez Moro
   Componente 2: Jorge Medina Carretero
 */



 // Añade los include que necesites

#include <cassert>
#include <forward_list>
#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado la
// marca de fin de entrada
bool tratar_caso() { /*
    Coste = O(N) * O(C) + O(T) * O(J) siendo N el número de jugadores, siendo C el número de buques de cada jugador; Siendo T el número de ataques y siendo J el número de jugadores en una casilla
  */
  // Implementar.
    int N, C;
    cin >> N >> C;

    if (N == 0 && C == 0)
        return false;

    string casilla, nombre;
    unordered_map<string, unordered_set<string>> nomPosiciones;
    unordered_map<string, int> nomBuques;

    //Coste de inserción
    for (int i = 0; i < N; i++) { // Coste del bucle: O(N) siendo N el número de jugadores
        pair<string, unordered_set<string>> parNomPos;
        pair<string, int> parNomCont;
        parNomCont.second = C;

        cin >> nombre;
        parNomPos.second.insert(nombre); // O(1)

        for (int j = 0; j < C; j++) { // Coste del bucle: O(C) siendo C el número de buques de cada jugador
            cin >> casilla;
            parNomPos.first = casilla;

            if (nomPosiciones.count(casilla)) // O(1)
                nomPosiciones.at(casilla).insert(nombre); // O(1) + O(1)
            else
                nomPosiciones.insert(parNomPos); // O(1)
        }

        parNomCont.first = nombre;
        nomBuques.insert(parNomCont); // O(1)
    }

    int T;
    cin >> T;
    //Coste del algoritmo de resolución
    for (int i = 0; i < T; i++) { // O(T) Siendo T el número de ataques 
        cin >> nombre >> casilla;
        auto it = nomPosiciones.find(casilla); // O(1)
        bool encontrado = false, vencido = false;

        if (it != nomPosiciones.end()) { //O(1)
            auto it2 = it->second.begin(); //O(1)

            while (it2 != it->second.end()) { //O(J) siendo J el número de jugadores en una casilla, es decir numPoisiciones.find(casilla).size()
                if ((*it2) != nombre) {
                    encontrado = true;
                    int buques = --nomBuques.at(*it2); //O(1)

                    if (buques <= 0)
                        vencido = true;

                    auto aux = it2;
                    aux++;
                    it->second.erase(*it2); //O(1)
                    it2 = aux;
                }
                else
                    it2++;
            }
        }

        if (vencido)
            cout << "VENCIDO" << endl;
        else if (encontrado)
            cout << "HUNDIDO" << endl;
        else
            cout << "AGUA" << endl;
    }

    cout << "---" << endl;

    return true;
}


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