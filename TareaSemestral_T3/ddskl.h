#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <chrono>
using namespace std;



class Sol{
public:
	
	u_char** v;
	int length;		// capacidad
	int numWord; 	// num palabras

	Sol();
	virtual ~Sol();
	int ucharCompare(const u_char* str1, const u_char* str2);
	void destroyArray(u_char* v);
	int searchArray(const u_char* word);
	bool elimArray(const u_char* word);
	bool insertArray(const u_char* word);
    void printArray();
	void redimension();
	
};

struct nodoG {
    u_char* key;
    nodoG* next;
    nodoG* up;
};

typedef struct nodoG nodo;


class Sol2 {
public:
    int L;          // Número de niveles
    nodo** G;       // Grilla de nodos

    Sol2(int level);
	nodo* searchG(const u_char* key);
    bool insertG(u_char* word);
  	void printG(nodo* L);
    int compareG(const u_char* word1, const u_char* word2);
};


// Estructura que representa un nodo del árbol
struct Node {
    string key;     		// Clave del nodo
    Node** children;     	// Array de punteros a los hijos del nodo
    int numChildren;     	// Número de hijos del nodo

    Node(const string& value, int k);
};

// Clase que representa el árbol de búsqueda
class Sol3 {
public:
    int k;              // Grado k del árbol
    Node* root;         // Puntero a la raíz del árbol

    Sol3(int degree);

    bool searchKey(Node* node, const string& key);
    void insertKey(Node*& node, const string& key);
    void removeKey(Node*& node, const string& key);
	void printT(Node* node, int level = 0);

};