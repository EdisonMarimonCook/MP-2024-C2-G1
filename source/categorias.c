#include <stdio.h>
#include <stdlib.h>     //ficheros
#include <string.h>     //stcpy, sscanf
#include "categorias.h"

unsigned lenCategorias(){

    unsigned numCat = 0;

    char linefich[MAX_LIN_FICH_CATEG];

    FILE *fich = fopen("../datos/Categorias.txt", "r");
    if(fich == NULL){
        perror("No se pudo abrir Categorias.txt");
        exit(1);
    }

    while(!feof(fich)){
        fgets(linefich, MAX_LIN_FICH_CATEG, fich);
        numCat++;
    }

    fclose(fich);

    return numCat;

}

static void modificarCategoria() {

    char idCategoria[MAX_ID_CATEG]; 
    char nuevaDescrip[MAX_DESC_CATEG];
    int a;

    fflush(stdin);

    do{
        printf("Escriba el ID de la categoria a modificar: ");
        //fgets(idCategoria, MAX_ID_CATEG, stdin);
        //idCategoria[strcspn(idCategoria, "\n")] = '\0';
        scanf(" %4s", idCategoria);

        a = atoi(idCategoria);
    }while(a == 0);

    printf("Escriba la nueva descripcion para la categoria: ");
    //fgets(nuevaDescrip, MAX_DESC_CATEG, stdin);
    //nuevaDescrip[strcspn(nuevaDescrip, "\n")] = '\0';
    scanf(" %50[^\n]", nuevaDescrip);   //

    printf("ID de la categoria a modificar: %s\n", idCategoria);
    printf("Nueva descripción: %s\n", nuevaDescrip);

    FILE *archivoOriginal, *archivoTemporal;
    char id[MAX_ID_CATEG];
    char descrip[MAX_DESC_CATEG];
    int encontrado = 0;

    descrip[MAX_DESC_CATEG] = '\0';

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

    fflush(stdin);

    Categorias nueva_categoria;

    strcpy(nueva_categoria.Id_categ, id_actual);

    for(int i = 0; i < MAX_DESC_CATEG; i++){
        nueva_categoria.Descrip[i] = '\0';
    }

    printf("Ingrese la descripción de la nueva categoría (máximo 50 caracteres): ");

    fgets(nueva_categoria.Descrip, MAX_DESC_CATEG, stdin);
    while(getchar() != '\n');

    printf("%s", nueva_categoria.Descrip);

    fprintf(fichero, "%s-%s\n", nueva_categoria.Id_categ, nueva_categoria.Descrip);

    fclose(fichero);

    printf("Se ha agregado una nueva categoría al archivo: %s-%s\n", nueva_categoria.Id_categ, nueva_categoria.Descrip);
}

static void realizarBaja() {
    char id_baja[MAX_ID_CATEG];
    int encontrado = 0;
    int a;

    do{
        printf("Ingrese el ID de la categoría que desea dar de baja: ");
        scanf(" %4s", id_baja);
        a = atoi(id_baja);

    }while(a == 0);

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

    while (fscanf(fichero_entrada, "%4s-%[^\n]", categoria.Id_categ, categoria.Descrip) == 2) {
        printf("%s", categoria.Id_categ);
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
        remove("../datos/Categorias_temp.txt");
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
        while (fgets(linea, sizeof(linea), fichero)){   //hacer sscanf
            id_numerica = atoi(id_actual);  
            id_numerica++;

            sprintf(id_actual, "%04d", id_numerica);

            printf("id actual: %s\n", id_actual);
            printf("id numerica: %d\n", id_numerica);
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
    
    fclose(fichero);
}
