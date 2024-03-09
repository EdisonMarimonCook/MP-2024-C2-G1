#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usuarios.h"
#include "clientes.h"
#include "adminprov.h"

// TODO: acabar iniciarSesion

void iniciarSesion(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    int valdCli, valdAdPr, op = 0; 
    tCliente *infoClientes;
    tAdminProv *infoAdminProvs;
    char email[EMAIL], psw[PASS];

    infoClientes = crearListaClientes();
    cargarClientes(infoClientes);
    infoAdminProvs = crearListaAdminProv();
    cargarAdminProvs(infoAdminProvs);

    do {
        op = 0;

        printf("Usuario (direccion email): ");
        fflush(stdin);
        fgets(email, EMAIL, stdin);

        printf("Contrasena: ");
        fflush(stdin);
        fgets(psw, PASS, stdin);

        // es importante eliminar el \n para que no haya problemas
        // comprobando si es un inicio valido
        email[strcspn(email, "\n")] = 0;
        psw[strcspn(psw, "\n")] = 0;

        // comprobamos si el inicio es valido o no
        int validoCliente = inicioValidoClientes(infoClientes, email, psw);
        int validoAdminProv = inicioValidoAdminProv(infoAdminProvs, email, psw);

        if(validoCliente == 0 && validoAdminProv == 0){
            fprintf(stderr, "\nEl usuario o la contrasena no coinciden.\n\n");

            // manejo de opciones
            do {
                printf("\nDesea registrarse? (1) o intentarlo de nuevo (2): ");

                if(scanf("%i", &op) != 1 || op != 1 && op != 2){
                    fflush(stdin);
                    fprintf(stderr, "Entrada no valida.");
                }

            } while(op != 1 && op != 2);
        }

        valdCli = validoCliente;
        valdAdPr = validoAdminProv;

    } while(valdCli == 0 && valdAdPr == 0 && op != 1);

    // las funciones de inicio valido tanto para clientes como para adminProv devolvían la posición en el array
    int posC = valdCli-1;
    int posAP = valdAdPr-1;    
    tCliente cliente = infoClientes[posC];
    tAdminProv adminprov = infoAdminProvs[posAP];

    free(infoClientes);
    free(infoAdminProvs);

    if(op == 1)
        registrarCliente();    // linea 75 el usuario es preguntado por registrarse (opcion 1)
    else if(valdCli == 0 || valdAdPr == 0){
        if(valdCli)
            menuCliente(&cliente);      // menu principal de usuario cliente
        else if(valdAdPr)
            menuAdminProv(&adminprov);  // menu principal de usuario adminprov
    }
}
