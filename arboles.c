#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct _nodo {
   int dato;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

//prototipo de funciones

void menu();
void Insertar(Arbol *a, int dat);
void Borrar(Arbol *a, int dat);
int Buscar(Arbol a, int dat);
int Vacio(Arbol r);
int EsHoja(pNodo r);
int NumeroNodos(Arbol a, int* c);
int AlturaArbol(Arbol a, int* altura);
int Altura(Arbol a, int dat);

void InOrden(Arbol, void (*func)(int*));
void PreOrden(Arbol, void (*func)(int*));
void PostOrden(Arbol, void (*func)(int*));


void Podar(Arbol *a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void Mostrar(int *d);

int main()
{
    //le damos color a la pantalla
    system("color 2f");
        menu();

   system("PAUSE");
   return 0;
}
//funcion menu del arbol
void menu(){
    int op;
     Arbol ArbolInt=NULL;
    int altura;
    int nnodos;
    int num, tam;
    do{
        printf("\t-----------------------\n");
        printf("\t|   MENU ARBOL        |\n");
        printf("\t|---------------------|\n");
        printf("\t|  1. insertar arbol  |\n");
        printf("\t|  2. busuqeda arbol  |\n");
        printf("\t|  3. borrar          |\n");
        printf("\t|  4.  salir          |\n");
         printf("\t----------------------\n");
        printf("\n\n");
        printf("\tingrese una opcion\n");
        scanf("%d",&op);
        system("cls");

        switch(op){
            //se le pide al usuario que ingrese los datos al arbol
            case 1: printf("ingrese el numero de elementos \n");
            scanf("%d",&tam);

            for(int i=0; i<tam; i++){
            printf("ingrese un numero\n");
            scanf("%d",&num);
            Insertar(&ArbolInt, num);
            }
            system("pause");
            system("cls");

            break;

            case 2: //muestra la altura del arbol
                printf("\n\n MOSTRANDO NODOS\n \n");

            printf("Altura de arbol %d\n", AlturaArbol(ArbolInt, &altura));
   //muestra el recorrer del arbol de la primera rama, antes de recorrer la última

            printf("InOrden: ");
            InOrden(ArbolInt, Mostrar);
            printf("\n");
   //realiza el recorrido desde el nodo antes de recorrer las ramas
            printf("PreOrden: ");
            PreOrden(ArbolInt, Mostrar);
            printf("\n");
            printf("PostOrden: ");
            PostOrden(ArbolInt, Mostrar);
            printf("\n");
            printf("N nodos: %d\n", NumeroNodos(ArbolInt, &nnodos));
            system("pause");
            system("cls");
            break;

            case 3:printf("ingrese el numero a eliminar\n");
            scanf("%d",&num);
            Borrar(&ArbolInt, num);

            printf("InOrden: ");
            InOrden(ArbolInt, Mostrar);
            printf("\n");
   //realiza el recorrido desde el nodo antes de recorrer las ramas
            printf("PreOrden: ");
            PreOrden(ArbolInt, Mostrar);
            printf("\n");
            printf("PostOrden: ");
            PostOrden(ArbolInt, Mostrar);
            printf("\n");

            printf("N nodos: %d\n", NumeroNodos(ArbolInt, &nnodos));
            printf("Altura de 1 %d\n", Altura(ArbolInt, 1));
            printf("Altura de 10 %d\n", Altura(ArbolInt, 10));
            printf("Altura de arbol %d\n", AlturaArbol(ArbolInt, &altura));

            Podar(&ArbolInt);
            system("pause");
            system("cls");

            break;

        }
    }while(op != 4);
}
// se elimina la rama de un arbol
void Podar(Arbol *a)
{

   if(*a) {
      Podar(&(*a)->izquierdo);
      Podar(&(*a)->derecho);
      free(*a);
      *a = NULL;
   }
}
//funcion para insertar los nodos del arbol
void Insertar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual = *a;
   //se comprueba si el arbol esta vasio

   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }

   if(!Vacio(actual)) return;

   if(Vacio(padre)) {
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
   }

   else if(dat < padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
   }

   else if(dat > padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
  }
}
// funcion para elimina un nodo del arbol
void Borrar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual;
   pNodo nodo;
   int aux;

   actual = *a;

   while(!Vacio(actual)) {
      if(dat == actual->dato) {
         if(EsHoja(actual)) {
            if(padre)

               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            free(actual);
            actual = NULL;
            return;
         }
         else {
            padre = actual;

            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }

            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }

            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else {
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

//funcion para realizar el recorrido del arbol empezando por las ramas
void InOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) InOrden(a->izquierdo, func);
   func(&(a->dato));
   if(a->derecho) InOrden(a->derecho, func);
}

//funcion para realizar el recorrido del arbol empezando por el nodo raiz
void PreOrden(Arbol a, void (*func)(int*))
{
   func(&a->dato);
   if(a->izquierdo) PreOrden(a->izquierdo, func);
   if(a->derecho) PreOrden(a->derecho, func);
}

//funcion para recorrer el arbol desde las ramas terminando en el nodo padre
void PostOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) PostOrden(a->izquierdo, func);
   if(a->derecho) PostOrden(a->derecho, func);
   func(&a->dato);
}

int Buscar(Arbol a, int dat)
{
   pNodo actual = a;

   while(!Vacio(actual)) {
      if(dat == actual->dato) return TRUE;
      else if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }
   return FALSE;
}

int Altura(Arbol a, int dat)
{
   int altura = 0;
   pNodo actual = a;

   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura;
      else {
         altura++;
         if(dat < actual->dato) actual = actual->izquierdo;
         else if(dat > actual->dato) actual = actual->derecho;
      }
   }
   return -1;
}
//cuenta el numero de nodos que tienen el arbol

int NumeroNodos(Arbol a, int *contador)
{
   *contador = 0;

   auxContador(a, contador);
   return *contador;
}

void auxContador(Arbol nodo, int *c)
{
   (*c)++;

   if(nodo->izquierdo) auxContador(nodo->izquierdo, c);
   if(nodo->derecho)   auxContador(nodo->derecho, c);
}
//muestra la altura del arbol
int AlturaArbol(Arbol a, int *altura)
{
   *altura = 0;

   auxAltura(a, 0, altura);
   return *altura;
}

void auxAltura(pNodo nodo, int a, int *altura)
{
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1, altura);

   if(EsHoja(nodo) && a > *altura) *altura = a;
}

int Vacio(Arbol r)
{
   return r==NULL;
}

int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}

void Mostrar(int *d)
{
   printf("%d, ", *d);
}

