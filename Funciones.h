//
// Created by Santiago Tomas Muscellini on 25/10/2022.
//

#ifndef PRUEBA_PARCIAL_2_FUNCIONES_H
#define PRUEBA_PARCIAL_2_FUNCIONES_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Estructuras/ArbolBinarioAVL.h"
#include "Estructuras/Lista.h"

using namespace std;

void rellenarArbol(ArbolBinarioAVL<string>& arbol, int&contadorPalabra, int &contadorLetra, int&contadorLineas, string nombreFile);
void excluirf(string nombreFile, ArbolBinarioAVL<string>&arbol);
void palabras(int n, ArbolBinarioAVL<string>& arbol);
void ocurrencias(int n, ArbolBinarioAVL<string>&arbol, Lista<string>*lista, int maxOcurrencias);
void mostrar(string argumento, ArbolBinarioAVL<string>&arbol);
void mostarNpalabrasString(string palabras, int n);
void excluir(string argumento, ArbolBinarioAVL<string>&arbol);

#endif //PRUEBA_PARCIAL_2_FUNCIONES_H
