#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productos.h"
#include "clientes.h"
#include "categorias.h"
#include "usuarios.h"

void consultaProductosCli(){

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
            fprintf(stderr, "Opcion no contemplada. Pruebe de nuevo.\n\n");
            system("pause");
            break;
        }else{
            switch (op){
            case 1: buscarCatProd(); break;
            case 2: buscarNombreProd(); break;
            case 3: break;
            default: fprintf(stderr, "Ha ocurrido un error.\n"); exit(1);
            }
        }
        
    }while(op < 1 || op > 3);

}

static void buscarCatProd(){
    int i, aux, op;
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
        op = 0;                         //      "           "             "             "                           resultado
        system ("cls");
        printf("Buscar categoria: ");
        fgets(c, 51, stdin);
        fflush(stdin);

        cambio(c);                      // Quito el salto de linea del \n y meto un \0

        categoria = (char *)malloc(strlen(c)+1*sizeof(char));

        if(categoria != NULL){
            strcpy(categoria, c);
        }else{
            fprintf(stderr, "No se ha podido reservar memoria.\n");
            exit(1);
        }


        for(i = 0; i < num && aux == 0; i++){
            if(fgets(temp, 56, f_categorias) != NULL){
                
                cambio(temp);                      // Quito el salto de linea del \n y meto un \0
                
                dividirCadenaCat(temp, del, &cat[i]);        // Guardo en las estructuras los datos del fichero Categorias.txt 

                // HASTA AQUI FUNCIONA BIEN

                /*printf ("%s-%s.\n", cat[i].Id_categ, cat[i].Descrip);
                PARA PRUEBAS
                system("pause");*/     

                if(strcmp(categoria, cat[i].Descrip) == 0){
                    categoriaEncontrada(&cat[i], del);
                    aux = 1;                                    // Variable que me permite salir del bucle y me dice si he encontrado o no la categoria
                }
            }
        }

        if (aux != 1){              // No se ha encontrado ninguna categoria
            fprintf (stderr, "La categoria introducida no existe.\n");
        }

        system("pause");
        system("cls");

        do{
            printf ("Quiere buscar otra vez? (1) Si (2) No.\n");
            printf ("Elige opcion: ");
            if (scanf("%d", &op) != 1){
                fprintf (stderr, "Opcion no contemplada. Pruebe de nuevo.\n");
                system("pause");
            }
            fflush(stdin);
        }while(op < 1 || op > 2);

        rewind(f_categorias);       // Puntero al inicio del fichero

    }while(op == 1);

    fclose(f_categorias);
    free(cat);
}

