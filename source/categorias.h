#ifndef CATEGORIAS_H_
#define CATEGORIAS_H_

#define MAX_ID_CATEG 5
#define MAX_DESC_CATEG 51
#define MAX_LIN_FICH_CATEG 56

typedef struct{
    char  Id_categ[MAX_ID_CATEG];
    char Descrip[MAX_DESC_CATEG];

}Categorias; 

/* FUNCIONES PUBLICAS */

// Precondición: nada.
// Postcondición: proporciona un menu.
void mainCategorias();

// Precondición: nada. 
// Postcondición: devuelve la cantidad de categorías del sistema.
unsigned lenCategorias();

/* FUNCIONES PRIVADAS */

// Precondición: nada.
// Postcondición: elimina una categoría especificada en el sistema.
static void realizarBaja();

// Precondición: nada.
// Postcondición: agrega una categoría.
static void realizarAlta();

// Precondición: nada.
// Postcondición: modifica una categoria especificada.
static void modificarCategoria();

#endif