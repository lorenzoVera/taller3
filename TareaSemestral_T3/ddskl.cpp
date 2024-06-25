#include "ddskl.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;


/*                SOLUCION 1                */
Sol::Sol() {
    length = 100;
    numWord = 0;
	v = new u_char*[length];
}

Sol::~Sol() {
    for(int i = 0; i < numWord; i++){
        delete[] v[i]; 
    } 
	delete[] v;
}

int Sol::searchArray(const u_char* word){
    

	int der = numWord - 1;
	int izq = 0;
	while(izq <= der){
		int mid = izq + (der-izq)/2;
		int compa = ucharCompare(word, v[mid]);
		if(compa == 0)
			return mid;
		else if(compa < 0)
			der = mid - 1;
		else
			izq = mid + 1;
	}
    
	return -1;
}

bool Sol::elimArray(const u_char* word){

	int pos = searchArray(word);
    if (pos < 0 || numWord <= 0)
        return false; 
   
    delete[] v[pos]; 
    for (int i = pos; i < numWord - 1; i++)
        v[i] = v[i + 1]; 
		
    numWord--;
    
    return true;
}

bool Sol::insertArray(const u_char* word) {
    
    int pos = 0;
    redimension();
   
    while (pos < numWord && ucharCompare(word, v[pos]) > 0)
        pos++;

    if (pos < numWord && ucharCompare(word, v[pos]) == 0) {
        cout << "NO SE PUEDE INSERTAR! (clave repetida)" << endl;
        return false;
    }
    
    for (int i = numWord - 1; i >= pos; i--)
        v[i + 1] = v[i];

    v[pos] = new u_char[strlen(reinterpret_cast<const char*>(word)) + 1];
    strcpy(reinterpret_cast<char*>(v[pos]), reinterpret_cast<const char*>(word));

    numWord++;


    return true;
}               

void Sol::printArray(){
	for (int i = 0; i<numWord; i++){
		cout << v[i] << " - ";
	}
	cout << endl;
}

void Sol::redimension(){
	if (numWord >= length){
		int newLength = length+static_cast<int>(length*0.2);
		u_char** newArray = new u_char*[newLength];
		for (int i = 0; i < numWord; i++) 
            newArray[i] = v[i];

	    delete[] v;
        v = newArray;		
    	length = newLength;
	}
}

int Sol::ucharCompare(const u_char* str1, const u_char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i])
            return -1;
        else if (str1[i] > str2[i])
            return 1;
        i++;
    }
    if (str1[i] == '\0' && str2[i] != '\0')
        return -1;
    else if (str1[i] != '\0' && str2[i] == '\0')
        return 1;
    else
        return 0;
}

/*                SOLUCION 2                */

Sol2::Sol2(int level) {
    L = level;
    G = new nodo*[L];
    for (int i=0 ; i<L ; i++) {
        G[i] = nullptr;
    }       
}

nodo* Sol2::searchG(const u_char* key) {
    
    nodo* p = G[L - 1];  
    
    while (p != nullptr) {
        int cmp = compareG(key, p->key);
        
        if (cmp == 0)
            return p;
        else if (cmp < 0)
            p = p->up;
        else
            p = p->next;
    }
    
    return nullptr;
}

bool Sol2::insertG(u_char* word) {
    
    //  creamos nuevo nodo
    nodo* nuevo = new nodo;
    nuevo->key = word;
    nuevo->next = NULL;
    nuevo->up = NULL;
    //  busca posicion donde insertar el nodo
    if (G[0] == nullptr || compareG(word, G[0]->key) < 0) {
        nuevo->next = G[0];
        G[0] = nuevo;
    } else {
        nodo* p = G[0];
        while (p->next != nullptr && compareG(word, p->next->key) >= 0) {
            if (compareG(word, p->next->key) == 0)
                return false;
            p = p->next;
		}
		nuevo->next = p->next;
        p->next = nuevo;
    }
    for (int i=1; i < L; i++) {
        nodo* prev = NULL;
        nodo* p = G[i - 1];

        while (p != nullptr && compareG(word, p->key) >= 0) {
            if (compareG(word, p->key) == 0)
                return false;
            prev = p;
            p = p->next;
        }
        if (prev != nullptr) {
            nodo* newNode = new nodo;
            newNode->key = word;
            newNode->next = p;
            newNode->up = prev->up;

            prev->up = newNode;
        }
    }
    
	return true;
}

int Sol2::compareG(const u_char* key1, const u_char* key2) {
    int i = 0;
    while (key1[i] != '\0' && key2[i] != '\0') {
        if (key1[i] < key2[i])
            return -1;
        else if (key1[i] > key2[i])
            return 1;
        
        i++;
    }
    
    if (key1[i] == '\0' && key2[i] == '\0')
        return 0;
    else if (key1[i] == '\0')
        return -1;
    else
        return 1;
}

void Sol2::printG(nodo* L) {
    for (int i = 0; i < this->L; i++) {
        nodo* p = G[i];

        while (p != nullptr) {
            cout << p->key << " ";
            p = p->next;
        }
        cout << endl;
    }
}

/* aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Sol2::Sol2(int level) {
    L = level;
    G = new nodo*[L];
    for (int i = 0; i < L; i++) {
        G[i] = nullptr;
    }       
}

nodo* Sol2::searchG(const u_char* key) {
    nodo* p = G[L - 1];  
    
    while (p != nullptr) {
        int cmp = compareG(key, p->key);
        
        if (cmp == 0)
            return p;
        if (cmp < 0)
            p = p->up;
        else
            p = p->next;
    }
    return nullptr;
}

bool Sol2::insertG(u_char* word) {
    //  creamos nuevo nodo
    nodo* nuevo = new nodo;
    nuevo->key = word;
    nuevo->next = nullptr;
    nuevo->up = nullptr;
    //  busca posición donde insertar el nodo
    if (G[0] == nullptr || compareG(word, G[0]->key) < 0) {
        nuevo->next = G[0];
        G[0] = nuevo;
    } else {
        nodo* p = G[0];
        while (p->next != nullptr && compareG(word, p->next->key) >= 0) {
            if (compareG(word, p->next->key) == 0)
                return false;
            p = p->next;
        }
        nuevo->next = p->next;
        p->next = nuevo;
    }
    // se inserta el nodo en los niveles inferiores
    for (int i = 1; i < L; i++) {
        if (compareG(word, G[i-1]->key) < 0) {
            nodo* newNode = new nodo;
            newNode->key = word;
            newNode->next = G[i-1];
            newNode->up = nullptr;
            G[i-1]->up = newNode;
            G[i] = newNode;
        } else {
            nodo* p = G[i-1];
            while (p->next != nullptr && compareG(word, p->next->key) >= 0) {
                if (compareG(word, p->next->key) == 0)
                    return false;
                p = p->next;
            }
            nuevo->next = p->next;
            p->next = nuevo;
            nuevo->up = p->up;
            p->up = nuevo;
        }
    }
    return true;
}

void Sol2::printG(nodo* L) {
    nodo* p = L;

    while (p != nullptr) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << endl;
}

int Sol2::compareG(const u_char* key1, const u_char* key2) {
    int i = 0;
    while (key1[i] != '\0' && key2[i] != '\0') {
        if (key1[i] < key2[i])
            return -1;
        else if (key1[i] > key2[i])
            return 1;
        i++;
    }
    if (key1[i] == '\0' && key2[i] == '\0')
        return 0;
    else if (key1[i] == '\0')
        return -1;
    else
        return 1;
}
*/
/*                SOLUCION 3                */

// Implementación de la estructura Node
Node::Node(const string& value, int k) {
    key = value;
    numChildren = 0;
    children = new Node*[k];
    for (int i = 0; i < k; i++) {
        children[i] = nullptr;
    }
}

// Implementación de la clase Sol3
Sol3::Sol3(int degree) {
    k = degree;
    root = nullptr;
}

bool Sol3::searchKey(Node* node, const string& key) {
    
    if (node == nullptr) {
        return false;
    }

    if (node->key == key) {
        return true;
    }

    int childIndex = 0;
    while (childIndex < node->numChildren && key > node->children[childIndex]->key) {
        childIndex++;
    }

    if (childIndex < node->numChildren && node->children[childIndex]->key == key) {
        return true;
    }

    if (childIndex == node->numChildren || key < node->children[childIndex]->key) {
        return searchKey(node->children[childIndex], key);
    }
    
    return false;
}

void Sol3::insertKey(Node*& node, const string& key) {

   if (node == nullptr) {
        node = new Node(key, k);
        return;
    }

    int childIndex = 0;
    while (childIndex < node->numChildren && key > node->children[childIndex]->key) {
        childIndex++;
    }

    if (childIndex < node->numChildren && node->children[childIndex]->key == key) {
        return;
    }

    if (childIndex == node->numChildren || key < node->children[childIndex]->key) {
        insertKey(node->children[childIndex], key);
    } else {
        insertKey(node->children[childIndex + 1], key);
    }
    
}

void Sol3::removeKey(Node*& node, const string& key) {
    
    if (node == nullptr) {
        return;
    }

    int childIndex = 0;
    while (childIndex < node->numChildren && key > node->children[childIndex]->key) {
        childIndex++;
    }

    if (childIndex < node->numChildren && node->children[childIndex]->key == key) {
        // Realizar la eliminación del nodo encontrado
        return;
    }

    if (childIndex == node->numChildren || key < node->children[childIndex]->key) {
        removeKey(node->children[childIndex], key);
    }
    
}

void Sol3::printT(Node* node, int level) {
    if (node == nullptr) {
        return;
    }

    // Imprimir el nodo actual
    cout << string(level * 4, ' ') << node->key << endl;

    // Imprimir los hijos recursivamente
    for (int i = 0; i < node->numChildren; i++) {
        printT(node->children[i], level + 1);
    }
}