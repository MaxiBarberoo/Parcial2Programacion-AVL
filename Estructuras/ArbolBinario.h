#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_

#include "NodoArbol.h"
#include "ColaPrioridad.h"
#include "Lista.h"

template <class T>
class ArbolBinario
{

public:
  ArbolBinario();

  void put(T data);

  T search(T data);

  NodoArbol<T> searchNodo(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void inorderNpalabras(string& ordenado);

  void postorder();

  ~ArbolBinario();

  bool esVacio();

  void print();

  int contarNodos();

  void searchAndIgnore(T datoIgnore);

  ColaPrioridad<T> ordenOcurrencias();

  int maxOcurrencia();

  void generarLista(Lista<T> *lista);

  void searchAndPrint(T data);
private:

    NodoArbol<T> *root;
  T search(T data, NodoArbol<T> *r);
  void searchAndIgnore(T datoIgnore, NodoArbol<T> *r);
  NodoArbol<T> *put(T data, NodoArbol<T> *r);
  NodoArbol<T> *remove(T data, NodoArbol<T> *r);
  NodoArbol<T> *findMaxAndRemove(NodoArbol<T> *r, bool *found);
  int contarNodos(NodoArbol<T> *r);
  int maxOcurrencia(int &max, NodoArbol<T> *r);
  ColaPrioridad<T> ordenOcurrencias(ColaPrioridad<T> &cola, NodoArbol<T> *r);
  void preorder(NodoArbol<T> *r);
  void inorder(NodoArbol<T> *r);
  void postorder(NodoArbol<T> *r);
  void generarLista(Lista<T> *lista, NodoArbol<T> *r);
  void inorderNpalabras(string& ordenado, NodoArbol<T>*r);
    NodoArbol<T> searchNodo(T data, NodoArbol<T>*r);
    void searchAndprint(T data, NodoArbol<T>*r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinario<T>::ArbolBinario() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinario<T>::search(T data)
{
  return search(data, root);
}

template <class T>
T ArbolBinario<T>::search(T data, NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    throw 404;
  }

  if (r->getData() == data)
  {
    return r->getData();
  }

  if (r->getData() > data)
  {
    return search(data, r->getLeft());
  }
  else
  {
    return search(data, r->getRight());
  }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolBinario<T>::put(T data) { root = put(data, root); }

template <class T>
NodoArbol<T> *ArbolBinario<T>::put(T data, NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return new NodoArbol<T>(data);
  }

  if (r->getData() == data)
  {
    r->incrementarOcurrencia();
    return r;
  }

  if (r->getData() > data)
  {
    r->setLeft(put(data, r->getLeft()));
  }
  else
  {
    r->setRight(put(data, r->getRight()));
  }

  return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T>
void ArbolBinario<T>::remove(T data)
{
  root = remove(data, root);
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r)
{

  if (r == nullptr)
  {
    throw 404;
  }

  NodoArbol<T> *aux;

  if(r->getData()==data){
      if(r->getRight()==nullptr&&r->getLeft()==nullptr){
          delete r;
          return nullptr;
      }
      if(r->getRight()!=nullptr && r->getLeft()==nullptr){
          aux=r->getRight();
          delete r;
          return aux;
      }
      if(r->getRight()==nullptr && r->getLeft()!=nullptr){
          aux=r->getLeft();
          delete r;
          return aux;
      }

      if(r->getRight()!=nullptr && r->getLeft()!=nullptr){

          if(r->getLeft()->getRight()!=nullptr){
              bool found;
              aux = findMaxAndRemove(r->getLeft(),&found);
              aux->setRight(r->getRight());
              aux->setLeft(r->getLeft());

          }else{
                aux=r->getLeft();
                aux->setRight(r->getRight());
          }
          delete r;
          return aux;

      }
  }else{
      if(r->getData()>data){
          r->setLeft(remove(data,r->getLeft()));
      }
      else{
          r->setRight(remove(data,r->getRight()));
      }
  }

    return r;
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::findMaxAndRemove(NodoArbol<T> *r, bool *found)
{
  NodoArbol<T> ret;
  *found = false;

  if (r->getRight() == nullptr)
  {
    *found = true;
    return r;
  }

  ret = findMaxAndRemove(r->getRight(), found);
  if (*found)
  {
    r->setRight(ret.getLeft());
    *found = false;
  }

  return ret;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T>
bool ArbolBinario<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolBinario<T>::preorder()
{
  preorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::preorder(NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  std::cout << r->getData() << " ";
  preorder(r->getLeft());
  preorder(r->getRight());
}

/**
 * Recorre un árbol en orden
 */
template <class T>
void ArbolBinario<T>::inorder()
{
        inorder(root);
        std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::inorder(NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  inorder(r->getLeft());
  std::cout << r->getData() << " ";
  inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T>
void ArbolBinario<T>::postorder()
{
  postorder(root);
  std::cout << std::endl;
}

template <class T>
void ArbolBinario<T>::postorder(NodoArbol<T> *r)
{
  if (r == nullptr)
  {
    return;
  }

  postorder(r->getLeft());
  postorder(r->getRight());
  std::cout << r->getData() << " ";
}

/**
 * Muestra un árbol por consola
 */
template <class T>
void ArbolBinario<T>::print()
{
  if (root != NULL)
    root->print(false, "");
}

template<class T>
int ArbolBinario<T>::contarNodos() {
    return contarNodos(root);
}

template<class T>
int ArbolBinario<T>::contarNodos(NodoArbol<T> *r) {
    if(r == nullptr) return 0;
    return 1 + contarNodos(r->getRight()) + contarNodos(r->getLeft());
}

template<class T>
void ArbolBinario<T>::searchAndIgnore(T datoIgnore) {
    searchAndIgnore(datoIgnore, root);
}

template<class T>
void ArbolBinario<T>::searchAndIgnore(T datoIgnore, NodoArbol<T> *r) {
    if (r == nullptr)
    {
        throw 404;
    }

    if (r->getData() == datoIgnore)
    {
        r->Evitar();
        return;
    }

    if (r->getData() > datoIgnore)
    {
        return searchAndIgnore(datoIgnore, r->getLeft());
    }
    else
    {
        return searchAndIgnore(datoIgnore, r->getRight());
    }
}

template<class T>
ColaPrioridad <T> ArbolBinario<T>::ordenOcurrencias() {
    ColaPrioridad<T> colaOrdenada;
    return ordenOcurrencias(colaOrdenada, root);
}

template<class T>
ColaPrioridad <T> ArbolBinario<T>::ordenOcurrencias(ColaPrioridad <T> &cola, NodoArbol<T> *r) {

    if(r == nullptr){
        return cola;
    }

    if(!r->debeEvitar()){
        cola.encolarPrioridad(r->getData(), r->getOcurrencias());
        ordenOcurrencias(cola, r->getLeft());
        ordenOcurrencias(cola, r->getRight());
    }else{
        ordenOcurrencias(cola, r->getLeft());
        ordenOcurrencias(cola, r->getRight());
    }

    return cola;
}

template<class T>
int ArbolBinario<T>::maxOcurrencia() {
    int maxInicial = 1;
    return maxOcurrencia(maxInicial, root);
}

template<class T>
int ArbolBinario<T>::maxOcurrencia(int &max, NodoArbol<T> *r) {
    if(r == nullptr){
        return max;
    }

    if(!r->debeEvitar() && r->getOcurrencias() > max){
        max = r->getOcurrencias();
        maxOcurrencia(max, r->getLeft());
        maxOcurrencia(max, r->getRight());
    }else{
        maxOcurrencia(max, r->getLeft());
        maxOcurrencia(max, r->getRight());
    }

    return max;
}

template<class T>
void ArbolBinario<T>::generarLista(Lista<T> *lista) {
    generarLista(lista, root);
}

template<class T>
void ArbolBinario<T>::generarLista(Lista<T> *lista, NodoArbol<T> *r) {
    Lista<T> *auxLista;
    if(r == nullptr){
        return;
    }


    if(!r->debeEvitar()){
        auxLista = &lista[r->getOcurrencias()-1];
        auxLista->insertarPrimero(r->getData());
    }
    generarLista(lista, r->getLeft());
    generarLista(lista, r->getRight());
}

template<class T>
void ArbolBinario<T>::inorderNpalabras(string& ordenado, NodoArbol<T>*r) {
    if (r == nullptr)
    {
        return;
    }

    inorderNpalabras(ordenado, r->getLeft());
    ordenado+= r->getData() + " ";
    inorderNpalabras(ordenado, r->getRight());
}

template<class T>
NodoArbol<T> ArbolBinario<T>::searchNodo(T data) {
    return searchNodo(data, root);
}

template<class T>
NodoArbol<T> ArbolBinario<T>::searchNodo(T data, NodoArbol<T> *r) {
    if (r == nullptr)
    {
        throw 404;
    }

    if (r->getData() == data)
    {
        return r;
    }

    if (r->getData() > data)
    {
        return search(data, r->getLeft());
    }
    else
    {
        return search(data, r->getRight());
    }
}

template<class T>
void ArbolBinario<T>::searchAndPrint(T data) {
    searchAndprint(data,root);
}

template<class T>
void ArbolBinario<T>::searchAndprint(T data, NodoArbol<T> *r) {
    if (r == nullptr)
    {
        throw 404;
    }

    if (r->getData() == data)
    {
        cout<< "Palabra: "<<r->getData()<<endl;
        cout<<"Ocurrencias: "<<r->getOcurrencias()<<endl;
        return;
    }

    if (r->getData() > data)
    {
        searchAndprint(data, r->getLeft());
    }
    else
    {
        searchAndprint(data, r->getRight());
    }
}

template<class T>
void ArbolBinario<T>::inorderNpalabras(string &ordenado) {
    inorderNpalabras(ordenado,root);
}


#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_
