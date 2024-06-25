#include "ddskl.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

using namespace std;

#define K 4  // valor utilizado en la solucion 2

int main(int argc, char **argv){
    
    Sol obj;
   
    string nomArchivo2 = "D2.txt";
	ifstream archivo2(nomArchivo2.c_str());
	string linea2;
    auto inicio = steady_clock::now();
	while(getline(archivo2, linea2)){
        cout << linea2 << endl;
        
        const u_char* uCharPtr2 = reinterpret_cast<const u_char*>(linea2.c_str());
		obj.insertArray(uCharPtr2);
        
	}
    auto fin = high_resolution_clock::now();
    duration<double> tiempoTranscurrido = fin - inicio;
    cout << "Tiempo de ejecución de la función insertArray: " << tiempoTranscurrido.count() << " segundos." << endl;


    obj.printArray();

    
    
    /*
    string nomArchivo1 = "D1.txt";
	ifstream archivo1(nomArchivo1.c_str());
	string linea1;
	while(getline(archivo1, linea1)){
        cout << linea1 << endl;
        
        const u_char* uCharPtr1 = reinterpret_cast<const u_char*>(linea1.c_str());
		obj.insertArray(uCharPtr1);
        
	}
    obj.printArray();
    */
    
    /*
    
    Sol2 obj2(3);
    cout << "se la insertan a manke" << endl;
    if (obj2.insertG((u_char*)"manke"))
        obj2.printG(obj2.G[0]);

    obj2.insertG((u_char*)"tuto");
    obj2.insertG((u_char*)"cangri");
    obj2.insertG((u_char*)"nico");
    obj2.insertG((u_char*)"yordy");
    obj2.insertG((u_char*)"io");
    obj2.insertG((u_char*)"angelo");
    

    obj2.printG(obj2.G[0]);

    nodo* acaesta1 = obj2.searchG((u_char*)"cangri");
    nodo* acaesta2 = obj2.searchG((u_char*)"manke");
    nodo* acaesta3 = obj2.searchG((u_char*)"pene");

    if (acaesta1 != nullptr)
        cout << "ACA ESTA!!" << endl;
    else
        cout << "NO ESTA!!" << endl;

    if (acaesta2 != nullptr)
        cout << "ACA ESTA!!" << endl;
    else
        cout << "NO ESTA!!" << endl;

    if (acaesta3 != nullptr)
        cout << "ACA ESTA!!" << endl;
    else
        cout << "NO ESTA!!" << endl;

    obj2.printG(obj2.G[0]);
    */
    Sol3 obj3(4);

    string nomArchivo3 = "D2.txt";
	ifstream archivo3(nomArchivo3.c_str());
	string linea3;
	while(getline(archivo3, linea3)){
        cout << linea3 << endl;
        obj3.insertKey(obj3.root, linea3);
    }

    

    cout << "### FIN ###" << endl;
    return EXIT_SUCCESS;
}