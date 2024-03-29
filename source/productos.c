#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productos.h"
#include "clientes.h"
#include "categorias.h"

void consulta_Productos(){

    system ("cls");

    int op;

    do{
        printf ("\tApartado de Productos.\n");
        printf ("(1) Realizar consulta por categoria.\n");
        printf ("(2) Realizar consulta por nombre.\n");
        printf ("(3) Salir.\n");
        printf ("Elige opcion: ");
        if ((scanf ("%d", &op) != 1) || (op < 1 || op > 3)){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Opcion no contemplada.\n\n");
        }else{
            switch (op){
                case 1: buscar_cat_prod(); break;
                case 2: buscar_nombre_prod(); break;
                case 3: break;
                default: fprintf(stderr, "Ha ocurrido un error.\n"); exit(1);
            }
        }
    }while(op < 1 || op > 3);

}

static void buscar_cat_prod(){
    int i, aux, op = 0;
    unsigned num;
    char temp[56], c[51], *categoria, del[] = "-";      //la longitud de temp2 = 56 pq es la longitud maxima de la linea del fichero, edison no tiene macro todavia para esto, estoy a la espera para cambiarlo
                                                        // Mismo razonamiento para c[51] pero para la descripcion de la categoria; 

    fflush(stdin);

    FILE *f_categorias;

    f_categorias = fopen("../datos/Categorias.txt", "r");

    if (f_categorias == NULL){
        fprintf (stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    //num = funcionEdison;

    num = 1;

    Categorias *cat;

    cat = (Categorias*)malloc(num*sizeof(Categorias));

    if(cat == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    do{
        aux = 0;                        //Para que en cada iteracion vuelva a tomar el valor 0 y no nos de un falso encontrado
        system ("cls");
        printf("Buscar categoria: ");
        fgets(c, 51, stdin);
        fflush(stdin);

        if (c[strlen(c) - 1] == '\n') // Ver si hay un salto de linea al final y reemplazarla con '\0'
            c[strlen(c) - 1] = '\0';

        categoria = (char *)malloc(strlen(c)+1*sizeof(char));

        if(categoria != NULL){
            strcpy(categoria, c);
        }else{
            fprintf(stderr, "No se ha podido reservar memoria.\n");
            exit(1);
        }


        for(i = 0; i < num && aux == 0; i++){
            if(fgets(temp, 56, f_categorias) != NULL){
                if (temp[strlen(temp) - 1] == '\n')            // Ver si hay un salto de linea al final y reemplazarla con '\0'
                    temp[strlen(temp) - 1] = '\0';
                
                dividir_cadena_cat(temp, del, &cat[i]);        // Guardo en las estructuras los datos del fichero Categorias.txt 

                // HASTA AQUI FUNCIONA BIEN

                /*printf ("%s-%s.\n", cat[i].Id_categ, cat[i].Descrip);
                PARA PRUEBAS
                system("pause");*/     

                if(strcmp(categoria, cat[i].Descrip) == 0){
                    categoria_encontrada(&cat[i], del);
                    aux = 1;                                    // Variable que me permite salir del bucle y me dice si he encontrado o no la categoria
                }
            }
        }

        if (aux != 1){              // No se ha encontrado ninguna categoria
            fprintf (stderr, "La categoria buscada no existe.\n");
            printf ("Quiere buscar otra vez? (1) Si (2) No.\n");
            printf ("Elige opcion: ");
            scanf("%s", &op);
        }

    }while(op == 1);
    
    // ESTE DO WHILE NO FUNCIONA!!!!!!!! mirar esto primero

    fclose(f_categorias);
    free(cat);
}

static void categoria_encontrada(Categorias *cat, char del[]){

    int i;
    unsigned num1;
    char temp[MAX_LIN_FICH_PROD];

    FILE *f_productos;

    f_productos = fopen("../datos/Productos.txt", "r");

    if (f_productos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    num1 = num_prod();   //Almaceno el numero de productos

    t_productos *prod;

    prod = (t_productos*)malloc(num1*sizeof(t_productos));       //Creo tantas estructuras como productos existan

    if(prod == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    for(i = 0; i < num1; i++){
        if(fgets(temp, MAX_LIN_FICH_PROD, f_productos) != NULL){
            if (temp[strlen(temp) - 1] == '\n')            // Ver si hay un salto de linea al final y reemplazarla con '\0'
                temp[strlen(temp) - 1] = '\0';
            
            dividir_cadena_prod(temp, del, &prod[i]);       // Guardo en las estructuras los datos del fichero Productos.txt
        }
    }

    for(i = 0; i < num1; i++){
        if(strcmp(prod[i].id_categ, cat->Id_categ) == 0){
                producto_encontrado(prod[i]);
        }
    }

    system("pause");
    system("cls");

    free(prod);
    fclose(f_productos);
}   

static void buscar_nombre_prod(){

    int i, j, aux, op;
    unsigned num;
    char temp[MAX_LIN_FICH_PROD], c[DES], *nombre, del[] = "-";

    FILE *f_productos;
        
    f_productos = fopen("../datos/Productos.txt", "r");

    if (f_productos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    num = num_prod();   //Almaceno el numero de productos

    t_productos *prod;

    prod = (t_productos*)malloc(num*sizeof(t_productos));       //Creo tantas estructuras como productos existan

    if(prod == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    fflush(stdin);

    do{
        aux = 0;        //Para que en cada iteracion vuelva a tomar el valor 0 y no nos de un falso encontrado
        system ("cls");
        printf("Buscar productos: ");
        fgets(c, 50, stdin);
        fflush(stdin);
        
        if (c[strlen(c) - 1] == '\n') // Ver si hay un salto de linea al final y reemplazarla con '\0'
            c[strlen(c) - 1] = '\0';

        nombre = (char*)malloc(strlen(c)+1*sizeof(char));
        
        if (nombre != NULL){
            strcpy(nombre, c);
        }else{
            fprintf (stderr, "No se ha podido reservar memoria.\n");
            exit(1);
        }

        for(i = 0; i < num && aux == 0; i++){   // Recorremos el vector
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH_PROD es el máximo que ocupara cada línea de Productos.txt
            // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
            if(fgets(temp, MAX_LIN_FICH_PROD, f_productos) != NULL){
                if (temp[strlen(temp) - 1] == '\n')        // Ver si hay un salto de linea al final y reemplazarla con '\0'
                    temp[strlen(temp) - 1] = '\0';
                

                dividir_cadena_prod(temp, del, &prod[i]);

                if(strcmp(nombre, prod[i].descrip) == 0){
                    producto_encontrado(prod[i]);
                    aux = 1;        // Variable que nos sirve para salir del bucle cuando hemos encontrado el producto
                }

                /*printf ("%s-%s-%s-%s-%d-%d-%lf.\n", prod[i].id_prod, prod[i].descrip, prod[i].id_categ, prod[i].id_gestor, prod[i].stock,
                                                    prod[i].entrega, prod[i].importe);*/
                // PARA PRUEBAS
            }
        }

        if (aux != 1){
            fprintf (stderr, "Lo sentimos, no tenemos disponible el producto buscado.\n");
        }

        system ("pause");

        do{
            printf ("Desea seguir buscando productos?\n");
            printf ("(1) Si\n(2) No\n");
            printf ("Elige opcion: ");
            
            if (scanf ("%d", &op) != 1){
                fprintf(stderr, "Opcion no contemplada.\n");
            }
            
            fflush(stdin);

            system ("cls");

        }while (op < 1 || op > 2);

        rewind(f_productos);    //Devuelve el puntero al inicio del fichero

    }while (op == 1);

    system ("cls");

    free(nombre);
    free(prod);
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

static void dividir_cadena_cat(char temp[], char del[], Categorias *cat){
    // Divido la cadena mediante su delimitador y la almaceno en la estructura
    char *p1 = strtok(temp, del);
    sprintf(cat->Id_categ, "%s", p1);

    char *p2 = strtok(NULL, del);
    sprintf(cat->Descrip, "%s", p2);
}

static void dividir_cadena_prod(char temp[], char del[], t_productos *producto){
    // Divido la cadena mediante su delimitador y la almaceno en la estructura
    char *p1 = strtok (temp, del);
    sprintf(producto->id_prod, "%s", p1);

    char *p2 = strtok (NULL, del);
    sprintf(producto->descrip, "%s", p2);

    char *p3 = strtok (NULL, del);
    sprintf(producto->id_categ, "%s", p3);

    char *p4 = strtok (NULL, del);
    sprintf(producto->id_gestor, "%s", p4);
        
    char *p5 = strtok (NULL, del);
    producto->stock = atof(p5);   // Uso del atof debido a que strtok devuelve un puntero a char no un puntero a unsigned

    char *p6 = strtok (NULL, del);
    producto->entrega = atof(p6); //          "           "                   "                   "               "

    char *p7 = strtok (NULL, del);
    producto->importe = atof(p7); //          "           "                   "                   "           a double

    printf("%s-%s-%s-%s-%d-%d-%lf.\n", producto->id_prod, producto->descrip, producto->id_categ, producto->id_gestor, producto->stock,
                                        producto->entrega, producto->importe);
}

static void producto_encontrado(t_productos prod){
    if(prod.stock == 0){
        fprintf (stderr, "No hay stock temporalmente del producto %s.\n", prod.descrip);
    }else{
        printf ("Del producto %s se encuentran %d unidades en stock con un importe cada una de %.2lf euros.\n", prod.descrip, prod.stock, prod.importe);
    }
}

void infoProdAdmin(){       // Para Pablo
    int i;
    char buffer[MAX_LIN_FICH_PROD], del[] = "-";

    FILE *fp;
        
    fp = fopen("../datos/Productos.txt", "r");

    if (fp == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    while(!feof(fp)){
        if (fgets(buffer, MAX_LIN_FICH_PROD, fp) != NULL){
            printf ("%s\n", buffer);
        }
    }
    
    fclose(fp);
}

