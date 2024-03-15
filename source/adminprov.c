#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adminprov.h"
#include "usuarios.h"   // existeEmail()

/* FUNCIONES PUBLICAS */

// TODO: TERMINAR perfilAdmin y perfilProveedor 

void menuAdmin(tAdminProv *admin){
    system("cls");

    int op, fin = 0;

    do {
        printf("Menu:\n\n");
        printf("\t\tAdministrador\n\n");
        printf("1. Perfil.\n");
        printf("2. Clientes.\n");
        printf("3. Proveedores.\n");
        printf("4. Productos.\n");
        printf("5. Categorias.\n");
        printf("6. Pedidos.\n");
        printf("7. Transportista.\n");
        printf("8. Descuentos.\n");
        printf("9. Devoluciones.\n");
        printf("10. Salir del sistema.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 10){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            // Menu Admins
            switch(op){
                case 1: perfilAdmin(admin); break;
                case 2: break;
                case 3: break;
                case 4: break;
                case 5: break;
                case 6: break;
                case 7: break;
                case 8: break;
                case 9: break;
                case 10: fin = 1; break;
                default: fprintf(stderr, "Se ha producido un error\n"); exit(1);
            }
        }

    } while(op < 1 || op > 10 || !fin);
}

void menuProveedor(tAdminProv *proveedor){
    system("cls");
    
    int op, fin = 0;
    
    do {
        printf("Menu:\n\n");
        printf("\t\tEmpresa: %s\n\n", proveedor->Nombre);
        printf("1. Perfil.\n");
        printf("2. Productos.\n");
        printf("3. Pedidos.\n");
        printf("4. Salir del sistema.\n\n");
    
        printf("Inserte la opcion: ");
    
        if(scanf("%i", &op) != 1 || op < 1 || op > 4){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            // Menu Proveedor
            switch(op){
                case 1: //perfilProveedor(proveedor); break;
                case 2: break;
                case 3: break;
                case 4: fin = 1; break;
                default: fprintf(stderr, "Se ha producido un error\n"); exit(1);
            }
        }
    
    } while(op < 1 || op > 4 || !fin);
}

tAdminProv *crearListaAdminProv(){
    tAdminProv *adminProvs;

    if(numAdminProvs() == 0)
        adminProvs = (tAdminProv *) calloc(numAdminProvs()+1, sizeof(tAdminProv));
    else
        adminProvs = (tAdminProv *) calloc(numAdminProvs(), sizeof(tAdminProv));

    if(adminProvs == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }

    return adminProvs;
}

void cargarAdminProvs(tAdminProv *infoAdminProv){
    unsigned i;
    char buffer[MAX_LIN_FICH_ADMINPROV];

    if(numAdminProvs() != 0){    // Comprobamos si existe algún usuario en Clientes.txt
        FILE *pf;

        pf = fopen("../datos/AdminProv.txt", "r");    // Abrimos el fichero en tipo lectura.

        if(pf == NULL){     // Comprobamos si su apertura es correcta.
            fprintf(pf, "Error en la apertura de archivos.\n");
            exit(1);
        }

        for(i = 0; i < numAdminProvs(); ++i){   // Recorremos el vector
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH es el máximo que ocupara cada línea de Usuarios.txt
            // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
            if(fgets(buffer, MAX_LIN_FICH_ADMINPROV, pf) != NULL){
                buffer[strcspn(buffer, "\n")] = '\0';
                sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]", infoAdminProv[i].Id_empresa, infoAdminProv[i].Nombre, 
                                                                infoAdminProv[i].email, infoAdminProv[i].Contrasenia, 
                                                                infoAdminProv[i].Perfil_usuario);
            }
        }

        fclose(pf); // Cerramos fichero.
    }
}

int inicioValidoAdminProv(tAdminProv *infoAdminProv, char *email, char *psw){
    int fin = 0;
    unsigned i = 0;

    while(i < numAdminProvs() && !fin){
        if(strcmp(infoAdminProv[i].email, email) == 0 && strcmp(infoAdminProv[i].Contrasenia, psw) == 0)
            fin = 1;

        ++i;
    }

    if(fin == 1)
        fin = i;    // devolvemos en que posicion se ha encontrado del vector infocli

    return fin;
}

