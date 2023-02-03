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
  
  No te olvides del coste de las operaciones
*/
 
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1: Diego Martínez Moro
  Componente 2: Jorge Medina Carretero
*/


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>
#include <set>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//

istream & operator>>(istream &is, Direccion &dir) {
  string palabra; is >> palabra;
  if (palabra == "Norte") dir = Direccion::Norte;
  else if (palabra == "Sur") dir = Direccion::Sur;
  else if (palabra == "Este") dir = Direccion::Este;
  else if (palabra == "Oeste") dir = Direccion::Oeste;
  else throw std::domain_error("Lectura de direccion incorrecta");
  return is;
}

class pairHash {
public:
	size_t operator()(const pair<int, int>& k) const {
		return k.first * 10000 + k.second;
	}
};


class Desierto {
public:

  Desierto() { }
  
  void anyadir_torre(const string &nombre, int x, int y) { // O(log torresY) + O(log torresX)
	  auto coord = make_pair(x, y);

	  if (torres.count(nombre))
		  throw std::domain_error("Torre ya existente");
	  else if (coordenadas.count(coord))
		  throw std::domain_error("Posicion ocupada");
	  else {
		  torres.insert(make_pair(nombre, coord));
		  coordenadas.insert(make_pair(coord, nombre));

		  mapInsert(mapXY, x, y);
		  mapInsert(mapYX, y, x);
	  }
  }
  
  void eliminar_torre(const string &nombre) { // O(log torresY) + O(log torresX)
	  if (torres.count(nombre)) {
		  auto coord = torres.at(nombre);
		  
		  coordenadas.erase(coord);
		  torres.erase(nombre);

		  mapErase(mapXY, coord.first, coord.second);
		  mapErase(mapYX, coord.second, coord.first);
	  }  
	  else
		  throw domain_error("Torre no existente");
  }
  
  pair<bool, string> torre_en_posicion(int x, int y) const { // O(1)
	  auto coord = make_pair(x, y);
	  if (coordenadas.count(coord))
		  return make_pair(true, coordenadas.at(coord));
	  else
		  return make_pair(false, "");
  }

  pair<int, int> posicion(const string &nombre) const { // O(1)
	  if (torres.count(nombre))
		  return torres.at(nombre);
	  else
		  throw domain_error("Torre no existente");
  }
  
  string torre_mas_cercana(const string &nombre, const Direccion &dir) const { // O(log torresCoord)
	  if (torres.count(nombre)) {
		  auto coord = torres.at(nombre); //O(1)
		  auto torreEnDir = primeraTorreEnDir(coord, dir); // O(log torresCoord)
		  if (torreEnDir.first)
			  return torreEnDir.second;
		  else
			  throw domain_error("No hay torres en esa direccion");
	  }
	  else
		  throw domain_error("Torre no existente");
  }

private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados

	unordered_map<string, pair<int, int>> torres;
	unordered_map<pair<int, int>, string, pairHash> coordenadas;
	unordered_map<int, set<int>> mapXY, mapYX;

	void mapErase(unordered_map<int, set<int>> &map, int x, int y) { //O(log torresY) siendo torresY el numero de torres en el eje Y
		map.at(x).erase(y);
	}

	void mapInsert(unordered_map<int, set<int>>& map, int x, int y) { //O(log torresY) siendo torresY el numero de torres en el eje Y
		set<int> us;
		if (map.count(x))
			map.at(x).insert(y); // O(log torresY)
		else {
			us.insert(y); //O(1)
			map.insert(make_pair(x, us));
		}
	}

	pair <bool, string> primeraTorreEnDir(pair<int, int> coord, Direccion dir) const { //O(log torresCoord) siendo torresCoord el numero de torres en el eje X o Y de una coordenada x y
		bool encontrado = false;
		string res;
		if (dir == Direccion::Norte) {
			const auto &set = mapXY.at(coord.first); //O(1)
			auto it = set.find(coord.second); // O(log torresY)
			++it;
			if (it != set.end()) {
				res = coordenadas.at(make_pair(coord.first, *it)); //O(1)
				encontrado = true;
			}	
		}
		else if(dir == Direccion::Este){
			const auto& set = mapYX.at(coord.second);
			auto it = set.find(coord.first);
			++it;
			if (it != set.end()) {
				res = coordenadas.at(make_pair(*it, coord.second));
				encontrado = true;
			}	
		}
		else if (dir == Direccion::Sur) {
			const auto& set = mapXY.at(coord.first);
			auto it = set.find(coord.second);
			if (it != set.begin()) {
				--it;
				res = coordenadas.at(make_pair(coord.first, *it));
				encontrado = true;
			}				
		}
		else {
			const auto& set = mapYX.at(coord.second);
			auto it = set.find(coord.first);
			if (it != set.begin()) {
				--it;
				res = coordenadas.at(make_pair(*it, coord.second));
				encontrado = true;
			}	
		}
		return make_pair(encontrado, res);
	}
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() { //O(log torresX)
  // Implementar.
	Desierto d;
	string accion;
	cin >> accion;

	if (!cin)
		return false;

	while (accion != "FIN") {
		string nombre;
		int x, y;

		if (accion == "anyadir_torre") {
			cin >> nombre >> x >> y;
			
			try {
				d.anyadir_torre(nombre, x, y); // O(log torresX)
			}
			catch(exception &e){
				cout << e.what() << endl;
			}	
		}
		else if (accion == "torre_en_posicion") {
			cin >> x >> y;
			auto p = d.torre_en_posicion(x, y); //O(1)
			if (p.first)
				cout << "SI " << p.second << endl;
			else
				cout << "NO" << endl;
		}
		else if (accion == "posicion") {
			cin >> nombre;
			try {
				auto coord = d.posicion(nombre); //O(1)
				cout << coord.first << " " << coord.second << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			
		}
		else if (accion == "torre_mas_cercana") {
			Direccion dir;
			cin >> nombre >> dir;
			try {
				string torre = d.torre_mas_cercana(nombre, dir); //O(log torresX)
				cout << torre << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}	
		}
		else if (accion == "eliminar_torre") {
			cin >> nombre;
			try {
				d.eliminar_torre(nombre); //O(log torresX)
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
		}
	
		cin >> accion;
	}

	cout << "---" << endl;

	return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

