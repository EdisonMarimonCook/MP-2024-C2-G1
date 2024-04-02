#ifndef CATEGORIAS_H_
#define CATEGORIAS_H_

typedef struct{
    char  Id_categ[5];
    char Descrip[51];

}Categorias; 

void mainCategorias();
<<<<<<< HEAD
unsigned lenCategorias();
=======
>>>>>>> 0be5ab220d516970d3e01a7ff1e9a04674d2380b

static void realizarBaja();
static void realizarAlta(char id_actual[]);
static void modificarCategoria();

#endif