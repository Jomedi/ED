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
  Componente 2:	Jorge Medina Carretero
*/


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <list>

using namespace std;


class Spitter {
public:
  
  Spitter() { }
  
  void nueva_publicacion(int id, const string &texto, const vector<string> &hashtags) { // O(H1logH2) siendo H1 el número de hashtags en el vector hashtags y H2 pi.hashtags.size()
	  if(publicaciones.count(id))
		  throw std::domain_error("Identificador duplicado");
	  
		pubOrd.push_front(id);
		pubInfo pi;
		for (auto ht : hashtags) { //O(H1logH2) siendo H1 el número de hashtags en el vector hashtags y H2 pi.hashtags.size()
			pi.hashtags.insert(ht);
		}
		pi.texto = texto;
		pi.it = pubOrd.begin();
		publicaciones.insert({ id, pi });

		for (int i = 0; i < hashtags.size(); i++) { //O(H) siendo H = hashtags.size()
			if (hashtagPub.count(hashtags[i]))
				hashtagPub.at(hashtags[i])++;
			else 
				hashtagPub.insert({hashtags[i],1});
		}
  }
  
  void borrar_publicacion(int id) { //O(H)
	  if (publicaciones.count(id)) {
		  pubOrd.erase(publicaciones.at(id).it); //O(pub) siendo pub el numero de publicaciones de pubOrd

		  for (auto hashtag : publicaciones.at(id).hashtags) { //O(H)
			  if (hashtagPub.at(hashtag) <= 1)
				  hashtagPub.erase(hashtag);
			  else
				  hashtagPub[hashtag]--;
		  }

		  publicaciones.erase(id); //O(1)
	  }	  
  }

  
  vector<string> mas_recientes(int n) const { //O(n) siendo n el parámetro de entrada
	  vector<string> v;
	  int i = 0;
	  for (auto it = pubOrd.begin(); it != pubOrd.end() && i < n; it++) { //O(n) siendo n el parámetro de entrada
		  if (publicaciones.count(*it)) {
			  v.push_back(publicaciones.at(*it).texto);
			  i++;
		  }	
	  }
	  return v;
  }  

  vector<string> hashtags(int id) const { // O(H)
	  if (!publicaciones.count(id))
		  throw domain_error("Publicacion no existente");
	  vector<string> sol;
	  const auto &set = publicaciones.at(id).hashtags; //O(1)
	  for (auto ht : set) { // O(H)
		  sol.push_back(ht);
	  }
	  return sol; 
  }
  
  void anyadir_hashtag(int id, const string &hashtag) {
	  if (!publicaciones.count(id))
		  throw domain_error("Publicacion no existente");

	  publicaciones.at(id).hashtags.insert(hashtag); //O(logH)

	  if(hashtagPub.count(hashtag))
		hashtagPub[hashtag]++;
	  else 
		  hashtagPub.insert({ hashtag, 1 });
  }
  
  int popularidad(const string &hashtag) const {
	  if (hashtagPub.count(hashtag))
		  return hashtagPub.at(hashtag);
	  else
		  return 0;
  }
  
  
private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados

	struct pubInfo {
		string texto;
		set<string> hashtags;
		list<int>::iterator it;
	};
	unordered_map <int, pubInfo> publicaciones;
	list<int> pubOrd;
	unordered_map <string, int> hashtagPub;
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
  // Implementar.
	Spitter p;
	string accion;
	cin >> accion;

	if (!cin)
		return false;

	while (accion != "FIN") {

		if (accion == "nueva_publicacion") {
			int id;
			string texto, hashtagsLine, aux;
			vector<string> hashtags;

			cin >> id;
			cin.ignore();
			getline(cin, texto);
			getline(cin, hashtagsLine);

			stringstream s(hashtagsLine);
			
			while (s >> aux) {
				hashtags.push_back(aux);
			}

			try {
				p.nueva_publicacion(id, texto, hashtags); 
			}
			catch (exception& e) {
				cout << "ERROR: " << e.what() << endl;
			}
		}
		else if (accion == "mas_recientes") {
			int id;
			cin >> id;
			auto v = p.mas_recientes(id);
			cout << "Las " << v.size() << " publicaciones mas recientes:" << endl;
			for (int i = 0; i < v.size(); i++) {
				cout << "   " << v[i] << endl;
			}
		}
		else if (accion == "hashtags") {
			int id;
			cin >> id;
			try {
				auto v = p.hashtags(id);
				for (int i = 0; i < v.size(); i++) {
					cout << v[i] << " ";
				}
				cout << endl;
			}
			catch (exception& e) {
				cout << "ERROR: " << e.what() << endl;
			}

		}
		else if (accion == "anyadir_hashtag") {
			int id;
			string hashtag;
			cin >> id >> hashtag;
			try {
				p.anyadir_hashtag(id, hashtag);
			}
			catch (exception& e) {
				cout << "ERROR: " << e.what() << endl;
			}
		}
		else if (accion == "borrar_publicacion") {
			int id; 
			cin >> id;
			try {
				p.borrar_publicacion(id);
			}
			catch (exception& e) {
				cout << "ERROR: " << e.what() << endl;
			}
		}
		else if (accion == "popularidad") {
			string hashtag;
			cin >> hashtag;
			cout << p.popularidad(hashtag) << endl;
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

