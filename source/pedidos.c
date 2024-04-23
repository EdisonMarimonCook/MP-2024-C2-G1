#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                case 2: //estadoPedidos(cli); 
                        break;                       
                case 3: break;
                default: fprintf(stderr, "Ha ocurrido un error.\n"); exit(1);
            }
        }
    }while(op < 1 || op > 3);
}

static void realizarPedido(tCliente *cliente){
    char *nombreProd, *temp, idProd[ID];
    int id, encontrado = 0;

    tProductos *Productos;

    Productos = (tProductos*)malloc(numProd()*sizeof(tProductos));
    cargarProductos(Productos);

    temp = buscarNombreProd(idProd, &encontrado);

    if(temp == NULL){
        fprintf(stderr, "No se ha podido asignar memoria.\n");
        exit(1);
    }

    if(encontrado == 1){
        fprintf(stderr, "No se puede pedir un articulo que se encuentra sin stock");
    }else{
        id = atof(idProd);          // Para que la id (0001) p.e se convierta en 1

        cliente->Cartera = cliente->Cartera - Productos[id].importe;

        if(cliente->Cartera < 0){
            fprintf(stderr, "No tienes suficiente saldo disponible");
        }else{
           /*nombreProd = (char*)malloc(strlen(temp)+1*sizeof(char));
            strcpy(nombreProd, temp);*/

            Productos[id].stock -= Productos[id].stock;
            recrearFicheroProductos(Productos, numProd());
        }

    }
    free(Productos);
    free(temp);
    
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