//
// Created by Santiago Tomas Muscellini on 25/10/2022.
//

#include "Funciones.h"

void rellenarArbol(ArbolBinarioAVL<string>& arbol, int&contadorPalabra,int &contadorLetra, int&contadorLineas,string nombreFile){ // Rellenamos nuestro ArbolAVL
                                                                                                                                // con las palabras en el texto
    ifstream file;
    string auxiliar;
    string renglon;
    file.open(nombreFile, ios::in);
    if(file.is_open()){
        while (!file.eof()){
            contadorLineas++;
            if(auxiliar != "") {
                arbol.put(auxiliar);
                contadorPalabra++;
                auxiliar = "";
            }
            getline(file, renglon);
            for(int i = 0; i < renglon.size();i++){
                if(renglon[i] !='(' && renglon[i] !=')'  && renglon[i] != '.' && renglon[i] != ','
                && renglon[i] != ' ' && renglon[i] != ';' && renglon[i] != '['  && renglon[i] != ']'    // Caracteres a evitar de ASCII
                && renglon[i] != 39 && renglon[i] != '?' && renglon[i] != ':' && renglon[i] != '='
                && renglon[i] != 34 && renglon[i] != 38 && renglon[i] != '!' && renglon[i] != '-'){
                    contadorLetra++;
                    auxiliar.push_back(tolower(renglon[i]));
                }else if(auxiliar != ""){
                    contadorPalabra++;
                    arbol.put(auxiliar);
                    auxiliar = "";
                }
            }
        }
    }
    else{
        throw 300;
    }
    cout << "Contador Letras: " << contadorLetra << endl;
    cout << "Contador Palabras: " << contadorPalabra << endl;
    cout << "Contador lineas: " << contadorLineas << endl;


    cout << "Cantidad de palabras distintas: " << arbol.contarNodos() << endl;
}

void excluirf(string nombreFile,ArbolBinarioAVL<string>&arbol){
    ifstream ignoreFile;
    string auxiliar,renglon;
    ignoreFile.open(nombreFile, ios::in);
    if(ignoreFile.is_open()) {
        while (!ignoreFile.eof()) {
            if (auxiliar != "") {
                arbol.searchAndIgnore(auxiliar);
                auxiliar = "";
            }
            getline(ignoreFile, renglon);
            for (int i = 0; i < renglon.size(); i++) {
                if (renglon[i] !='(' && renglon[i] !=')'  && renglon[i] != '.' && renglon[i] != ',' && renglon[i] != ' '
                && renglon[i] != ';' && renglon[i] != '['  && renglon[i] != ']' && renglon[i] != 39 && renglon[i] != '?'
                && renglon[i] != ':' && renglon[i] != '=' && renglon[i] != 34 && renglon[i] != 38 && renglon[i] != '!'
                && renglon[i] != '-') {
                    auxiliar.push_back(tolower(renglon[i]));
                } else if (auxiliar != "") {
                    arbol.searchAndIgnore(auxiliar);  // El metodo searchAndIgnore cambia de estado el atributo "evitar" del nodo arbol a true
                    auxiliar = "";                              // Asi cuando se necesite imprimir la palabra en la funcion ocurrencias se ignora si el valor es true
                }

            }
        }
    }else{
        throw 400;
    }
}

void palabras(int n,ArbolBinarioAVL<string>& arbol){
    string ordenado;
    cout << "ORDEN ALFABETICO PALABRAS DIFERENTES: " << endl;
    if(n==0){
        arbol.inorder();
    }
    else{
        arbol.inorderNpalabras(ordenado);
        mostarNpalabrasString(ordenado, n);
    }
    cout << endl;
}

void mostarNpalabrasString(string palabras, int n){
    for(int i=0; i < palabras.size() && n > 0;i++){
        if(palabras[i]!=' '){
            cout<< palabras[i];
        }
        else{
            n--;
            cout<<palabras[i];
        }
    }
    cout<<endl;
}

void ocurrencias(int n, ArbolBinarioAVL<string>&arbol, Lista<string>*arregloLista, int maxOcurrencias){

    if(n==0){
        for(int i = maxOcurrencias-1; i >= 0; i--){
            if(!arregloLista[i].esVacia()){
                cout << "Elementos del texto que ocurren " << i+1<< " veces." << endl;
                arregloLista[i].print();
                cout << endl;
            }
        }
    }
    else{
        for(int i = maxOcurrencias-1; i >= 0 && n>0; i--){
            if(!arregloLista[i].esVacia()){
                cout << "Elementos del texto que ocurren " << i+1<< " veces." << endl;
                arregloLista[i].print(n);
                cout << endl;
            }
        }
    }
}
void mostrar(string argumento, ArbolBinarioAVL<string>&arbol){
    string auxiliar="";

    cout <<"Argumento mostrar: " <<argumento<<endl;
    for (int i = 0; i < argumento.size(); i++) {
        if (argumento[i] != '.' && argumento[i] != ',' && argumento[i] != ' ') {
            auxiliar.push_back(tolower(argumento[i]));
        } else if (auxiliar != "") {
            arbol.searchAndPrint(auxiliar);
            auxiliar = "";
        }
        if(i==argumento.size()-1) arbol.searchAndPrint(auxiliar);
    }
}

void excluir(string argumento, ArbolBinarioAVL<string>&arbol){
    string auxiliar="";

    for (int i = 0; i < argumento.size(); i++) {
        if (argumento[i] != '.' && argumento[i] != ',') {
            auxiliar.push_back(tolower(argumento[i]));
        } else if (auxiliar != "") {
            arbol.searchAndIgnore(auxiliar);
            auxiliar = "";
        }
        if(i==argumento.size()-1) arbol.searchAndIgnore(auxiliar);
    }
}