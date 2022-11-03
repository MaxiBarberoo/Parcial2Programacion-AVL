#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Estructuras/ArbolBinario.h"
#include "Estructuras/Lista.h"
#include "Funciones.h"

using namespace std;

int main(int argc, char ** argv) {
    clock_t begin;
    begin = clock();

    cout << "Comenzando a medir Tiempo\n" << endl;

    ArbolBinario<string> arbol;
    string nombreFile="/Users/mussa/Documents/Universidad/Programacion_III/prueba-parcial-2/";
    string nombreIgnore="/Users/mussa/Documents/Universidad/Programacion_III/prueba-parcial-2/";
    int contadorPalabra = 0, contadorLetra = 0, contadorLineas = 0;
    int aux;
    string aux_comandos,aux_comandos2;
    ifstream prueba_error;
    aux_comandos=argv[1];
    aux_comandos2=nombreFile+aux_comandos;


    try{
        prueba_error.open(aux_comandos2,ios::in);
        if(!prueba_error.is_open()) throw 404;
        else prueba_error.close();
    }
    catch(int error){
        cout<<"No se ha provisto un archivo de texto con el cual trabajar."<<endl;
        exit(404);
    }

    rellenarArbol(arbol,contadorPalabra,contadorLetra,contadorLineas,aux_comandos2);

    int maxOcurrencias = arbol.maxOcurrencia();
    Lista<string> arregloLista[maxOcurrencias];

    for(int i=2; i <argc;i++){
       aux_comandos = argv[i];

       if(aux_comandos=="palabras"){
           aux = stoi(argv[i+1]);
           palabras(aux,arbol);
       }

        if(aux_comandos=="excluirf"){
            aux_comandos2 = nombreIgnore+argv[i+1];
            excluirf(aux_comandos2,arbol);
        }

        if(aux_comandos=="ocurrencias"){
            aux = stoi(argv[i+1]);
            arbol.generarLista(arregloLista);
            ocurrencias(aux,arbol,arregloLista,maxOcurrencias);
        }

        if(aux_comandos=="mostrar"){
            aux_comandos2=argv[i+1];
            mostrar(aux_comandos2,arbol);
        }

        if(aux_comandos=="excluir"){
            aux_comandos2=argv[i+1];
            excluir(aux_comandos2,arbol);
        }
    }


/*
    rellenarArbol(arbol,contadorPalabra,contadorLetra,contadorLineas,nombreFile);
    palabras(0,arbol);

    excluirf(nombreIgnore,arbol);


    int maxOcurrencias = arbol.maxOcurrencia();
    Lista<string> arregloLista[maxOcurrencias];
    arbol.generarLista(arregloLista);

    ocurrencias(0,arbol,arregloLista,maxOcurrencias);

*/


    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo: " << elapsed_secs << " seg\n" << std::endl;
    return 0;
}


