#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adminprov.h"
#include "clientes.h"   // infoClientes()
#include "usuarios.h"   // existeEmail()
#include "categorias.h" // mainCategorias()
#include "descuentos.h" // menuDescuentos()

/* FUNCIONES PUBLICAS */

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
                case 2: infoClientes(); break;  // clientes.h
                case 3: infoProveedores(); break;
                case 4: break;
                case 5: mainCategorias(); break;
                case 6: break;
                case 7: break;
                case 8: menuDescuentos(); break;
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
                case 1: perfilProveedor(proveedor); break;
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

        fclose(pf); 
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
    tAdminProv original = *admin;

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

    if(existeCambiosAdminProv(*admin, original))
        modificarFicheroAdminProv(*admin);
}

void perfilProveedor(tAdminProv *proveedor){
    system("cls");

    int op;
    tAdminProv *datos;
    tAdminProv original = *proveedor;

    datos = crearListaAdminProv();
    cargarAdminProvs(datos);

    do {
        printf("Perfil.\n\n");
        printf("\t1. Nombre Empresa: %s\n", proveedor->Nombre);
        printf("\t2. Email: %s\n", proveedor->email);
        printf("\t3. Contrasena: %s\n", proveedor->Contrasenia);
        printf("\t4. Volver.\n\n");

        printf("Pulse opcion si desea modificar algun dato: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 5){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida\n\n");
        } else{
            switch(op){
                case 1: getNombreProvedor(proveedor); break;
                case 2: getEmailAdminProv(proveedor); break;
                case 3: getContraseniaAdminProv(proveedor); break;
                case 4: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 5);

    if(existeCambiosAdminProv(*proveedor, original))
        modificarFicheroAdminProv(*proveedor);
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

void guardarDatosAdminProvFich(char *destino, tAdminProv datos){
    FILE *pf;

    pf = fopen(destino, "a");   // append

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }
    
    fprintf(pf, "\n%s-%s-%s-%s-%s", datos.Id_empresa, datos.Nombre, datos.email,
                                  datos.Contrasenia, datos.Perfil_usuario);

    fclose(pf);
}

void getNombreProvedor(tAdminProv *adminprovs){
    char *nombre = NULL;

    while(!nombre)
        nombre = obtenerNombreProvedor();

    strncpy(adminprovs->Nombre, nombre, NOM);
    free(nombre);
}

void getEmailAdminProv(tAdminProv *adminprovs){
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

void getContraseniaAdminProv(tAdminProv *adminprovs){
    char *psw = NULL;

    while(!psw)
        psw = obtenerContrasenia();

    strncpy(adminprovs->Contrasenia, psw, PASS);
    free(psw); 
}

void reservarAdminProv(tAdminProv *infoAdminProv){
    if(numAdminProvs() == 0)
        infoAdminProv = (tAdminProv *) calloc(numAdminProvs()+1, sizeof(tAdminProv));
    else
        infoAdminProv = (tAdminProv *) realloc(infoAdminProv, (numAdminProvs()+1)*sizeof(tAdminProv));
    
    if(infoAdminProv == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }
}

/* FUNCIONES PRIVADAS */

static void infoProveedores(){
    system("cls");

    int op;

    imprimirProveedores(); // listado de proveedores

    do {
        printf("\n\nMenu:\n\n");
        printf("1. Dar de alta.\n");
        printf("2. Dar de baja.\n");
        printf("3. Buscar.\n");
        printf("4. Modificar.\n");
        printf("5. Volver.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 5){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida\n\n");
        } else{
            switch(op){
                case 1: registrarProveedor(); break;
                case 2: bajaProveedor(); break;
                case 3: buscadorProveedores(); break;
                case 4: modificarProveedores(); break;
                case 5: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 5);
}

static void bajaProveedor(){
    system("cls");
    
    int idNum;
    tAdminProv *adminprov = crearListaAdminProv();
    cargarAdminProvs(adminprov);

    do {
        imprimirProveedores();

        printf("\n\nIndique la ID del cliente a eliminar (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de proveedores en el sistema entonces no existe
            if(idNum > numAdminProvs() || strcmp(adminprov[idNum-1].Perfil_usuario, "proveedor"))
                printf("No existe proveedor con ID: %i.", idNum);
            else{
                --idNum;

                // eliminar cliente de idNum y reemplazar posiciones
                for(; idNum < numAdminProvs()-1; ++idNum){
                    adminprov[idNum] = adminprov[idNum+1];    // reemplazamos
                    generarID(adminprov[idNum].Id_empresa, idNum+1, ID_EMPRESA-1); // regeneramos la ID
                }

                recrearFicheroProveedores(adminprov, numAdminProvs()-1);  // modificamos fichero
            }
        }

        do {
            printf("\nDesea buscar otro proveedor? (1 = si, 0 = no): ");

            if(scanf("%i", &idNum) != 1){
                system("cls");
                fflush(stdin);
                fprintf(stderr, "Entrada no valida.\n\n");
            }
        } while(idNum != 1 && idNum != 0);

    } while(idNum != 0);

    free(adminprov);
}

static void recrearFicheroProveedores(tAdminProv *proveedores, int numProveedores){
    FILE *pf, *temp;
    char buffer[MAX_LIN_FICH_CLI];
    char *fich = "../datos/AdminProv.txt";
    char *fichTemp = "../datos/Temp-AdminProv.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    int i;

    for(i = 0; i < numProveedores; ++i){
        if(i+1 == numProveedores)
            fprintf(temp, "%s-%s-%s-%s-%s", proveedores[i].Id_empresa, proveedores[i].Nombre, 
                                            proveedores[i].email, proveedores[i].Contrasenia, 
                                            proveedores[i].Perfil_usuario);
        else
            fprintf(temp, "%s-%s-%s-%s-%s\n", proveedores[i].Id_empresa, proveedores[i].Nombre, 
                                              proveedores[i].email, proveedores[i].Contrasenia, 
                                              proveedores[i].Perfil_usuario);
    }
                
    // cerramos ficheros
    fclose(pf);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar pf
    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
}

// TODO: terminar modificarProveedores, no se pueden modificar ni buscar Admin, ya que no es un proovedor
static void modificarProveedores(){
    system("cls");
    
    int idNum;
    tAdminProv original;
    tAdminProv *proveedores = crearListaAdminProv();
    cargarAdminProvs(proveedores);

    do {
        imprimirProveedores();

        printf("\n\nIndique la ID (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de usuarios en el sistema entonces no existe
            if(idNum > numAdminProvs() || strcmp(proveedores[idNum-1].Perfil_usuario, "proveedor"))
                printf("No existe proveedor con ID: %i.", idNum);
            else{
                --idNum;

                original = proveedores[idNum];

                system("cls");

                printf("\nDatos del proveedor buscado: ");
                printf("%s-%s-%s-%s-%s\n", proveedores[idNum].Id_empresa, proveedores[idNum].Nombre, 
                                           proveedores[idNum].email, proveedores[idNum].Contrasenia, 
                                           proveedores[idNum].Perfil_usuario);

                int op;

                do {
                    printf("\nOpciones de modificacion (PROVEEDORES):\n\n");
                    printf("1. Modificar nombre.\n");
                    printf("2. Modificar email.\n");
                    printf("3. Modificar contrasena.\n");
                    printf("4. Volver.\n\n");

                    printf("Inserte la opcion: ");

                    if(scanf("%i", &op) != 1 || op < 1 || op > 4){
                        system("cls");
                        fflush(stdin);
                        fprintf(stderr, "Entrada no valida\n\n");
                    } else{
                        switch(op){
                            case 1: getNombreProvedor(&proveedores[idNum]); break;
                            case 2: getEmailAdminProv(&proveedores[idNum]); break;
                            case 3: getContraseniaAdminProv(&proveedores[idNum]); break;
                            case 4: break;
                            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
                        }

                        system("cls");
                    }

                } while(op < 1 || op > 4);       
            }

            // si se ha producido algun cambio, es necesario modificar AdminProv.txt
            if(existeCambiosAdminProv(proveedores[idNum], original) && strcmp(proveedores[idNum-1].Perfil_usuario, "proveedor") == 0){
                modificarFicheroAdminProv(proveedores[idNum]);
                printf("Proveedor modificado.\n");
            }
        }

        printf("\nDesea buscar otro proveedor? (1 = si, 0 = no): ");

        if(scanf("%i", &idNum) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        }

    } while(idNum != 0);

    free(proveedores);
}

static void buscadorProveedores(){
    system("cls");

    int op;

    do {
        printf("\nOpciones de busqueda (PROVEEDORES):\n\n");
        printf("1. Buscar por ID.\n");
        printf("2. Buscar por nombre.\n");
        printf("3. Buscar por correo.\n");
        printf("4. Volver.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 4){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida\n\n");
        } else{
            switch(op){
                case 1: buscarIDproveedor(); break;
                case 2: buscarConTextoProveedores(NOMBRE); break;
                case 3: buscarConTextoProveedores(CORREO); break;
                case 4: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 4);
}

static void buscarIDproveedor(){
    system("cls");
    printf("Tipo de Buscador: por ID.\n");

    int idNum;

    do {
        printf("Indique la ID (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de usuarios en el sistema entonces no existe
            if(idNum > numAdminProvs())
                printf("No existe usuario con ID: %i.", idNum);
            else{
                tAdminProv *proveedores = crearListaAdminProv();
                cargarAdminProvs(proveedores);

                --idNum;

                printf("\nDatos del usuario buscado: ");
                printf("%s-%s-%s-%s-%s\n", proveedores[idNum].Id_empresa, proveedores[idNum].Nombre, 
                                           proveedores[idNum].email, proveedores[idNum].Contrasenia, 
                                           proveedores[idNum].Perfil_usuario);

                free(proveedores);
            }
        }

        printf("\nDesea buscar otro usuario? (1 = si, 0 = no): ");

        if(scanf("%i", &idNum) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        }

    } while(idNum != 0);
}

static void desgloseCompletoProveedor(tAdminProv proveedor){
    printf("Coincidencia: %s-%s-%s-%s-%s\n", proveedor.Id_empresa, proveedor.Nombre, 
                                             proveedor.email, proveedor.Contrasenia,
                                             proveedor.Perfil_usuario);
}

static void buscarEnProveedores(BusquedaProveedores tipo, const char *str, unsigned tamStr){
    unsigned i = 0, cont = 0;
    tAdminProv *proveedores = crearListaAdminProv();
    cargarAdminProvs(proveedores);

    while(i < numAdminProvs()){
        switch(tipo){
            case NOMBREPV: 
                if(strncmp(str, proveedores[i].Nombre, tamStr) == 0){
                    desgloseCompletoProveedor(proveedores[i]);
                    ++cont;
                }
                break;
            case CORREOPV: 
                if(strncmp(str, proveedores[i].email, tamStr) == 0) 
                    desgloseCompletoProveedor(proveedores[i]);
                    // no hacemos ++cont ya que no se van a repetir dos emails
                break;
            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
        }
            
        ++i;
    }

    if(tipo != CORREOPV)  // dos emails no se repiten
        printf("Resultados encontrados: %u.\n", cont);
    
    free(proveedores);
    system("pause");
}

static void buscarConTextoProveedores(BusquedaProveedores tipo){
    system("cls");

    // Por temas de legibilidad en el programa, se indica que tipo de busqueda se hará
    // se hace esto también para no tener que repetir el codigo en todos los casos que hay
    // de búsqueda.
    switch(tipo){
        case NOMBREPV: 
            printf("Tipo de Buscador: por nombre.\n\n"); 
            printf("Inserte el nombre a buscar.\n"); 
            char *nombre = NULL;

            while(!nombre)
                nombre = obtenerNombreProvedor();

            buscarEnProveedores(tipo, nombre, NOM);

            free(nombre);
            break;

        case CORREOPV: 
            printf("Tipo de Buscador: por email.\n\n"); 
            printf("Inserte el email a buscar.\n"); 
            char *email = NULL;

            while(!email)
                email = obtenerEmail();

            buscarEnProveedores(tipo, email, EMAIL);

            free(email);            
            break;
        default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
    }
}

// TODO: modificaciones correctamente de proveedores

static void imprimirProveedores(){
    FILE *pf;

    pf = fopen("../datos/AdminProv.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    char buffer[MAX_LIN_FICH_ADMINPROV];

    printf("\tListado de Proveedores:\n\n");

    // Leemos linea a linea el fichero AdminProv.txt
    while(fgets(buffer, MAX_LIN_FICH_ADMINPROV, pf) != NULL){
        // Obtenemos el rol del usuario
        char perfil[PERFIL];
        sscanf(buffer, "%*[^-]-%*[^-]-%*[^-]-%*[^-]-%s", perfil);

        // Si el perfil es proveedor imprimimos la línea
        if(strcmp(perfil, "proveedor") == 0)
            printf("%s", buffer);
    }

    fclose(pf);
}

static int existeCambiosAdminProv(tAdminProv nuevo, tAdminProv original){
    int boole = 1;

    if(nuevo.Nombre == original.Nombre && nuevo.email == original.email 
        && nuevo.Contrasenia == original.Contrasenia)
        boole = 0;
    
    return boole;
}

static void modificarFicheroAdminProv(tAdminProv adminprovMod){
    FILE *pf, *temp;
    char idFich[ID_EMPRESA];
    char buffer[MAX_LIN_FICH_ADMINPROV];
    char *fich = "../datos/AdminProv.txt";
    char *fichTemp = "../datos/Temp-AdminProv.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    // Buscar la ID en el fichero y cambiar la linea por los datos de clienteMod
    while(fgets(buffer, MAX_LIN_FICH_ADMINPROV, pf) != NULL){
        strncpy(idFich, buffer, ID_EMPRESA);    // En id se almacena los 4 primeros caracteres de cada linea

        // En temp se guardara el fichero modificado
        if(strncmp(idFich, adminprovMod.Id_empresa, ID_EMPRESA-1) == 0){
            if(numAdminProvs() == atoi(idFich))
                fprintf(temp, "%s-%s-%s-%s-%s", adminprovMod.Id_empresa, adminprovMod.Nombre, adminprovMod.email,
                                                adminprovMod.Contrasenia, adminprovMod.Perfil_usuario);
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numAdminProv
            else
                fprintf(temp, "%s-%s-%s-%s-%s\n", adminprovMod.Id_empresa, adminprovMod.Nombre, adminprovMod.email,
                                                  adminprovMod.Contrasenia, adminprovMod.Perfil_usuario);
        } else
            fprintf(temp, "%s", buffer);
    }

    // cerramos ficheros
    fclose(pf);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar pf
    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
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
