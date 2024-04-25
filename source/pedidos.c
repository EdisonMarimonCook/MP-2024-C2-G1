#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pedidos.h"
#include "productos.h"
#include "clientes.h"   // ID
#include "usuarios.h"
#include "adminprov.h"
#include "descuentosClientes.h"

void consultaPedidosCli(tCliente *cli){
    system("cls");

    int op;

    do{
        printf("\tApartado de Pedidos\n");
        printf("(1) Realizar un pedido.\n");
        printf("(2) Consultar estado de mis pedidos.\n");
        printf("(3) Salir.\n");
        printf("Elige opcion: ");

        if((scanf("%d", &op) != 1) || (op < 1 || op > 3)){
            fprintf(stderr, "Opcion no contemplada, pruebe de nuevo.\n");
            system("pause");
        }else{
            switch(op){
                case 1: realizarPedido(cli); break;
                case 2: estadoPedidos(cli); break;                       
                case 3: break;
                default: fprintf(stderr, "Ha ocurrido un error.\n"); exit(1);
            }
        }
    }while(op < 1 || op > 3);

}

void consultaPedidosAdmin(tAdminProv *admin){
    system("cls");

    int op;

    do{
        printf("\tApartado de Pedidos\n");
        printf("(1) Consultar informacion de los productos.\n");
        printf("(2) Dar de alta un pedido.\n");
        printf("(3) Dar de baja un pedido.\n");
        printf("(4) Modificar un pedido.\n");
        printf("(5) Volver.\n");
        printf("Elige opcion: ");

        if(scanf("%d", &op) != 1 || op < 1 || op > 5){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Opcion no contemplada. Pruebe de nuevo.\n");
            system("pause");
        }else{
            printf("La opcion elegida es: %d.\n", op);
            system("pause");
            switch(op){
                case 1: infoPedAdmin(); break;          // NO FUNCIONA
                case 2: AltaPedidoAdmin(*admin); break;
                case 3: darBajaPedido(); break;
                case 4: modPedAdmin(); break;
                case 5: break;
                default: fprintf(stderr, "Opcion no contemplada.\n"); break;
            }
        }
    }while(op < 1 || op > 5);
}

