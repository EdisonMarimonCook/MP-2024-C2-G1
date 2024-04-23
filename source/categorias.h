#ifndef CATEGORIAS_H_
#define CATEGORIAS_H_

#define MAX_ID_CATEG 5
#define MAX_DESC_CATEG 51
#define MAX_LIN_FICH_CATEG 56

typedef struct{
    char  Id_categ[MAX_ID_CATEG];
    char Descrip[MAX_DESC_CATEG];

}Categorias; 

void mainCategorias();
unsigned lenCategorias();

static void realizarBaja();
static void realizarAlta(char id_actual[]);
static void modificarCategoria();

#endif