//
// Created by Santiago Tomas Muscellini on 25/10/2022.
//

#include "Funciones.h"

void rellenarArbol(ArbolBinarioAVL<string>& arbol, int&contadorPalabra,int &contadorLetra, int&contadorLineas,string nombreFile){
    /*
     * Rellenamos nuestro ArbolAVL con las palabras contenidas en el archivo de texto.
     */
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
                if((renglon[i] >= 65 && renglon[i] <= 90) || (renglon[i] >= 97 && renglon[i] <= 122)){
                    //Se chequea que el renglon[i] caiga dentro de los valores ascii de las letras.
                    contadorLetra++;
                    auxiliar.push_back(tolower(renglon[i]));
                }else if(renglon[i] == -61 ||renglon[i] == -79){
                    /*
                     * Si la palabra es un caracter con tilde o especial ocupa dos espacios.
                     * Entonces salteamos uno para evitar que el programa lo tome como dos letras distintas.
                     */
                    contadorLetra++;
                    auxiliar.push_back(tolower(renglon[i]));
                    i++;
                }else if(auxiliar != ""){
                    contadorPalabra++;
                    arbol.put(auxiliar);
                    auxiliar = "";
                }
            }
        }
        if(auxiliar!=""){
            contadorPalabra++;
            arbol.put(auxiliar);
        }
    }
    else{
        throw 300;
    }

    file.close();

    cout << "Contador Letras: " << contadorLetra << endl;
    cout << "Contador Palabras: " << contadorPalabra << endl;
    cout << "Contador lineas: " << contadorLineas << endl;


    cout << "Cantidad de palabras distintas: " << arbol.contarNodos() << endl;
}

void excluirf(string nombreFile,ArbolBinarioAVL<string>&arbol){

    //Se realiza el mismo procedimiento que en rellenar arbol pero utilizando el metodo searchAndIgnore
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
            for(int i = 0; i < renglon.size();i++){
                if((renglon[i] >= 65 && renglon[i] <= 90) || (renglon[i] >= 97 && renglon[i] <= 122)){

                    auxiliar.push_back(tolower(renglon[i]));
                }else if(renglon[i] == -61 ||renglon[i] == -79){
                    auxiliar.push_back(tolower(renglon[i]));
                    i++;
                }else if(auxiliar != ""){
                    arbol.searchAndIgnore(auxiliar);
                    auxiliar = "";
                }
            }
        }
        if(auxiliar!=""){
            arbol.searchAndIgnore(auxiliar);
        }
    }else{
        throw 400;
    }
    ignoreFile.close();

    cout<<endl;
}

void palabras(int n,ArbolBinarioAVL<string>& arbol){
    string ordenado;
    cout << "ORDEN ALFABETICO PALABRAS DIFERENTES: " << endl;
    if(n==0){
        arbol.inorder();
    }
    else{
        /*
         * Si n no es 0, utilizamos el string ordenado y lo rellenamos con todas las palabras del arbol en orden alfabetico.
         * Luego llamamos al metodo mostrasNpalabras que imprime el string hasta la enesima palabra.
         */
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

    /*
     * Para mostrar las ocurrencias generamos un arreglo de lista.
     * En cada posicion del arreglo hay una lista que contiene los elementos que se repiten i veces de
     * acuerdo a la posicion del arreglo. Por ejemplo, la posicion 2 del arreglo contiene los
     * elementos que se repiten 3 veces en el texto.
     */
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

    /*
     * Mostrar busca la palabra en el árbol e imprime las ocurrencias.
     */
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

    /*
     * Las palabras ingresadas se bucan en el arbol con el metodo searchAndIgnore.
     * Este metodo cambia el booleano contenido en el nodo arbol a true para que el metodo ocurrencias lo ignore.
     */

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