void perfilAdmin(tAdminProv *admin){
    system("cls");

    int op;
    tAdminProv *datos;
    tAdminProv original = *admin;

    datos = crearListaAdminProv();
    cargarAdminProvs(datos);

    // TODO: admin puede cambiarse su perfil a otro que no sea admin?
    do {
        printf("Perfil.\n\n");
        printf("\t1. Email: %s\n", admin->email);
        printf("\t2. Contrasena: %s\n", admin->Contrasenia);
        printf("\t3. Volver.\n\n");

        printf("Pulse opcion si desea modificar algun dato: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 4){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida\n\n");
        } else{
            switch(op){
                case 1: getEmailAdminProv(admin); break;
                case 2: getContraseniaAdminProv(admin); break;
                case 3: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 4);
}

unsigned numAdminProvs(){
    // Sabemos que el fichero Clientes.txt tendrá tantas lineas como clientes en el sistema ESIZON
    char buffer[MAX_LIN_FICH_ADMINPROV];
    FILE *pf;
    unsigned i = 0;

    pf = fopen("../datos/AdminProv.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(pf)){
        fgets(buffer, MAX_LIN_FICH_ADMINPROV, pf);
        ++i;
    }

    fclose(pf);

    return i;
}

/* FUNCIONES PRIVADAS */

static void getNombreProvedor(tAdminProv *adminprovs){
    char *nombre = NULL;

    while(!nombre)
        nombre = obtenerNombreProvedor();

    strncpy(adminprovs->Nombre, nombre, NOM);
    free(nombre);
}

static char *obtenerNombreProvedor(){
    int i = 0;
    char c, *nombre;

    nombre = (char *) calloc(NOM, sizeof(char));

    if(nombre == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba su nombre (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < NOM){    // Recogemos caracter a caracter para controlar el tamaño de entrada
        nombre[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nombre) > NOM-1){
        fprintf(stderr, "El nombre de la empresa excede los 20 caracteres.");
        free(nombre);
        return NULL;
    } 
    
    if(strlen(nombre) == 0){
        fprintf(stderr, "El nombre de la empresa no puede estar vacio.");
        free(nombre);
        return NULL;
    }

    return nombre;
}

static void getEmailAdminProv(tAdminProv *adminprovs){
    char *email = NULL;

    while(!email)
        email = obtenerEmail();

    char copia[EMAIL];

    strncpy(adminprovs->email, email, EMAIL);
    strncpy(copia, email, EMAIL);     // para poder liberar la memoria y llamar de nuevo a la funcion sin problemas
    free(email);

    // Comprobamos si el Email introducido ya existe
    if(existeEmail(copia)){
        fprintf(stderr, "El email ya esta registrado en ESIZON.\n");
        getEmailAdminProv(adminprovs);
    }    
}

static char *obtenerEmail(){
    int i = 0;
    char c, *nomEmail;

    nomEmail = (char *) calloc(EMAIL, sizeof(char));

    if(nomEmail == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba su email (maximo 30 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < EMAIL){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomEmail[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomEmail) > EMAIL-1){
        fprintf(stderr, "El email excede los 30 caracteres.");
        free(nomEmail);
        return NULL;
    }

    if(strlen(nomEmail) == 0){
        fprintf(stderr, "El email no puede estar vacio.");
        free(nomEmail);
        return NULL;
    }

    return nomEmail;
}

static void getContraseniaAdminProv(tAdminProv *adminprovs){
    char *psw = NULL;

    while(!psw)
        psw = obtenerContrasenia();

    strncpy(adminprovs->Contrasenia, psw, PASS);
    free(psw); 
}

static char *obtenerContrasenia(){
    int i = 0;
    char c, *contrasenia;

    contrasenia = (char *) calloc(PASS, sizeof(char));

    if(contrasenia == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe la contrasena (maximo 15 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < PASS){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        contrasenia[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(contrasenia) > PASS-1){
        fprintf(stderr, "La contrasena excede los 15 caracteres.");
        free(contrasenia);
        return NULL;
    }

    if(strlen(contrasenia) == 0){
        fprintf(stderr, "La contrasena no puede estar vacio.");
        free(contrasenia);
        return NULL;
    } 

    return contrasenia;
}
