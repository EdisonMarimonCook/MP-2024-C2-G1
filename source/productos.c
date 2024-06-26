#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "productos.h"
#include "clientes.h"
#include "usuarios.h"
#include "adminprov.h"
#include "pedidos.h"
#include "categorias.h"

void consultaProductosCli(){

    system ("cls");

    int op, encontrado;
    char producto[DES], idProd[ID];

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
        }else{
            switch (op){
            case 1: buscarCatProd(); break;
            case 2: buscarNombreProd(idProd, &encontrado); break;
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

    num = lenCategorias();

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
    unsigned num;
    char temp[MAX_LIN_FICH_PROD];

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

    for(i = 0; i < num; i++){
        if(fgets(temp, MAX_LIN_FICH_PROD, f_productos) != NULL){
            
            cambio(temp);                      // Quito el salto de linea del \n y meto un \0
            
            dividirCadenaProd(temp, del, &prod[i]);       // Guardo en las estructuras los datos del fichero Productos.txt
        }
    }

    for(i = 0; i < num; i++){
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

char* buscarNombreProd(char *idProd, int *encontrado){

    int i, aux, op;
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
        op = 0;
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
                    *encontrado = productoEncontrado(prod[i]);
                    aux = 1;        // Variable que nos sirve para salir del bucle cuando hemos encontrado el producto
                    idProd = prod[i].id_prod;
                }

                /*printf ("%s-%s-%s-%s-%d-%d-%lf.\n", prod[i].id_prod, prod[i].descrip, prod[i].id_categ, prod[i].id_gestor, prod[i].stock,
                                                    prod[i].entrega, prod[i].importe);*/
                // PARA PRUEBAS
            }
        }

        if (aux != 1){
            fprintf (stderr, "Lo sentimos, no tenemos disponible el producto buscado.\n");
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
        }

        system ("pause");
        system ("cls");

        rewind(f_productos);    //Devuelve el puntero al inicio del fichero

    }while (op == 1);

    system ("cls");

    free(prod);
    fclose(f_productos);

    return nombre;
}

