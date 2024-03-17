#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productos.h"
#include "clientes.h"

void consulta_Productos(){
    int op;

    do{
        printf ("\tApartado de Productos.\n");
        printf ("(1) Realizar consulta por categoria.\n");
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

    int i, j;
    unsigned num;
    char temp[MAX_LIN_FICH_PROD], aux[DES], *nombre;

    num = num_prod();   //Almaceno el numero de productos

    t_productos *prod;

    prod = (t_productos*)malloc(num*sizeof(t_productos));

    if(prod == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    fflush(stdin);
    printf("Buscar productos: ");
    fgets(aux, 50, stdin);
    fflush(stdin);
    
    if (aux[strlen(aux) - 1] == '\n') // Verificar si hay una nueva línea al final y reemplazarla con '\0'
        aux[strlen(aux) - 1] = '\0';

    nombre = (char*)malloc(strlen(aux)+1*sizeof(char));
    
    if (nombre != NULL){
        strcpy(nombre, aux);
    }else{
        fprintf (stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    FILE *f_productos;
    
    f_productos = fopen("../datos/Productos.txt", "r");

    if (f_productos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    for(i = 0; i < num; i++){   // Recorremos el vector
        // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH_PROD es el máximo que ocupara cada línea de Productos.txt
        // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
        if(fgets(temp, MAX_LIN_FICH_PROD, f_productos) != NULL){
            if (temp[strlen(temp) - 1] == '\n'){
                temp[strlen(temp) - 1] = '\0';
            }
            sscanf(temp, "%[^-]-%[^-]-%[^-]-%[^-]-%d-%d-%lf", prod[i].id_prod, prod[i].descrip, prod[i].id_categ, prod[i].id_gestor,
                                                            prod[i].stock, prod[i].entrega, prod[i].importe);

            printf("%s-%s-%s-%s-%d-%d-%lf", prod[i].id_prod, prod[i].descrip, prod[i].id_categ, prod[i].id_gestor,
                                            prod[i].stock, prod[i].entrega, prod[i].importe);
        }
    }

    free(nombre);
    fclose(f_productos);
}

static unsigned num_prod(){

    char buffer[MAX_LIN_FICH_PROD];
    unsigned cont = 0;

    FILE *f_productos;
    f_productos = fopen("../datos/Productos.txt", "r");
    if(f_productos == NULL){
        fprintf(stderr, "No se ha podido abrir el fichero.\n");
        exit(1);
    }

    vaciar(buffer);

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(f_productos)){
        fgets(buffer, MAX_LIN_FICH_CLI, f_productos);
        cont++;
    }

    if (fseek(f_productos, 0, SEEK_END) != 0){          //Puntero al principio del fichero
        fprintf(stderr, "Ha ocurrido un error en el fichero.\n");
        exit(1);
    }
    fputs("\n", f_productos);

    fclose(f_productos);

    return cont;
}

static void vaciar(char temp[]){
    int i = 0;

    while (i < MAX_LIN_FICH_PROD){
        temp[i] = '\0';
        i++;
    }
}

