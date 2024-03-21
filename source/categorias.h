#ifndef CATEGORIAS_H_
#define CATEGORIAS_H_

typedef struct{
    char  Id_categ[5];
    char Descrip[51];

}Categorias; 

void mainCategorias();

static void realizarBaja();
static void realizarAlta(char id_actual[]);
static void modificarCategoria();

#endif