static void infoPedAdmin(){
    system("cls");

    int i;
    unsigned num = numPedidos();
    char temp[MAX_LIN_FICH_PED], del[] = "-";

    FILE *fPedidos;

    fPedidos = fopen("../datos/Pedidos.txt", "r");

    if(fPedidos == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    tPedidos *pedidos;

    pedidos = (tPedidos*)malloc(num*sizeof(tPedidos));

    if(pedidos == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    fflush(stdin);

    printf("Se ejecuta?.\n");
    system("pause");

    for(i = 0; i < num; i++){   //Recorremos el vector
        //Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH_PED es el máximo que ocupara cada línea de Pedidos.txt
        if(fgets(temp, MAX_LIN_FICH_PED, fPedidos) != NULL){
            cambio(temp);       //Quito el salto de linea

            dividirCadenaPed(temp, del, &pedidos[i]);

            printf("\nId pedido: %s, fecha de entrega: %.02d/%.02d/%.02d, id cliente: %s lugar de recogida: %s, id descuento: %s",
                    pedidos[i].id_pedido, pedidos[i].fecha[0], pedidos[i].fecha[1], pedidos[i].fecha[2], pedidos[i].id_cliente, 
                    pedidos[i].lugar, pedidos[i].id_cod);
        }
    }

    fclose(fPedidos);
    free(pedidos);

    system("pause");
}

static void AltaPedidoAdmin(tAdminProv admin){
    system("cls");
    unsigned num = numPedidos();
    int aux = 0, op, reparto;
    char *entrega, temp[DES], *cod, idtemp[ID];

    tPedidos NuevoPedido;

    do{
        printf("Donde va a ser la entrega del pedido?: \n");
        printf("(1) Domicilio.\n");
        printf("(2) Locker.\n");
        printf("Elige opcion: ");
        if((scanf("%d", &op) != 1) || (op < 1 || op > 2)){
            fprintf(stderr, "Opcion no contemplada, pruebe de nuevo.\n");
            aux = 1;
            system("pause");
            system("cls");
        }
    }while(aux == 1);
    fflush(stdin);

    if(op != 1)
        strcpy(entrega, "Locker");
    else
        strcpy(entrega, "Domicilio");

    do{
        printf("En cuantos dias sera la entrega?: ");
        if(scanf("%d", &reparto) != 1){
            fprintf(stderr, "Entrada no valida.\n");
            exit(1);
        }
    }while(reparto < 0);

    printf("Pulse 1 si quieres aplicar un codigo promocional o cheque regalo: ");
    if(scanf("%d", &op) != 1){
        fprintf(stderr, "Formato no valido.\n");
        exit(1);
    }

    if(op == 1){
        printf("Introduce el codigo: ");
        fgets(temp, DES, stdin);
        cambio(temp);
        fflush(stdin);

        cod = (char*)malloc(strlen(temp)+1*sizeof(char));

        if(cod == NULL){
            fprintf(stderr, "No se ha podido asignar memoria.\n");
            exit(1);
        }

        strcpy(cod, temp);
    }

    do{
        printf("Introduce el ID del cliente asociado al pedido (formato 0000001): ");
        fgets(idtemp, ID, stdin);
        cambio(idtemp);
        fflush(stdin);
    }while(strlen(idtemp) != ID-1);

    generarID(NuevoPedido.id_pedido, num, ID-1);
    generarFecha(NuevoPedido.fecha, reparto);
    strcpy(NuevoPedido.id_cliente, idtemp);

    if(op == 1)
        strcpy(NuevoPedido.id_cod, cod);
    else
        strcpy(NuevoPedido.id_cod, "\0");


    fflush(stdin);

    guardarNuevoPedido("../datos/Pedidos.txt", NuevoPedido);

    printf("Pedido realizado con exito!.\n");
    printf("Este es el identificador de su pedido: %s.\n", NuevoPedido.id_pedido);
    printf("Guardelo para poder realizar el seguimiento de su pedido.\n");
    printf("Una vez que el pedido es entregado el identificador ya no servira.\n");
    system("pause");
}

static void darBajaPedido(){
    system("cls");

    int idNum;

    unsigned num = numPedidos();

    tPedidos *Pedidos;

    Pedidos = (tPedidos*)malloc(num*sizeof(tPedidos));
    cargarPedidos(Pedidos);

    do{
        imprimirPedidos();

        printf("Indique la ID del pedido a eliminar (formato 1, 2, ...): ");
        if(scanf("%d", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n");
        }else{
            if(idNum > num)
                printf("No existe pedido con ID: %d.", idNum);
            else{
                idNum--;
                // eliminar pedido de idNum y reemplazar posiciones
                for(; idNum < num-1; idNum++){
                    Pedidos[idNum] = Pedidos[idNum+1];      // reemplazamos
                    generarID(Pedidos[idNum].id_pedido, idNum, ID-1);
                }

                recrearFicheroPedidos(Pedidos, num-1);
            }
        }
        

        do{
            printf("Desea eliminar otro pedido?\n");
            printf("(1) Si.\n(2) No.\n");
            printf("Elige opcion: ");

            if(scanf("%d", &idNum) != 1){
                system("cls");
                fflush(stdin);
                fprintf(stderr, "Entrada no valida.\n\n");
            }
        }while(idNum != 1 && idNum != 2);   
    }while(idNum == 1);

    free(Pedidos);
}

static void modPedAdmin(){
    system("cls");
    
    int idNum;
    unsigned num = numPedidos();
    tPedidos original;
    tPedidos *Pedidos;

    Pedidos = (tPedidos*)malloc(num*sizeof(tPedidos));

    if(Pedidos == NULL){
        fprintf(stderr, "Error al asignar memoria.\n");
    }

    cargarPedidos(Pedidos);

    do {
        imprimirPedidos();

        printf("\n\nIndique la ID del pedido a modificar(formato 1, 2, ...): ");
        
        if(scanf("%d", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de pedidos en el sistema entonces no existe
            if(idNum > num)
                printf("No existe el pedido con ID: %i.", idNum);
            else{
                idNum--;

                original = Pedidos[idNum];

                printf("\nDatos del pedido buscado: ");
                printf("%s-%.02d/%.02d/%.02d-%s-%s-%s", Pedidos[idNum].id_pedido, Pedidos[idNum].fecha[0], Pedidos[idNum].fecha[1],
                                                         Pedidos[idNum].fecha[2], Pedidos[idNum].id_cliente, Pedidos[idNum].lugar, Pedidos[idNum].id_cod);

                unsigned op;

                do {
                    printf("\nOpciones de modificacion (PEDIDOS):\n\n");
                    printf("1. Modificar fecha de entrega.\n");
                    printf("2. Modificar lugar de recogida.\n");
                    printf("3. Volver.\n\n");

                    printf("Inserte la opcion: ");

                    if(scanf("%u", &op) != 1 || op < 1 || op > 6){
                        system("cls");
                        fflush(stdin);
                        fprintf(stderr, "Entrada no valida\n\n");
                    } else{
                        switch(op){
                            case 1: nuevaFecha(Pedidos[idNum].fecha);
                            case 2: nuevoLugar(Pedidos[idNum].lugar); break;
                            case 3: break;
                            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
                        }

                        system("cls");
                    }

                } while(op < 1 || op > 3);       
            }

            // si se ha producido algun cambio, es necesario modificar Pedidos.txt
            if(existeCambioPedidos(Pedidos[idNum], original) && idNum <= numPedidos()){
                modificarFicheroPedidos(Pedidos[idNum]);
                printf("Pedido modificado.\n");
            }
        }

        printf("\nDesea modificar otro pedido? (1 = si, 0 = no): ");

        if(scanf("%d", &idNum) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        }

    } while(idNum != 1);

    free(Pedidos);

}

static int existeCambioPedidos(tPedidos nuevo, tPedidos original){
    int boole;

    if(nuevo.fecha[0] == original.fecha[0] && nuevo.fecha[1] == original.fecha[1] && nuevo.fecha[2] == original.fecha[2]
        && nuevo.lugar == original.lugar)
        boole = 0;

    return boole;
}

static void modificarFicheroPedidos(tPedidos pedidoMod){
    FILE *fp, *temp;

    char buffer[MAX_LIN_FICH_PED];
    char *fich = "../datos/Pedidos.txt";
    char *fichTemp = "../datos/Temp-Pedidos.txt";

    fp = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if (fp == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    // Buscar la ID en el fichero y cambiar la linea por los datos de pedidoMod
    while(fgets(buffer, MAX_LIN_FICH_PED, fp) != NULL){
        char idFich[ID];

        strncpy(idFich, buffer, ID);        // En id se almacenan los 8 primeros caracteres de cada linea

        // En temp se guardara el fichero modificado

        if(strncmp(idFich, pedidoMod.id_pedido, ID-1) == 0){
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numPedidos
            if(numPedidos() == atoi(idFich))
                fprintf(temp, "%s-%.02d/%.02d/%.02d-%s-%s-%s", pedidoMod.id_pedido, pedidoMod.fecha[0], pedidoMod.fecha[1],
                                                            pedidoMod.fecha[2], pedidoMod.id_cliente, pedidoMod.lugar, pedidoMod.id_cod);
                
                else
                fprintf(temp, "%s-%.02d/%.02d/%.02d-%s-%s-%s\n", pedidoMod.id_pedido, pedidoMod.fecha[0], pedidoMod.fecha[1],
                                                            pedidoMod.fecha[2], pedidoMod.id_cliente, pedidoMod.lugar, pedidoMod.id_cod);
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

static void nuevaFecha(int *fecha){
    int dias;

    do{
        printf("Introduce el numero de dias para la entrega del pedido: ");
        if(scanf("%d", &dias) != 1){
            fprintf(stderr, "Entrada no valida.\n");
            exit (1);
        }
    }while (dias < 0);

    generarFecha(fecha, dias);
}

static void nuevoLugar(char *lugar){
    if(strcmp(lugar, "Domicilio") == 0)
        strcpy(lugar, "Locker");
    else
        strcpy(lugar, "Domicilio");
}

static void cargarPedidos(tPedidos *pedidos){
    unsigned i;
    char temp[MAX_LIN_FICH_PED];

    if(numProd() != 0){         // Comprobamos si existen pedidos
        FILE *fp;

        fp = fopen("../datos/Pedidos.txt", "r");        //Abrimos el fichero modo lectura

        if(fp == NULL){
            fprintf(stderr, "Error en la apertura de ficheros.\n");
            exit(1);
        }

        for(i = 0; i < numPedidos(); i++){
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH_PED es el máximo que ocupara cada línea de Pedidos.txt
            if(fgets(temp, MAX_LIN_FICH_PED, fp) != NULL){
                cambio(temp);
                sscanf(temp, "%[^-]-%i/%i/%i-%[^-]-%[^-]-%[^-]", pedidos->id_pedido, pedidos->fecha[0], pedidos->fecha[1],
                                                                pedidos->fecha[2], pedidos->id_cliente, pedidos->lugar, pedidos->id_cod);

            }
        }

        fclose(fp);     // Cerramos fichero
    }
}

static void imprimirPedidos(){
    FILE *fp;

    fp = fopen("../datos/Pedidos.txt", "r");

    if(fp == NULL){
        fprintf(stderr, "Error en la apertura de fichero.\n");
        exit(1);
    }

    char temp[MAX_LIN_FICH_PED];

    printf("\tListado de Pedidos:\n\n");

    while(fgets(temp, MAX_LIN_FICH_PED, fp) != NULL)
    printf("%s", temp);
    
    fclose(fp);
}

static void recrearFicheroPedidos(tPedidos *pedidos, unsigned numPedidos){
    FILE *fp, *temp;

    char *fich = "../datos/Pedidos.txt";
    char *fichTemp = "../datos/Temp-Pedidos.txt";

    fp = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(fp == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    int i;

    for(i = 0; i < numPedidos; i++){
        if (i+1 == numProd())
            fprintf(temp, "%s-%.02d/%.02d/%.02d-%s-%s-%s", pedidos[i].id_pedido, pedidos[i].fecha[0], pedidos[i].fecha[1],
                                                        pedidos[i].fecha[2], pedidos[i].id_cliente, pedidos[i].lugar,
                                                        pedidos[i].id_cod);
        else
            fprintf(temp, "%s-%.02d/%.02d/%.02d-%s-%s-%s\n", pedidos[i].id_pedido, pedidos[i].fecha[0], pedidos[i].fecha[1],
                                                        pedidos[i].fecha[2], pedidos[i].id_cliente, pedidos[i].lugar,
                                                        pedidos[i].id_cod);
    }

    // cerramos ficheros
    fclose(fp);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar fp

    remove(fich);
    rename(fichTemp, fich);
}

static void realizarPedido(tCliente *cliente){
    char idProd[ID], *cod, temp[DES];
    int id, encontrado = 0, op;
    float descuento = 0.0;

    tProductos *Productos;

    Productos = (tProductos*)malloc(numProd()*sizeof(tProductos));
    cargarProductos(Productos);

    buscarNombreProd(idProd, &encontrado);

    if(encontrado == 1){
        fprintf(stderr, "No se puede pedir un articulo que se encuentra sin stock.\n");
    }else{
        id = atof(idProd);          // Para que la id (0001) p.e se convierta en 1

        printf("Pulse 1 si quieres aplicar un codigo promocional o cheque regalo: ");
        if(scanf("%d", &op) != 1){
            fprintf(stderr, "Formato no valido.\n");
            exit(1);
        }

        if(op == 1){
            printf("Introduce el codigo: ");
            fgets(temp, DES, stdin);
            cambio(temp);
            fflush(stdin);

            cod = (char*)malloc(strlen(temp)+1*sizeof(char));

            if(cod == NULL){
                fprintf(stderr, "No se ha podido asignar memoria.\n");
                exit(1);
            }

            strcpy(cod, temp);
        }

        //descuento = obtenerDescuento(cliente->Id_cliente, cod);       //NO FUNCIONA LA FUNCION
        // Si el descuento que el cliente ha introducido esta activo me devuelve la cantidad del descuento
        // en otro caso, me devuelve 0.

        printf("Descuento aplicado de %f euros.\n", descuento);

        Productos[id].importe = Productos[id].importe - descuento;

        cliente->Cartera = cliente->Cartera - Productos[id].importe;

        if(cliente->Cartera < 0){
            fprintf(stderr, "No tienes suficiente saldo disponible.\n");
        }else{
            Productos[id].stock = Productos[id].stock - 1;
            recrearFicheroProductos(Productos, numProd());
            modificarFicheroClientes(*cliente);
            printf("Llega aqui? SI\n");
            system("pause");

            darAltaPedido(*cliente, Productos[id].entrega, cod);
            printf("Pedido realizado con exito.\n");
        }

    }
    free(Productos);
    free(cod);

    system("pause");
    system("cls");

}

unsigned numPedidos(){
    char buffer[MAX_LIN_FICH_PED];
    unsigned cont = 0;

    FILE *f_pedidos;
    f_pedidos = fopen("../datos/Pedidos.txt", "r");
    if(f_pedidos == NULL){
        fprintf(stderr, "No se ha podido abrir el fichero.\n");
        exit(1);
    }

    vaciar(buffer);

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(f_pedidos)){
        fgets(buffer, MAX_LIN_FICH_CLI, f_pedidos);
        cont++;
    }

    if (fseek(f_pedidos, 0, SEEK_END) != 0){          //Puntero al principio del fichero
        fprintf(stderr, "Ha ocurrido un error en el fichero.\n");
        exit(1);
    }
    fputs("\n", f_pedidos);                           

    fclose(f_pedidos);

    return cont;
}

static void darAltaPedido(tCliente Cliente, int reparto, char *cod){
    system("cls");
    unsigned num = numPedidos();
    int aux = 0, op;
    char *entrega;

    printf("LLega aqui? NO LLEGA.\n");
    system("pause");

    tPedidos NuevoPedido;

    do{
        printf("Donde desea que se le entregue el pedido?: \n");
        printf("(1) Domicilio.\n");
        printf("(2) Locker.\n");
        printf("Elige opcion: ");
        if((scanf("%d", &op) != 1) || (op < 1 || op > 2)){
            fprintf(stderr, "Opcion no contemplada, pruebe de nuevo.\n");
            aux = 1;
            system("pause");
            system("cls");
        }
    }while(aux == 1);
    fflush(stdin);

    if(op != 1)
        strcpy(entrega, "Locker");
    else
        strcpy(entrega, "Domicilio");

    system("pause");

    generarID(NuevoPedido.id_pedido, num, ID-1);
    generarFecha(NuevoPedido.fecha, reparto);
    strcpy(NuevoPedido.id_cliente, Cliente.Id_cliente);
    strcpy(NuevoPedido.lugar, entrega);
    if(op == 1)
        strcpy(NuevoPedido.id_cod, cod);
    else
        strcpy(NuevoPedido.id_cod, "\0");
    

    fflush(stdin);

    guardarNuevoPedido("../datos/Pedidos.txt", NuevoPedido);

    printf("Pedido realizado con exito!.\n");
    printf("Este es el identificador de su pedido: %s.\n", NuevoPedido.id_pedido);
    printf("Guardelo para poder realizar el seguimiento de su pedido.\n");
    printf("Una vez que el pedido es entregado el identificador ya no servira.\n");
    system("pause");

    free(entrega);
}

static void generarFecha(int *fecha, int reparto){
    time_t tiempoActual;
    struct tm *fechaActual;

    // Obtener el tiempo actual
    tiempoActual = time(NULL);
    fechaActual = localtime(&tiempoActual);

    // Almacenar día, mes y año actual en el vector
    fecha[0] = fechaActual->tm_mday;    // Día del mes
    fecha[1] = fechaActual->tm_mon + 1; // Mes (se suma 1 porque en struct tm el rango de meses es 0-11)
    fecha[2] = fechaActual->tm_year + 1900;  // Año (se suma 1900 porque struct tm cuenta los años desde 1900)

    fecha[0] = fecha[0] + reparto;

    if(fecha[0] > 30){
        fecha[0] = fecha[0] - 30;
        fecha[1]++;
    }

    if(fecha[1] > 12){
        fecha[1] = 1;
        fecha[2]++;
    }

    // HE SUPUESTO QUE EL TIEMPO DE ENTREGA NO VA A SER MAYOR DE 30 DIAS
}

static void guardarNuevoPedido(char *destino, tPedidos datos){
    FILE *fPedidos;

    fPedidos = fopen(destino, "a");   // append

    if(fPedidos == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }
    
    fprintf(fPedidos, "\n%s-%.02d/%.02d/%.02d-%s-%s-%s", datos.id_pedido, datos.fecha[0], datos.fecha[1],
                                                         datos.fecha[2], datos.id_cliente, datos.lugar, datos.id_cod);

    fclose(fPedidos);
}

static void estadoPedidos(tCliente *cliente){
   int i;
   unsigned num = numPedidos();
   char temp[MAX_LIN_FICH_PED], del[] = "-";

   FILE *fPedidos;

    fPedidos = fopen("../datos/Pedidos.txt", "r");

    if (fPedidos == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    tPedidos *Pedidos;

    Pedidos = (tPedidos*)malloc(num*sizeof(tPedidos));       //Creo tantas estructuras como pedidos existan

    if(Pedidos == NULL){
        fprintf(stderr, "No se ha podido reservar memoria.\n");
        exit(1);
    }

    for(i = 0; i < num; i++){
        if(fgets(temp, MAX_LIN_FICH_PED, fPedidos) != NULL){        // Recojo la linea
            
            cambio(temp);                      // Quito el salto de linea del \n y meto un \0
            
            dividirCadenaPed(temp, del, &Pedidos[i]);       // Guardo en las estructuras los datos del fichero Productos.txt
        }
    }

    for(i = 0; i < num; i++){
        if(strcmp(Pedidos[i].id_cliente, cliente->Id_cliente) == 0){
                idEncontrada(&Pedidos[i]);
        }
    }

    system("pause");
    system("cls");
    fflush(stdin);

    free(Pedidos);
    fclose(fPedidos); 
}

static void dividirCadenaPed(char *temp, char del[], tPedidos *pedido){
        // Divido la cadena mediante su delimitador y la almaceno en la estructura
    char *p1 = strtok (temp, del);
    sprintf(pedido->id_pedido, "%s", p1);

    char *p2 = strtok (NULL, "/");
    pedido->fecha[0] = atof(p2); 

    char *p3 = strtok (NULL, "/");
    pedido->fecha[1] = atof(p3);

    char *p4 = strtok (NULL, "/");
    pedido->fecha[2] = atof(p4);
        
    char *p5 = strtok (NULL, del);
    sprintf(pedido->id_cliente, "%s", p5);

    char *p6 = strtok (NULL, del);
    sprintf(pedido->lugar, "%s", p6);

    char *p7 = strtok (NULL, del);
    sprintf(pedido->id_cod, "%s", p7);
}

static void idEncontrada(tPedidos *pedido){
    printf("El pedido con id: %s tiene prevista su entrega el: %d/%d/%d.\n", pedido->id_pedido,
                                        pedido->fecha[0], pedido->fecha[1], pedido->fecha[2]);
}