static void categoriaEncontrada(Categorias *cat, char del[]){

    int i;
    unsigned num1;
    char temp[MAX_LIN_FICH_PROD];

    FILE *f_productos;

    f_productos = fopen("../datos/Productos.txt", "r");

    if (f_productos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    num1 = numProd();   //Almaceno el numero de productos

    tProductos *prod;

    prod = (tProductos*)malloc(num1*sizeof(tProductos));       //Creo tantas estructuras como productos existan

    if(prod == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    for(i = 0; i < num1; i++){
        if(fgets(temp, MAX_LIN_FICH_PROD, f_productos) != NULL){
            
            cambio(temp);                      // Quito el salto de linea del \n y meto un \0
            
            dividirCadenaProd(temp, del, &prod[i]);       // Guardo en las estructuras los datos del fichero Productos.txt
        }
    }

    for(i = 0; i < num1; i++){
        if(strcmp(prod[i].id_categ, cat->Id_categ) == 0){
                productoEncontrado(prod[i]);
        }
    }

    system("pause");
    system("cls");
    fflush(stdin);

    free(prod);
    fclose(f_productos);
}   

static void buscarNombreProd(){

    int i, j, aux, op;
    unsigned num;
    char temp[MAX_LIN_FICH_PROD], c[DES], *nombre, del[] = "-";

    FILE *f_productos;
        
    f_productos = fopen("../datos/Productos.txt", "r");

    if (f_productos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    num = numProd();   //Almaceno el numero de productos

    tProductos *prod;

    prod = (tProductos*)malloc(num*sizeof(tProductos));       //Creo tantas estructuras como productos existan

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
        
        cambio(c);                      // Quito el salto de linea del \n y meto un \0

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
                
                cambio(temp);                      // Quito el salto de linea del \n y meto un \0

                dividirCadenaProd(temp, del, &prod[i]);

                if(strcmp(nombre, prod[i].descrip) == 0){
                    productoEncontrado(prod[i]);
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
        system ("cls");

        do{
            printf ("Desea seguir buscando productos?\n");
            printf ("(1) Si\n(2) No\n");
            printf ("Elige opcion: ");
            
            if (scanf ("%d", &op) != 1){
                fprintf(stderr, "Opcion no contemplada. Pruebe de nuevo.\n");
                system("pause");
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

static unsigned numProd(){

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

static void dividirCadenaCat(char temp[], char del[], Categorias *cat){
    // Divido la cadena mediante su delimitador y la almaceno en la estructura
    char *p1 = strtok(temp, del);
    sprintf(cat->Id_categ, "%s", p1);

    char *p2 = strtok(NULL, del);
    sprintf(cat->Descrip, "%s", p2);
}

static void dividirCadenaProd(char temp[], char del[], tProductos *producto){
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

}

static void productoEncontrado(tProductos prod){
    if(prod.stock == 0){
        fprintf (stderr, "No hay stock temporalmente del producto %s.\n", prod.descrip);
    }else{
        printf ("Del producto %s se encuentran %d unidades en stock con un importe cada una de %.2lf euros.\n", prod.descrip, prod.stock, prod.importe);
    }
}

void consultaProdAdmin(){

    system("cls");

    int op;

    do{
        printf ("\tApartado de Productos\n");
        printf ("(1) Consultar informacion de los productos.\n");
        printf ("(2) Dar de alta un producto.\n");
        printf ("(3) Dar de baja un producto.\n");
        printf ("(4) Buscar producto por nombre.\n");
        printf ("(5) Buscar producto por categoria.\n");
        printf ("(6) Modificar un producto.\n");

        if((scanf("%d", &op) != 1) || (op < 1 || op > 6)){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Opcion no contemplada. Pruebe de nuevo.\n\n");
            system("pause");
        }else{
            switch(op){
            case 1: infoProdAdmin(); break;
            case 2: darAltaProd(); break;
            case 3: break;
            case 4: buscarNombreProd(); break;
            case 5: buscarCatProd(); break;
            case 6: break;
            default: fprintf(stderr, "Opcion no contemplada"); break;
            }
        }


    }while(op < 1 || op > 6);
}

static void infoProdAdmin(){       // Para Pablo

    system("cls");          // Limpiar la terminal

    int i;
    unsigned num;
    char temp[MAX_LIN_FICH_PROD], del[] = "-";

    FILE *f_productos;
        
    f_productos = fopen("../datos/Productos.txt", "r");

    if (f_productos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    num = numProd();   //Almaceno el numero de productos

    tProductos *prod;

    prod = (tProductos*)malloc(num*sizeof(tProductos));       //Creo tantas estructuras como productos existan

    if(prod == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    fflush(stdin);

    for(i = 0; i < num; i++){   // Recorremos el vector
        // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH_PROD es el máximo que ocupara cada línea de Productos.txt
        // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
        if(fgets(temp, MAX_LIN_FICH_PROD, f_productos) != NULL){
            
            cambio(temp);                      // Quito el salto de linea del \n y meto un \0
            
            dividirCadenaProd(temp, del, &prod[i]);

            printf ("\nId producto: %s, producto: %s, id categoria: %s, id gestor: %s, stock: %d, entrega: %d, importe: %lf.\n\n", 
            prod[i].id_prod, prod[i].descrip, prod[i].id_categ, prod[i].id_gestor, prod[i].stock, prod[i].entrega, prod[i].importe);
                                            
        }
    }
    
    fclose(f_productos);
    free(prod);

    system("pause");
}

static void darAltaProd(){

    unsigned num = numProd();
    tProductos NuevoProd;

    generarID(NuevoProd.id_prod, num, ID);
    getDescripcion(NuevoProd.descrip);
    printf ("Nueva descripcion: %s.\n", NuevoProd.descrip);
    getIDcateg(NuevoProd.id_categ);
    printf("Id categ: %s.\n", NuevoProd.id_categ);
    /*getIDgestor(&NuevoProd.id_gestor);
    getStock(&NuevoProd.stock);
    getEntrega(&NuevoProd.entrega);
    getImporte(&NuevoProd.importe);*/

}

void modProdAdmin(){

}

static void getDescripcion(char *descripcion){
    
    char Descrip[100];              // aux[DES+1] para saber si nos excedemos de caracteres
    int op;

    fflush(stdin);

    do{
        op = 0;                         // Ruta de escape 
        printf ("Introduce la descripcion del nuevo producto: ");
        fgets(Descrip, 100, stdin);
        cambio(Descrip);                // Quito el salto de linea del \n y meto un \0
        fflush(stdin);

        if(strlen(Descrip) > DES-1){
            fprintf(stderr, "Se excede la longitud maxima de caracteres, pruebe de nuevo.\n");
            op = 1;
            system("pause");
        }else
            strcpy(descripcion, Descrip);
        
    }while(op == 1);

}

static void getIDcateg(char *categ){

    char id[ID_PROD], temp[56], del[] = "-";      //la longitud de temp2 = 56 pq es la longitud maxima de la linea del fichero, edison no tiene macro todavia para esto, estoy a la espera para cambiarlo;
    int op, i, aux;
    unsigned num;

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
        aux = 0;                          // Para que en cada iteracion vuelva a tomar el valor 0 y no nos de un falso encontrado
        op = 0;                           ///      "           "             "             "                           resultado
        printf("Introduce la ID de la categoria (formato 0000): ");
        fgets(id, ID_PROD, stdin);
        cambio(id);                       // Quito el salto de linea del \n y meto un \0
        fflush(stdin);

        if(strlen(id) != ID_PROD-1){
            fprintf(stderr, "La longitud del ID es distinta a la requerida, pruebe de nuevo.\n");
            aux = 2;                // Para que no entre en el bucle
        }

        for(i = 0; i < num && aux == 0; i++){
            if(fgets(temp, 56, f_categorias) != NULL){
                
                cambio(temp);                      // Quito el salto de linea del \n y meto un \0
                
                dividirCadenaCat(temp, del, &cat[i]);        // Guardo en las estructuras los datos del fichero Categorias.txt      

                if(strcmp(id, cat[i].Id_categ) == 0){
                    strcpy(categ, id);
                    aux = 1;                                    // Variable que me permite salir del bucle y me dice si he encontrado o no la categoria
                }
            }
        }

        if (aux != 1){              // No se ha encontrado ninguna categoria
            fprintf (stderr, "La categoria introducida no existe.\n");
        }

        system("pause");
        system("cls");

        do{
            printf ("Quiere probar otra vez? (1) Si (2) No.\n");
            printf ("Elige opcion: ");
            if (scanf("%d", &op) != 1){
                fprintf (stderr, "Opcion no contemplada. Pruebe de nuevo.\n");
                system("pause");
            }
            fflush(stdin);
        }while(op < 1 || op > 2);

        rewind(f_categorias);       // Puntero al inicio del fichero

        if(op == 2)
            break;          //Para que no continue la ejecucion de las siguientes funciones en darAltaProd

    }while(op == 1);

    fclose(f_categorias);

}


void cambio(char *temp){
    if (temp[strlen(temp) - 1] == '\n') // Ver si hay un salto de linea al final y reemplazarla con '\0'
        temp[strlen(temp) - 1] = '\0';
}