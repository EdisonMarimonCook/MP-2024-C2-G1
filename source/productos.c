#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productos.h"
#include "clientes.h"

void consultaProductos(){
    int op;

    do{
        printf ("\tApartado de Productos.\n");
        printf ("(1) Realizar consulta por categoría.\n");
        printf ("(2) Realizar consulta por nombre.\n");
        if ((scanf ("%d", &op) != 1) || (op < 1 || op > 2)){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Opcion no contemplada.\n\n");
        }else{
            switch (op){
                case 1: break;
                case 2: buscar_nombre_prod(); break;
                default: fprintf(stderr, "Ha ocurrido un error.\n"); exit(1);
            }
        }
    }while(op < 1 || op > 2);

}

static void buscar_nombre_prod(){

    int i;
    char buffer[MAX_LIN_FICH_PROD], aux[DES], *nombre;

    fgets(aux, 50, stdin);
    fflush(stdin);
    
    aux[strcspn(aux, "\n")] = '\0';

    nombre = (char*)malloc(strlen(aux)+1*sizeof(char));
    
    if (nombre != NULL){
        strcpy(nombre, aux);
    }else{
        fprintf (stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    FILE *f;
    
    f = fopen("../datos/Productos.txt", "r");

    if (f == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    // leemos linea a linea el fichero Productos.txt
    while(fgets(buffer, MAX_LIN_FICH_PROD, f) != NULL)
        printf("%s", buffer);

    for (i = 0; i < numProductos(); i++){
        
    }

    free(nombre);
    fclose(f);
}

static unsigned num_prod(){

    char buffer[MAX_LIN_FICH_PROD];
    unsigned i = 0;

    FILE *f;
    f = fopen("../datos/Clientes.txt", "r");
    if(f == NULL){
        fprintf(stderr, "No se ha podido abrir el fichero.\n");
        exit(1);
    }

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(f)){
        fgets(buffer, MAX_LIN_FICH_CLI, f);
        i++;
    }

    fclose(f);

    return i;
}

/*void cargarProductos (t_productos *info_prod){
    int i;
    char buffer[]
}*/