unsigned numProd(){

    char buffer[MAX_LIN_FICH_PROD];
    unsigned cont = 0;

    FILE *f_productos;
    f_productos = fopen("../datos/Productos.txt", "r");
    if(f_productos == NULL){
        fprintf(stderr, "No se ha podido abrir el fichero.\n");
        exit(1);
    }

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(f_productos)){
        fgets(buffer, MAX_LIN_FICH_PROD, f_productos);
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

void vaciar(char temp[]){
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

static int productoEncontrado(tProductos prod){
    int aux;

    if(prod.stock == 0){
        fprintf (stderr, "No hay stock temporalmente del producto %s.\n", prod.descrip);
        aux = 1;
    }else{
        printf ("Del producto %s se encuentran %d unidades en stock con un importe cada una de %.2lf euros.\n", prod.descrip, prod.stock, prod.importe);
    }

    return aux;
}

void consultaProdAdmin(){

    system("cls");

    int op, encontrado;
    char idProd[ID];

    do{
        printf ("\tApartado de Productos\n");
        printf ("(1) Consultar informacion de los productos.\n");
        printf ("(2) Dar de alta un producto.\n");
        printf ("(3) Dar de baja un producto.\n");
        printf ("(4) Buscar producto por nombre.\n");
        printf ("(5) Buscar producto por categoria.\n");
        printf ("(6) Modificar un producto.\n");
        printf ("(7) Volver.\n");

        if((scanf("%d", &op) != 1) || (op < 1 || op > 7)){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Opcion no contemplada. Pruebe de nuevo.\n\n");
            system("pause");
        }else{
            fflush(stdin);
            switch(op){
            case 1: infoProdAdmin(); break;
            case 2: darAltaProd(); break;
            case 3: darBajaProd(); break;
            case 4: buscarNombreProd(idProd, &encontrado); break;
            case 5: buscarCatProd(); break;
            case 6: modProdAdmin(); break;
            case 7: break;
            default: fprintf(stderr, "Opcion no contemplada"); break;
            }
        }


    }while(op < 1 || op > 7);
}

static void infoProdAdmin(){      

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

    system("cls");
    unsigned num = numProd();
    tProductos NuevoProd;

    generarID(NuevoProd.id_prod, num, ID-1);
    getDescripcion(NuevoProd.descrip);
    getIDcateg(NuevoProd.id_categ);
    getIDgestor(NuevoProd.id_gestor);         
    getStock(&NuevoProd.stock);
    getEntrega(&NuevoProd.entrega);
    getImporte(&NuevoProd.importe);

    fflush(stdin);

    guardarNuevoProducto("../datos/Productos.txt", NuevoProd);

    printf("Producto guardado con exito!.\n");
    system("pause");

}

static void darBajaProd(){
    system ("cls");

    int idNum;
    unsigned num = numProd();

    tProductos *Productos;

    Productos = (tProductos*)malloc(num*sizeof(tProductos));
    cargarProductos(Productos);

    do{
        imprimirProductos();

        printf("\n\nIndique la ID del producto a eliminar (formato 1, 2, ...): ");
        if (scanf("%d", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n");
        }else{
            if(idNum > num)
                printf("No existe producto con ID: %d.", idNum);
            else{
                idNum--;
                // eliminar producto de idNum y reemplazar posiciones
                for(; idNum < num-1; idNum++){
                    Productos[idNum] = Productos[idNum+1];      // reemplazamos
                    generarID(Productos[idNum].id_prod, idNum, ID-1);
                }

                recrearFicheroProductos(Productos, num-1);
            }
        }

        do{
            printf("Desea eliminar otro producto?\n");
            printf("(1) Si.\n(2) No.\n");
            printf("Elige opcion: ");

            if(scanf("%d", &idNum) != 1){
                system("cls");
                fflush(stdin);
                fprintf(stderr, "Entrada no valida.\n\n");
            }
        }while(idNum != 1 && idNum != 2);   
    }while(idNum == 1);

    free(Productos);
}

static void imprimirProductos(){
    FILE *fp;

    fp = fopen("../datos/Productos.txt", "r");

    if(fp == NULL){
        fprintf(stderr, "Error en la apertura de fichero.\n");
        exit(1);
    }

    char temp[MAX_LIN_FICH_PROD];

    printf("\tListado de Productos:\n\n");

    while(fgets(temp, MAX_LIN_FICH_PROD, fp) != NULL)
    printf("%s", temp);

    fclose(fp);
}

static void modProdAdmin(){
    system("cls");

    int idNum;
    unsigned num = numProd();
    tProductos original;
    tProductos *Productos;

    Productos = (tProductos*)malloc(num*sizeof(tProductos));

    if(Productos == NULL){
        fprintf(stderr, "Error al asignar memoria.\n");
        exit(1);
    }
    cargarProductos(Productos);

    do{
        imprimirProductos();

        printf("\n\nIndique la ID del producto a modificar (formato 1, 2, 3...): ");

        if(scanf("%d", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        }else{
            // Si la ID introducida es mayor al numero de productos en el sistema entonces no existe
            if(idNum > num){
                printf("No existe un producto con ID: %d.\n", idNum);
            }else{
                idNum--;

                original = Productos[idNum];

                printf("\nDatos del producto buscado: ");
                printf("%s-%s-%s-%s-%d-%d-%lf", Productos[idNum].id_prod, Productos[idNum].descrip, Productos[idNum].id_categ,
                                                Productos[idNum].id_gestor, Productos[idNum].stock, Productos[idNum].entrega,
                                                Productos[idNum].importe);

                int op;

                do{
                    printf("\nOpciones de modificacion (PRODUCTOS): \n\n");
                    printf("1. Modificar descripcion.\n");
                    printf("2. Modificar categoria.\n");
                    printf("3. Modificar gestor.\n");
                    printf("4. Modificar stock.\n");
                    printf("5. Modificar entrega.\n");
                    printf("6. Modificar importe.\n");
                    printf("7. Volver.\n");
                    printf("Elige opcion: ");

                    if(scanf("%d", &op) != 1 || op < 1 || op > 6){
                        system("cls");
                        fflush(stdin);
                        fprintf(stderr, "Entrada no valida.\n\n");
                    }else{
                        switch(op){
                            case 1: getDescripcion(Productos[idNum].descrip); break;
                            case 2: getIDcateg(Productos[idNum].id_categ); break;
                            case 3: getIDgestor(Productos[idNum].id_gestor); break;
                            case 4: getStock(&Productos[idNum].stock); break;
                            case 5: getEntrega(&Productos[idNum].entrega); break;
                            case 6: getImporte(&Productos[idNum].importe); break;
                            case 7: break;
                            default: fprintf(stderr, "Opcion no contemplada.\n"); exit(1);
                        }

                        system("cls");
                    }

                }while(op < 1 || op > 7);

            }

            // si se ha producido algun cambio, es necesario modificar Productos.txt
            if(existeCambiosProductos(Productos[idNum], original) && idNum <= num){
                modificarFicheroProductos(Productos[idNum]);
                printf("Producto modificado.\n");
            }
        }

        printf("\nDesea buscar otro producto?\n");
        printf("(1) Si.\n");
        printf("(2) No.\n");
        printf("Elige opcion: ");

        if(scanf("%d", &idNum) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida");
        }

    }while(idNum == 1);

    free(Productos);
}

static int existeCambiosProductos(tProductos nuevo, tProductos original){
    int boole = 1;

    if(nuevo.descrip == original.descrip && nuevo.id_categ == original.id_categ && nuevo.id_gestor == original.id_gestor
       && nuevo.stock == original.stock && nuevo.entrega == original.entrega && nuevo.importe == original.importe)
       boole = 0;

    return boole;
}

static void modificarFicheroProductos(tProductos productoMod){
    FILE *fp, *temp;
    char buffer[MAX_LIN_FICH_PROD];
    char *fich = "../datos/Productos.txt";
    char *fichTemp = "../datos/Temp-Productos.txt";

    fp = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(fp == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    // Buscar la ID en el fichero y cambiar la linea por los datos de productoMod
    while(fgets(buffer, MAX_LIN_FICH_PROD, fp) != NULL){
        char idFich[ID];

        strncpy(idFich, buffer, ID);          // En id se almacena los 8 primeros caracteres de cada linea

        // En temp se guardara el fichero modificado

        if(strncmp(idFich, productoMod.id_prod, ID-1) == 0){
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numProd
            if(numProd() == atoi(idFich))
                fprintf(temp, "%s-%s-%s-%s-%d-%d-%lf", productoMod.id_prod, productoMod.descrip, productoMod.id_categ,
                                                       productoMod.id_gestor, productoMod.stock, productoMod.entrega,
                                                       productoMod.importe);

            else
                fprintf(temp, "%s-%s-%s-%s-%d-%d-%lf\n", productoMod.id_prod, productoMod.descrip, productoMod.id_categ,
                                                       productoMod.id_gestor, productoMod.stock, productoMod.entrega,
                                                       productoMod.importe);        
        }else
            fprintf(temp, "%s", buffer);
    }

    // cerramos ficheros

    fclose(fp);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar fp
    remove(fich);
    rename(fichTemp, fich);
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

    system("cls");

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

    num = 2;

    //num = lenCategorias();

    Categorias *cat;

    cat = (Categorias*)malloc(num*sizeof(Categorias));

    if(cat == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    do{
        aux = 0;                          // Para que en cada iteracion vuelva a tomar el valor 0 y no nos de un falso encontrado
        op = 0;                           //      "           "             "             "                           resultado
        printf("Introduce la ID de la categoria (formato 0000): ");
        fgets(id, ID_PROD, stdin);
        cambio(id);                       // Quito el salto de linea del \n y meto un \0
        fflush(stdin);

        if(strlen(id) != ID_PROD-1){
            fprintf(stderr, "La longitud del ID es distinta a la requerida, pruebe de nuevo.\n");
            aux = 2;                // Para que no entre en el bucle
            //op = 1;                 // Para que se repita
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
            do{
                printf ("Quiere probar otra vez? (1) Si (2) No.\n");
                printf ("Elige opcion: ");
                if (scanf("%d", &op) != 1){
                    fprintf (stderr, "Opcion no contemplada. Pruebe de nuevo.\n");
                    system("pause");
                }
                fflush(stdin);
            }while(op < 1 || op > 2);
        }

        system("cls");

        rewind(f_categorias);       // Puntero al inicio del fichero

        if(op == 2)
            break;          //Para que no continue la ejecucion de las siguientes funciones en darAltaProd

    }while(op == 1);

    fclose(f_categorias);
    free(cat);

}

static void getIDgestor(char *idNProd){                 

    char id[ID_PROD], temp[MAX_LIN_FICH_ADMINPROV], del[] = "-";
    int op, i, aux, c;
    unsigned num;

    fflush(stdin);

    FILE *f_adminprov;

    f_adminprov = fopen("../datos/AdminProv.txt", "r");

    if (f_adminprov == NULL){
        fprintf (stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    num = numAdminProvs();
    
    tAdminProv *adminprov;

    adminprov = (tAdminProv*)malloc(num*sizeof(tAdminProv));

    if (adminprov == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    do{
        aux = 0;
        op = 0;
        printf ("Introduce el ID del gestor (formato 0000): ");
        fgets(id, MAX_LIN_FICH_ADMINPROV, stdin);
        cambio(id);
        fflush(stdin);

        if(strlen(id) != ID_PROD-1){
            fprintf(stderr, "La longitud del ID es distinta a la requerida, pruebe de nuevo.\n");
            aux = 2;                // Para que no entre en el bucle
        }

        // Limpiar el búfer de entrada  
        while ((c = getchar()) != '\n' && c != EOF);            // Si no se hace esto hay fallos en el programa

        for(i = 0; i < num && aux == 0; i++){
            if(fgets(temp, MAX_LIN_FICH_ADMINPROV, f_adminprov) != NULL){
                
                cambio(temp);                      // Quito el salto de linea del \n y meto un \0
                //printf("Linea leida : %s.\n", temp);

                dividirCadenaAdminProv(temp, del, &adminprov[i]);        // Guardo en las estructuras los datos del fichero AdminProv.txt     

                if(strcmp(id, adminprov[i].Id_empresa) == 0){
                    strcpy(idNProd, id);
                    aux = 1;                                    // Variable que me permite salir del bucle y me dice si he encontrado o no al gestor
                }
            }
        }

        if (aux != 1){              // No se ha encontrado ninguna categoria
            fprintf (stderr, "El gestor introducido no existe.\n");
            do{
                printf ("Quiere probar otra vez? (1) Si (2) No.\n");
                printf ("Elige opcion: ");
                if (scanf("%d", &op) != 1){
                    fprintf (stderr, "Opcion no contemplada. Pruebe de nuevo.\n");
                    system("pause");
                }
                fflush(stdin);
            }while(op < 1 || op > 2);
        }

        system("cls");

        rewind(f_adminprov);       // Puntero al inicio del fichero

        if(op == 2)
            break;          //Para que no continue la ejecucion de las siguientes funciones en darAltaProd

    }while(op == 1);

    fclose(f_adminprov);
    free(adminprov);

}

static void getStock(int *stock){
    int num, op;

    do{
        op = 0;
        printf("Introduce el stock disponible del producto: ");
        if(scanf ("%d", &num) != 1){
            fprintf(stderr, "Valor no valido, pruebe de nuevo.\n");
            op = 1;
        }else{
            if(num < 0){
                fprintf(stderr, "El stock no puede ser negativo, pruebe de nuevo.\n");
                op = 1;
                system("pause");
            }else
                *stock = num;
        }

        system("cls");
        
    }while(op == 1);

}

static void getEntrega(int *entrega){
    int num;
    int op;

    fflush(stdin);

    do{
        op = 0;
        printf("Introduce el numero de dias maximo de la entrega: ");
        if(scanf ("%d", &num) != 1){
            fprintf(stderr, "Valor no valido, pruebe de nuevo.\n");
            op = 1;
        }

        if(num < 0){
            fprintf(stderr, "La entrega no puede ser negativa, pruebe de nuevo.\n");
            op = 1;
            system("pause");
        }else
            *entrega = num;

        system("cls");
        
    }while (op == 1);

}

static void getImporte(double *importe){
    double num;
    int op;

    fflush(stdin);

    do{
        printf("Introduce el importe del producto: ");
        if(scanf("%lf", &num) != 1){
            fprintf(stderr, "Valor no valido, pruebe de nuevo.\n");
            op = 1;
        }

        if(num < 0){
            fprintf(stderr, "El importe no puede ser negativo, pruebe de nuevo.\n");
            op = 1;
            system("pause");
        }else
            *importe = num;

        system("cls");
        
    }while(op == 1);

}

static void dividirCadenaAdminProv(char temp[], char del[], tAdminProv *adminProv){
    // Divido la cadena mediante su delimitador y la almaceno en la estructura
    char *p1 = strtok (temp, del);
    sprintf(adminProv->Id_empresa, "%s", p1);

    char *p2 = strtok (NULL, del);
    sprintf(adminProv->Nombre, "%s", p2);

    char *p3 = strtok (NULL, del);
    sprintf(adminProv->email, "%s", p3);

    char *p4 = strtok (NULL, del);
    sprintf(adminProv->Contrasenia, "%s", p4);
        
    char *p5 = strtok (NULL, del);
    sprintf(adminProv->Perfil_usuario, "%s", p5);
}

void cargarProductos(tProductos *prod){
    unsigned i;
    char temp[MAX_LIN_FICH_PROD];

    if(numProd() != 0){    // Comprobamos si existe algún producto en Productos.txt
        FILE *fp;

        fp = fopen("../datos/Productos.txt", "r");    // Abrimos el fichero en tipo lectura.

        if(fp == NULL){     // Comprobamos si su apertura es correcta.
            fprintf(fp, "Error en la apertura de archivos.\n");
            exit(1);
        }

        for(i = 0; i < numProd(); i++){   // Recorremos el vector
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH_PROD es el máximo que ocupara cada línea de Productos.txt
            if(fgets(temp, MAX_LIN_FICH_PROD, fp) != NULL){
                cambio(temp);
                sscanf(temp, "%[^-]-%[^-]-%[^-]-%[^-]-%i-%i-%lf", prod[i].id_prod, prod[i].descrip, prod[i].id_categ,
                                                                        prod[i].id_gestor, &prod[i].stock, &prod[i].entrega, &prod[i].importe);
            }
        }

        fclose(fp); // Cerramos fichero.
    }
}


void cambio(char *temp){
    if (temp[strlen(temp) - 1] == '\n') // Ver si hay un salto de linea al final y reemplazarla con '\0'
        temp[strlen(temp) - 1] = '\0';
}

static void guardarNuevoProducto(char *destino, tProductos datos){
    FILE *fp;

    fp = fopen(destino, "a");   // append

    if(fp == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }
    
    fprintf(fp, "\n%s-%s-%s-%s-%d-%d-%lf", datos.id_prod, datos.descrip, datos.id_categ,
                                       datos.id_gestor, datos.stock, datos.entrega, datos.importe);

    fclose(fp);
}

void recrearFicheroProductos(tProductos *productos, unsigned numProd){
    FILE *fp, *temp;
    char *fich = "../datos/Productos.txt";
    char *fichTemp = "../datos/Temp-Productos.txt";

    fp = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if (fp == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    int i;

    for(i = 0; i < numProd; i++){
        if (i+1 == numProd)
            fprintf(temp, "%s-%s-%s-%s-%d-%d-%lf", productos[i].id_prod, productos[i].descrip, productos[i].id_categ,
                                                   productos[i].id_gestor, productos[i].stock, productos[i].entrega,
                                                    productos[i].importe);
        else
            fprintf(temp, "%s-%s-%s-%s-%d-%d-%lf\n", productos[i].id_prod, productos[i].descrip, productos[i].id_categ,
                                                   productos[i].id_gestor, productos[i].stock, productos[i].entrega,
                                                    productos[i].importe);
    }

    // cerramos ficheros
    fclose(fp);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar fp

    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
}
