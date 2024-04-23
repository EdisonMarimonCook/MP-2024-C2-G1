#include <stdio.h>
#include <stdlib.h>     //ficheros
#include <string.h>     //stcpy, sscanf
#include "categorias.h"

void mainCategorias();
unsigned lenCategorias();
static void realizarBaja();
static void realizarAlta(char id_actual[]);
static void modificarCategoria();

unsigned lenCategorias(){

    unsigned numCat = 0;

    FILE *fich = fopen("../datos/Categorias.txt", "r");
    if(fich == NULL){
        perror("No se pudo abrir Categorias.txt");
        exit(1);
    }

    while(!feof(fich)){
        numCat++;
    }

    fclose(fich);

    return numCat;

}

static void modificarCategoria() {

    char idCategoria[5]; 
    char nuevaDescrip[50];

    printf("Escriba el ID de la categoria a modificar: ");
    scanf("%s", idCategoria);
    while (getchar() != '\n');

    printf("Escriba la nueva descripcion para la categoria: ");
    scanf("%s", nuevaDescrip);

    FILE *archivoOriginal, *archivoTemporal;
    char id[5];
    char descrip[51];
    int encontrado = 0;

    descrip[51] = '\0';

    archivoOriginal = fopen("../datos/Categorias.txt", "r");
    if (archivoOriginal == NULL) {
        printf("No se pudo abrir el archivo original.\n");
        exit(1);
    }

    archivoTemporal = fopen("../datos/Categorias_temp.txt", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo abrir el archivo temporal.\n");
        fclose(archivoOriginal);
        exit(1);
    }

    while (fscanf(archivoOriginal, "%4s-%[^\n]\n", id, descrip) != EOF) {
        if (strcmp(id, idCategoria) == 0) {
            strncpy(descrip, nuevaDescrip, sizeof(descrip) - 1); 
            encontrado = 1;
        }
        fprintf(archivoTemporal, "%s-%s\n", id, descrip);
    }

    fclose(archivoOriginal);
    fclose(archivoTemporal);

    if (encontrado) {
        remove("../datos/Categorias.txt");
        rename("../datos/Categorias_temp.txt", "../datos/Categorias.txt");
        printf("Categoría modificada correctamente.\n");
    } else {
        printf("Categoría no encontrada.\n");
        remove("../datos/Categorias_temp.txt");
    }
}

static void realizarAlta(char id_actual[]) {
    FILE *fichero = fopen("../datos/Categorias.txt", "a+");
    if (fichero == NULL) {
        printf("No se pudo abrir el archivo Categorias.txt\n");
        exit(1);
    }

    Categorias nueva_categoria;

    strcpy(nueva_categoria.Id_categ, id_actual);

    printf("Ingrese la descripción de la nueva categoría (máximo 50 caracteres): ");

    fgets(nueva_categoria.Descrip, sizeof(nueva_categoria.Descrip), stdin);
    nueva_categoria.Descrip[strcspn(nueva_categoria.Descrip, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    fprintf(fichero, "%s-%s\n", nueva_categoria.Id_categ, nueva_categoria.Descrip);

    fclose(fichero);

    printf("Se ha agregado una nueva categoría al archivo: %s-%s\n", nueva_categoria.Id_categ, nueva_categoria.Descrip);
}

static void realizarBaja() {
    char id_baja[5];
    int encontrado = 0;

    printf("Ingrese el ID de la categoría que desea dar de baja: ");
    fgets(id_baja, 4, stdin);
    if (id_baja[strlen(id_baja) - 1] == '\n') 
        id_baja[strlen(id_baja) - 1] = '\0';
    scanf("%s", id_baja);
    while (getchar() != '\n');

    FILE *fichero_entrada = fopen("../datos/Categorias.txt", "r");
    if (fichero_entrada == NULL) {
        printf("No se pudo abrir el archivo Categorias.txt\n");
        exit(1);
    }

    FILE *fichero_salida = fopen("../datos/Categorias_temp.txt", "w");
    if (fichero_salida == NULL) {
        printf("No se pudo abrir el archivo temporal\n");
        fclose(fichero_entrada);
        exit(1);
    }

    Categorias categoria;

    while (fscanf(fichero_entrada, "%4s-%50[^\n]", categoria.Id_categ, categoria.Descrip) == 2) {
        if (strcmp(categoria.Id_categ, id_baja) != 0) {
            fprintf(fichero_salida, "%s-%s\n", categoria.Id_categ, categoria.Descrip);
        }else{
            encontrado = 1;
        }
    }

    if(!encontrado){
        printf("No se ha encontrado la ID ingresada.\n");
        fclose(fichero_salida);
        fclose(fichero_entrada);
        return;
    }

    fclose(fichero_entrada);
    fclose(fichero_salida);

    remove("../datos/Categorias.txt");
    rename("../datos/Categorias_temp.txt", "../datos/Categorias.txt");

    printf("La categoría con ID %s ha sido dada de baja.\n", id_baja);
}

void mainCategorias(){

    FILE *fichero = fopen("../datos/Categorias.txt", "r+");
    if (fichero == NULL){
        perror("No se pudo abrir Categorias.txt");
        exit(1);
    }

    char id_actual[5];
    char linea[56];
    int id_numerica;
    int op = 1;
    int i = 0;
   
    if (fscanf(fichero, "%4s", id_actual) != 1){    //si no existe alguna categoria, crearlo
        strcpy(id_actual, "0001");
        id_numerica = 1;

    }else{  
        while (fgets(linea, sizeof(linea), fichero)){
            id_numerica = atoi(id_actual);  
            id_numerica++;

            sprintf(id_actual, "%04d", id_numerica);
        }
    }

    rewind(fichero);

    Categorias *categoria;

    categoria = (Categorias*)calloc(id_numerica, sizeof(Categorias));

    printf("Contenido del archivo Categorias.txt:\n");
    
    while (fgets(linea, sizeof(linea), fichero) != NULL && i < id_numerica){
        if (sscanf(linea, "%4s-%[^\n]\n", categoria[i].Id_categ, categoria[i].Descrip) != 2) {
            printf("Error al leer datos de  categoría en la línea %d.\n", i + 1);
            exit(1);
        }else{
            printf("%s-%s\n", categoria[i].Id_categ, categoria[i].Descrip);
        }
        i++;
    }

    id_numerica--;

    printf("1 para realizar alta, 2 para baja y 3 para modificar: ");

    do{
        if(scanf("%d", &op) != 1 || op < 1 || op > 3){
            system("cls");
            fflush(stdin);
            perror("Entrada no valida. \n\n");
        }else{

            switch(op){
                case 1: realizarAlta(id_actual); break;

                case 2: realizarBaja(); break;

                case 3: modificarCategoria(); break;
            }
        }
    }while(op < 1 || op > 3);
    scanf("%d", &op);
    while (getchar() != '\n');

    if(op < 1 || op > 3){
        printf("Escriba un numero entre 1 y 3.\n");
        system("cls");
        mainCategorias();
    }

    switch(op){
        case 1: realizarAlta(id_actual); break;

        case 2: realizarBaja(); break;

        case 3: modificarCategoria(); break;
    }
    
    fclose(fichero);
}

