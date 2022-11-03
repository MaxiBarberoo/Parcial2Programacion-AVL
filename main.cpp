#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Estructuras/ArbolBinarioAVL.h"
#include "Estructuras/Lista.h"
#include "Funciones.h"
#include <stdexcept>

using namespace std;

int main(int argc, char ** argv) {
    clock_t begin;
    begin = clock();

    cout << "Comenzando a medir Tiempo\n" << endl;

    if(argc < 2){
        cout << "Argumentos de consola insuficiente" << endl;
        exit(2);
    }

    ArbolBinarioAVL<string> arbol;
    string nombreFile="C:\\Users\\win10\\Desktop\\Parcial2Programacion-AVL\\";
    string nombreIgnore="C:\\Users\\win10\\Desktop\\Parcial2Programacion-AVL\\";
    int contadorPalabra = 0, contadorLetra = 0, contadorLineas = 0;
    int aux;
    string aux_comandos,aux_comandos2;
    ifstream prueba_error;
    aux_comandos=argv[1];
    aux_comandos2=nombreFile+aux_comandos;


    try{
        rellenarArbol(arbol,contadorPalabra,contadorLetra,contadorLineas,aux_comandos2);
    }
    catch(int error){
        cout<<"No se ha provisto un archivo de texto con el cual trabajar o el archivo de texto es invalido"<<endl;
        exit(300);
    }



    int maxOcurrencias = arbol.maxOcurrencia();
    Lista<string> arregloLista[maxOcurrencias];

    for(int i=2; i <argc;i++){
       aux_comandos = argv[i];

       if(aux_comandos=="palabras"){
           try {
               aux = stoi(argv[i + 1]);
               palabras(aux, arbol);
           }catch(std::invalid_argument &error){
                palabras(0, arbol);
           }catch(std::logic_error &error){
               palabras(0, arbol);
           }
       }

        if(aux_comandos=="excluirf"){
            try {
                if(i+1 >= argc){
                    throw 404;
                }
                aux_comandos2 = nombreIgnore + argv[i + 1];
                cout << aux_comandos2;
                excluirf(aux_comandos2, arbol);
            }catch(int error){
                if(error == 404){
                cout << "No se encontro archivo" << endl;
                exit(404);
                }else{
                    cout << " No se recibio un archivo valido" << endl;
                    exit(400);
                }
            }
        }

        if(aux_comandos=="ocurrencias"){
            try {
                arbol.generarLista(arregloLista);
                aux = stoi(argv[i + 1]);
                ocurrencias(aux, arbol, arregloLista, maxOcurrencias);
            }catch(std::invalid_argument &error){
                ocurrencias(0, arbol, arregloLista, maxOcurrencias);
            }catch(std::logic_error &error){
                ocurrencias(0, arbol, arregloLista, maxOcurrencias);

            }
        }

        if(aux_comandos=="mostrar"){
            try {
                if(i+1 >= argc){
                    throw 400;
                }
                aux_comandos2 = argv[i + 1];
                mostrar(aux_comandos2, arbol);
            }catch(int &error){
                if(error == 400) {
                    cout << "Argumento consola Invalido" << endl;
                    exit(400);
                }
            }
        }

        if(aux_comandos=="excluir"){
            try {
                if(i+1 >= argc){
                    throw 400;
                }
                aux_comandos2 = argv[i + 1];
                excluir(aux_comandos2, arbol);
            }catch(int &error){
                if(error == 400) {
                    cout << "Argumento consola Invalido" << endl;
                    exit(400);
                }
            }
        }
    }

    cout << "\nTerminar Medir Tiempo" << endl;
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo: " << elapsed_secs << " seg\n" << std::endl;
    return 0;
}


