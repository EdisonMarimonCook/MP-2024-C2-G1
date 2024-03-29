#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usuarios.h"
#include "clientes.h"   // tCliente
#include "adminprov.h"  // tAdminProv
#include "transportista.h"  // tTransportista

void inicio(){
    system("cls");

	int op;

	do {
		printf("\t\tESIZON");

		printf("\n\n\t1. Iniciar Sesion.\n");
		printf("\t2. Registrarse.\n");
		printf("\t0. Salir.\n\n");
		printf("Indique la opcion: ");
		
		if(scanf("%i", &op) != 1 || (op < 0 || op > 2)){      // Con esta condición podemos evitar que el usuario haga una entrada errónea.    
            system("cls");
			fflush(stdin);
            fprintf(stderr, "Entrada no valida. Opcion Incorrecta.\n\n");
        } else {
			switch(op){
				case 0: break;
				case 1: iniciarSesion(); break;
				case 2: registrarse(CON_MENU); break;	// solo puede registrarse como cliente
				default: fprintf(stderr, "Se ha producido un error.\n"); exit(1);
			}
		}

	} while(op < 0 || op > 2);

	system("pause");
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
    guardarNuevoCliente("../datos/Clientes.txt", nuevoCliente);

    if(op == 1)
        menuCliente(&nuevoCliente);
    else
        printf("Se ha registrado un nuevo usuario con nombre %s correctamente.\n\n", nuevoCliente.Nomb_cliente);
}

void generarID(char *id, int idNum, int numDigitos){
    if(idNum >= 0 && numDigitos > 0)
        sprintf(id, "%0*d", numDigitos, idNum);   // Transformamos idNum en ID con el numero de dígitos almacenados en numDigitos
    else
        fprintf(stderr, "La ID no puede ser negativa.");
}

void registrarTransportista(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    tTransportista *transportistas = crearListaTransportistas(); 
    cargarTransportistas(transportistas);
    unsigned nTransp = numTransportistas();

    if(nTransp != 0){
        transportistas = (tTransportista *) realloc(transportistas, (nTransp+1)*sizeof(tTransportista));

        if(transportistas == NULL){
            fprintf(stderr, "Error en la asignacion de memoria.\n");
            exit(1);
        }
    }

    // Obtenemos los datos del transportista
    generarID(transportistas[nTransp].Id_transp, nTransp+1, ID_TR-1);
    getNombreTransportista(&transportistas[nTransp]);
    getEmailTransportista(&transportistas[nTransp]);
    getContraseniaTransportista(&transportistas[nTransp]);
    getNombreEmpresa(&transportistas[nTransp]);
    getCiudad(&transportistas[nTransp]);    

    tTransportista nuevoTransportista = transportistas[nTransp];

    // liberamos memoria que ya no nos hace falta
    free(transportistas);    

    guardarNuevoTransportista("../datos/Transportistas.txt", nuevoTransportista);
}

void registrarProveedor(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    tAdminProv *datos = crearListaAdminProv(); 
    cargarAdminProvs(datos);
    unsigned nAdminProvs = numAdminProvs();

    if(nAdminProvs != 0)
        reservarAdminProv(datos);    // crearListaAdminProv si nAdminProvs es cero reserva 1 posicion

    // Obtenemos los datos del proveedor
    generarID(datos[nAdminProvs].Id_empresa, nAdminProvs+1, ID_EMPRESA-1);
    getNombreProvedor(&datos[nAdminProvs]);
    getEmailAdminProv(&datos[nAdminProvs]);
    getContraseniaAdminProv(&datos[nAdminProvs]);
    strcpy(datos[nAdminProvs].Perfil_usuario, "proveedor");

    tAdminProv nuevoProveedor = datos[nAdminProvs];
    
    // liberamos memoria que ya no nos hace falta
    free(datos);    

    guardarNuevoAdminProv("../datos/AdminProv.txt", nuevoProveedor);
}

int existeEmail(char *email){
    unsigned i = 0, fin = 0;    
    tCliente *clientes = crearListaClientes();
    tAdminProv *adminprovs = crearListaAdminProv();
    tTransportista *transp = crearListaTransportistas();

    cargarClientes(clientes);
    cargarAdminProvs(adminprovs);
    cargarTransportistas(transp);

    // buscamos si coinciden dos emails para los usuarios
    while(i < numClientes() && !fin){
        if(strcmp(clientes[i].email, email) == 0)
            fin = 1;    // se han encontrado dos emails iguales
        
        ++i;
    }

    i = 0; // ahora para los administradores y proveedores
    
    while(i < numAdminProvs() && !fin){
        if(strcmp(adminprovs[i].email, email) == 0)
            fin = 1;
        
        ++i;
    }

    i = 0;  // ahora para los transportistas

    while(i < numTransportistas() && !fin){
        if(strcmp(transp[i].email, email) == 0)
            fin = 1;

        ++i;
    }

    free(clientes);
    free(adminprovs);
    free(transp);
    return fin;
}


/* FUNCIONES PRIVADAS */

static void iniciarSesion(){
    system("cls");
    printf("\t\t\tESIZON\n\n");

    int validoCliente, validoAdminProv, validoTransp, op = 0; 
    tCliente *infoClientes;
    tAdminProv *infoAdminProvs;
    tTransportista *infoTransp;
    char email[EMAIL], psw[PASS];

    infoClientes = crearListaClientes();
    cargarClientes(infoClientes);
    infoAdminProvs = crearListaAdminProv();
    cargarAdminProvs(infoAdminProvs);
    infoTransp = crearListaTransportistas();
    cargarTransportistas(infoTransp);

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
        validoCliente = inicioValidoClientes(infoClientes, email, psw);
        validoAdminProv = inicioValidoAdminProv(infoAdminProvs, email, psw);
        validoTransp = inicioValidoTransportistas(infoTransp, email, psw);

        if(validoCliente == 0 && validoAdminProv == 0 && validoTransp == 0){
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

    } while(validoCliente == 0 && validoAdminProv == 0 && validoTransp == 0 && op != 1);

    // las funciones de inicio valido tanto para clientes como para adminProv devolvían la posición en el array
    int posC = validoCliente-1;
    int posAP = validoAdminProv-1; 
    int posT = validoTransp-1;

    tCliente cliente = infoClientes[posC];
    tAdminProv adminprov = infoAdminProvs[posAP];
    tTransportista transportista = infoTransp[posT];

    free(infoClientes);
    free(infoAdminProvs);
    free(infoTransp);

    if(op == 1)
        registrarse(CON_MENU);    // usuario es preguntado por registrarse (opcion 1)
    else if(validoCliente == 0 || validoAdminProv == 0 || validoTransp == 0){
        if(validoCliente)
            menuCliente(&cliente);      // menu principal de usuario cliente
        else if(validoAdminProv){
            if(strcmp("administrador", adminprov.Perfil_usuario) == 0)
                menuAdmin(&adminprov);      // menu principal de usuario admin
            else
                menuProveedor(&adminprov);   // menu principal de usuario proveedor
        } else  // el que queda no puede ser otro que no sea transportista
            menuTransportista(&transportista);  // menu principal de usuario transportista
    }
}
