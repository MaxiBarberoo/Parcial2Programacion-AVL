//
// Created by Santiago Tomas Muscellini on 25/10/2022.
//

#ifndef PRUEBA_PARCIAL_2_FUNCIONES_H
#define PRUEBA_PARCIAL_2_FUNCIONES_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Estructuras/ArbolBinario.h"
#include "Estructuras/Lista.h"

using namespace std;

void rellenarArbol(ArbolBinario<string>& arbol, int&contadorPalabra,int &contadorLetra, int&contadorLineas,string nombreFile);
void excluirf(string nombreFile, ArbolBinario<string>&arbol);
void palabras(int n, ArbolBinario<string>& arbol);
void ocurrencias(int n, ArbolBinario<string>&arbol, Lista<string>*lista, int maxOcurrencias);
void mostrar(string argumento, ArbolBinario<string>&arbol);
void mostarNpalabrasString(string palabras, int n);
void excluir(string argumento, ArbolBinario<string>&arbol);

#endif //PRUEBA_PARCIAL_2_FUNCIONES_H
