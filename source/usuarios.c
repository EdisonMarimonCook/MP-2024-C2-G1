#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usuarios.h"
#include "clientes.h"   // tCliente
#include "adminprov.h"  // tAdminProv

void registrarProveedor(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    tAdminProv *datos = crearListaAdminProv(); 
    cargarAdminProvs(datos);
    unsigned nAdminProvs = numAdminProvs();

    if(nAdminProvs != 0)
        reservarAdminProv(datos);    // crearListaAdminProv si nAdminProvs es cero reserva 1 posicion

    // Obtenemos los datos del cliente
    generarID(datos[nAdminProvs].Id_empresa, nAdminProvs+1, ID_EMPRESA-1);
    getNombreProvedor(&datos[nAdminProvs]);
    getEmailAdminProv(&datos[nAdminProvs]);
    getContraseniaAdminProv(&datos[nAdminProvs]);
    strcpy(datos[nAdminProvs].Perfil_usuario, "proveedor");

    tAdminProv nuevoProveedor = datos[nAdminProvs];
    
    // liberamos memoria que ya no nos hace falta
    free(datos);    

    guardarDatosAdminProvFich("../datos/AdminProv.txt", nuevoProveedor);
}

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
        registrarse(CON_MENU);    // usuario es preguntado por registrarse (opcion 1)
    else if(valdCli == 0 || valdAdPr == 0){
        if(valdCli)
            menuCliente(&cliente);      // menu principal de usuario cliente
        else if(valdAdPr){
            if(strcmp("administrador", adminprov.Perfil_usuario) == 0)
                menuAdmin(&adminprov);      // menu principal de usuario admin
            else
                menuProveedor(&adminprov);   // menu principal de usuario proveedor
        }    
    }
}

void registrarse(int op){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    tCliente *datos;    // un usuario solo puede registrarse como cliente
    unsigned nClientes = numClientes();
 
    datos = crearListaClientes();
    cargarClientes(datos);

    if(nClientes != 0)
        reservarNuevoCliente(datos);    // crearListaCliente si nClientes es cero reserva 1 posicion

    // Obtenemos los datos del cliente
    generarID(datos[nClientes].Id_cliente, nClientes+1, ID-1);
    getNombre(&datos[nClientes]);
    getDireccion(&datos[nClientes]);
    getPoblacion(&datos[nClientes]);
    getProvincia(&datos[nClientes]);
    getEmail(&datos[nClientes]);
    getContrasenia(&datos[nClientes]);
    datos[nClientes].Cartera = obtenerCartera();

    tCliente nuevoCliente = datos[nClientes];
    
    // liberamos memoria que ya no nos hace falta
    free(datos);    

    // Guardamos los datos del cliente
    guardarDatosClienteFich("../datos/Clientes.txt", nuevoCliente);

    if(op == 1)
        menuCliente(&nuevoCliente);
    else
        printf("Se ha registrado un nuevo usuario con nombre %s correctamente.\n\n", nuevoCliente.Nomb_cliente);
}

// TODO: incluir email de transportistas
int existeEmail(char *email){
    unsigned i = 0, fin = 0;    
    tCliente *clientes = crearListaClientes();
    tAdminProv *adminprovs = crearListaAdminProv();

    cargarClientes(clientes);
    cargarAdminProvs(adminprovs);

    // buscamos si coinciden dos emails para los usuarios
    while(i < numClientes() && !fin){
        if(strcmp(clientes[i].email, email) == 0)
            fin = 1;    // se han encontrado dos emails iguales
        
        ++i;
    }

    i = 0; // ahora para los clientes
    
    while(i < numAdminProvs() && !fin){
        if(strcmp(adminprovs[i].email, email) == 0)
            fin = 1;
        
        ++i;
    }

    free(clientes);
    free(adminprovs);
    return fin;
}


void generarID(char *id, int idNum, int numDigitos){
    if(idNum >= 0 && numDigitos > 0)
        sprintf(id, "%0*d", numDigitos, idNum);   // Transformamos idNum en ID con el numero de dígitos almacenados en numDigitos
    else
        fprintf(stderr, "La ID no puede ser negativa.");
}

/* FUNCIONES PRIVADAS */