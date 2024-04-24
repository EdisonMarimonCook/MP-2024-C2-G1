#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pedidos.h"
#include "productos.h"
#include "clientes.h"   // ID
#include "usuarios.h"
#include "adminprov.h"

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

static void realizarPedido(tCliente *cliente){
    char *nombreProd, idProd[ID];
    int id, encontrado = 0, op;

    tProductos *Productos;

    Productos = (tProductos*)malloc(numProd()*sizeof(tProductos));
    cargarProductos(Productos);

    buscarNombreProd(idProd, &encontrado);

    if(encontrado == 1){
        fprintf(stderr, "No se puede pedir un articulo que se encuentra sin stock.\n");
    }else{
        id = atof(idProd);          // Para que la id (0001) p.e se convierta en 1

        cliente->Cartera = cliente->Cartera - Productos[id].importe;

        if(cliente->Cartera < 0){
            fprintf(stderr, "No tienes suficiente saldo disponible.\n");
        }else{
            
            
            
            Productos[id].stock = Productos[id].stock - 1;
            recrearFicheroProductos(Productos, numProd());
            modificarFicheroClientes(*cliente);
            darAltaPedido(*cliente, Productos[id].entrega);
            printf("Pedido realizado con exito.\n");
        }

    }
    free(Productos);

    system("pause");
    system("cls");

}

static void recrearFicheroProductos(tProductos *Productos, unsigned numProd){
    FILE *fp, *temp;
    char *fich = "../datos/Productos.txt";
    char *fichTemp = "../datos/Temp-Productos.txt";

    fp = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(fp == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura del archivos.\n");
        exit(1);
    }

    unsigned i;

    for(i = 0; i < numProd; i++){
        if(i+1 == numProd){
            fprintf(temp, "%s-%s-%s-%s-%d-%d-%lf", Productos[i].id_prod, Productos[i].descrip, Productos[i].id_categ,
                                                   Productos[i].id_gestor, Productos[i].stock, Productos[i].entrega, Productos[i].importe);
        }else{
            fprintf(temp, "%s-%s-%s-%s-%d-%d-%lf\n", Productos[i].id_prod, Productos[i].descrip, Productos[i].id_categ,
                                                     Productos[i].id_gestor, Productos[i].stock, Productos[i].entrega, Productos[i].importe);
        }
    }

    // cerramos ficheros
    fclose(fp);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar pf
    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
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

static void darAltaPedido(tCliente Cliente, int reparto){
    system("cls");
    unsigned num = numPedidos();
    int op, aux = 0;
    char *cod, temp[DES], *entrega;

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

    generarID(NuevoPedido.id_pedido, num, ID-1);
    generarFecha(NuevoPedido.fecha, reparto);
    strcpy(NuevoPedido.id_cliente, Cliente.Id_cliente);
    strcpy(NuevoPedido.lugar, entrega);
    if(op == 1){
        strcpy(NuevoPedido.id_cod, cod);
    }else{
        strcpy(NuevoPedido.id_cod, "\0");
    }

    fflush(stdin);

    guardarNuevoPedido("../datos/Pedidos.txt", NuevoPedido);

    printf("Pedido realizado con exito!.\n");
    printf("Este es el identificador de su pedido: %s.\n", NuevoPedido.id_pedido);
    printf("Guardelo para poder realizar el seguimiento de su pedido.\n");
    printf("Una vez que el pedido es entregado el identificador ya no servira.\n");
    system("pause");
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