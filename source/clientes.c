#include <stdio.h>      
#include <stdlib.h>    // exit
#include <string.h>    // sscanf

#include "clientes.h"
#include "usuarios.h"    // existeEmail(), generar
#include "productos.h"  // consulta_productos()
#include "pedidos.h"
#include "categorias.h"

/* FUNCIONES PUBLICAS */

void menuCliente(tCliente *cliente){
    system("cls");

    int op, fin = 0;

    do {
        printf("Menu: Tipo Cliente.\n\n");
        printf("\t\tUsuario: %s\n\n", cliente->Nomb_cliente);
        printf("1. Perfil.\n");
        printf("2. Productos.\n");
        printf("3. Descuentos.\n");
        printf("4. Pedidos.\n");
        printf("5. Devoluciones.\n");
        printf("6. Salir del sistema.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 6){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            // Menu Clientes
            switch(op){
                case 1: perfilCliente(cliente); break;
                case 2: consultaProductosCli(); break;
                case 3: break;
                case 4: consultaPedidosCli(cliente); break;
                case 5: break;
                case 6: fin = 1; break;
                default: fprintf(stderr, "Se ha producido un error\n"); exit(1);
            }
        }

    } while(op < 1 || op > 6 || !fin);
}

void perfilCliente(tCliente *cliente){
    system("cls");

    int op;
    tCliente original = *cliente;

    do {
        printf("Perfil.\n\n");
        printf("\t1. Usuario: %s\n", cliente->Nomb_cliente);
        printf("\t2. Direccion: %s\n", cliente->Dir_cliente);
        printf("\t3. Poblacion: %s\n", cliente->Poblacion);
        printf("\t4. Provincia: %s\n", cliente->Provincia);
        printf("\t5. Email: %s\n", cliente->email);
        printf("\t6. Contrasena: %s\n", cliente->Contrasenia);
        printf("\t7. Saldo en la cartera: %.2lf euros\n", cliente->Cartera);
        printf("\t8. Volver.\n\n");

        printf("Pulse opcion si desea modificar algun dato: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 8){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            switch(op){
                case 1: getNombre(cliente); break;
                case 2: getDireccion(cliente); break;
                case 3: getPoblacion(cliente); break;
                case 4: getProvincia(cliente); break;
                case 5: getEmail(cliente); break;
                case 6: getContrasenia(cliente); break;
                case 7: cliente->Cartera = obtenerCartera(); break;
                case 8: break;
                default: fprintf(stderr, "Se ha producido un inesperado.\n"); exit(1);
            }

            system("cls"); 
        }

    } while(op < 1 || op > 8);

    // si se ha producido algun cambio, es necesario modificar Clientes.txt
    if(existeCambiosClientes(*cliente, original))
        modificarFicheroClientes(*cliente);
}

void cargarClientes(tCliente *infocli){
    unsigned i;
    char buffer[MAX_LIN_FICH_CLI];

    if(numClientes() != 0){    // Comprobamos si existe algún usuario en Clientes.txt
        FILE *pf;

        pf = fopen("../datos/Clientes.txt", "r");    // Abrimos el fichero en tipo lectura.

        if(pf == NULL){     // Comprobamos si su apertura es correcta.
            fprintf(pf, "Error en la apertura de archivos.\n");
            exit(1);
        }

        for(i = 0; i < numClientes(); ++i){   // Recorremos el vector
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH es el máximo que ocupara cada línea de Usuarios.txt
            // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
            if(fgets(buffer, MAX_LIN_FICH_CLI, pf) != NULL){
                buffer[strcspn(buffer, "\n")] = '\0';
                sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%lf", infocli[i].Id_cliente, infocli[i].Nomb_cliente, 
                                                                     infocli[i].Dir_cliente, infocli[i].Poblacion, 
                                                                     infocli[i].Provincia, infocli[i].email, 
                                                                     infocli[i].Contrasenia, &infocli[i].Cartera);
            }
        }

        fclose(pf); // Cerramos fichero.
    }
}

tCliente *crearListaClientes(){
    tCliente *clientes;

    // Reservamos la memoria necesaria gracias a la función numClientes()
    if(numClientes() == 0)
        clientes = (tCliente *) calloc(numClientes()+1, sizeof(tCliente)); 
    else
        clientes = (tCliente *) calloc(numClientes(), sizeof(tCliente));

    if(clientes == NULL){   // Comprobamos si surge algún error en la asignación
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }

    return clientes;    // Devolvemos dicho vector.
}

int inicioValidoClientes(tCliente *infocli, char *email, char *psw){
    int fin = 0;
    unsigned i = 0;
    
    while(i < numClientes() && !fin){
        if(strcmp(infocli[i].email, email) == 0 && strcmp(infocli[i].Contrasenia, psw) == 0)
            fin = 1;

        ++i;
    }

    if(fin == 1)
        fin = i;    // devolvemos en que posicion se ha encontrado del vector infocli

    return fin;
}

void guardarNuevoCliente(char *destino, tCliente datos){
    FILE *pf;

    pf = fopen(destino, "a");   // append

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }
    
    fprintf(pf, "\n%s-%s-%s-%s-%s-%s-%s-%lf", datos.Id_cliente, datos.Nomb_cliente, datos.Dir_cliente,
                                           datos.Poblacion, datos.Provincia, datos.email, 
                                           datos.Contrasenia, datos.Cartera);

    fclose(pf);
}

void reservarNuevoCliente(tCliente *infocli){
    if(numClientes() == 0)
        infocli = (tCliente *) calloc(numClientes()+1, sizeof(tCliente));
    else
        infocli = (tCliente *) realloc(infocli, (numClientes()+1)*sizeof(tCliente));
    
    if(infocli == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }
}

unsigned numClientes(){
    // Sabemos que el fichero Clientes.txt tendrá tantas lineas como clientes en el sistema ESIZON
    char buffer[MAX_LIN_FICH_CLI];
    FILE *pf;
    unsigned i = 0;

    pf = fopen("../datos/Clientes.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(pf)){
        fgets(buffer, MAX_LIN_FICH_CLI, pf);
        ++i;
    }

    fclose(pf);

    return i;
}

void getNombre(tCliente *cliente){
    char *nomCliente = NULL;

    while(!nomCliente)
        nomCliente = obtenerNombreCliente();

    strncpy(cliente->Nomb_cliente, nomCliente, NOM);
    free(nomCliente);
}

void getDireccion(tCliente *cliente){
    char *direccion = NULL;

    while(!direccion)
        direccion = obtenerDireccion();

    strncpy(cliente->Dir_cliente, direccion, DIR);
    free(direccion);
}

void getPoblacion(tCliente *cliente){
    char *poblacion = NULL;

    while(!poblacion)
        poblacion = obtenerPoblacion();

    strncpy(cliente->Poblacion, poblacion, POB);
    free(poblacion);
}

void getProvincia(tCliente *cliente){
    char *provincia = NULL;

    while(!provincia)
        provincia = obtenerProvincia();

    strncpy(cliente->Provincia, provincia, POB);
    free(provincia);
}

void getEmail(tCliente *cliente){
    char *email = NULL;

    while(!email)
        email = obtenerEmail();

    char copia[EMAIL];

    strncpy(cliente->email, email, EMAIL);
    strncpy(copia, email, EMAIL);     // para poder liberar la memoria y llamar de nuevo a la funcion sin problemas
    free(email);

    // Comprobamos si el Email introducido ya existe
    if(existeEmail(copia)){
        fprintf(stderr, "El email ya esta registrado en ESIZON.\n");
        getEmail(cliente);
    }    
}

void getContrasenia(tCliente *cliente){
    char *psw = NULL;

    while(!psw)
        psw = obtenerContrasenia();

    strncpy(cliente->Contrasenia, psw, PASS);
    free(psw); 
}

double obtenerCartera(){
    double saldoIni = 0;
    
    printf("\nIndique su saldo (formato 0.00euros): ");
    
    while(scanf("%lf", &saldoIni) != 1 || saldoIni < 0) {
        fflush(stdin);
        fprintf(stderr, "Entrada no esperada. Intente de nuevo.\n");
        printf("Indique su saldo: ");
    }
    
    return saldoIni;
}

void administracionClientes(){
    system("cls");

    int op;

    imprimirClientes(); // listado de clientes

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
                case 1: registrarse(SIN_MENU); break;
                case 2: bajaCliente(); break;
                case 3: buscadorCliente(); break;
                case 4: modificarClientes(); break;
                case 5: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 5);
}

void imprimirClientes(){
    FILE *pf;

    pf = fopen("../datos/Clientes.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    char buffer[MAX_LIN_FICH_CLI];  

    printf("\tListado de Clientes:\n\n");

    // leemos linea a linea el fichero Clientes.txt
    while(fgets(buffer, MAX_LIN_FICH_CLI, pf) != NULL)
        printf("%s", buffer);

    fclose(pf);  
}

/* FUNCIONES PRIVADAS */

static void bajaCliente(){
    system("cls");
    
    int idNum;
    tCliente *clientes = crearListaClientes();
    cargarClientes(clientes);

    do {
        imprimirClientes();

        printf("\n\nIndique la ID del cliente a eliminar (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de usuarios en el sistema entonces no existe
            if(idNum > numClientes())
                printf("No existe usuario con ID: %i.", idNum);
            else{
                --idNum;

                // eliminar cliente de idNum y reemplazar posiciones
                for(; idNum < numClientes()-1; ++idNum){
                    clientes[idNum] = clientes[idNum+1];    // reemplazamos
                    generarID(clientes[idNum].Id_cliente, idNum+1, ID-1); // regeneramos la ID
                }

                recrearFichero(clientes, numClientes()-1);  // modificamos fichero
            }
        }

        do {
            printf("\nDesea buscar otro usuario? (1 = si, 0 = no): ");

            if(scanf("%i", &idNum) != 1){
                system("cls");
                fflush(stdin);
                fprintf(stderr, "Entrada no valida.\n\n");
            }
        } while(idNum != 1 && idNum != 0);

    } while(idNum != 0);

    free(clientes);
}

static void recrearFichero(tCliente *clientes, int numClientes){
    FILE *pf, *temp;
    char *fich = "../datos/Clientes.txt";
    char *fichTemp = "../datos/Temp-Clientes.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    int i;

    for(i = 0; i < numClientes; ++i){
        if(i+1 == numClientes)
            fprintf(temp, "%s-%s-%s-%s-%s-%s-%s-%lf", clientes[i].Id_cliente, clientes[i].Nomb_cliente, clientes[i].Dir_cliente,
                                                      clientes[i].Poblacion, clientes[i].Provincia, clientes[i].email,
                                                      clientes[i].Contrasenia, clientes[i].Cartera);
        else
            fprintf(temp, "%s-%s-%s-%s-%s-%s-%s-%lf\n", clientes[i].Id_cliente, clientes[i].Nomb_cliente, clientes[i].Dir_cliente,
                                                        clientes[i].Poblacion, clientes[i].Provincia, clientes[i].email,
                                                        clientes[i].Contrasenia, clientes[i].Cartera);
    }
                
    // cerramos ficheros
    fclose(pf);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar pf
    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
}

static void modificarClientes(){
    system("cls");
    
    int idNum;
    tCliente original;
    tCliente *clientes = crearListaClientes();
    cargarClientes(clientes);

    do {
        imprimirClientes();

        printf("\n\nIndique la ID (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de usuarios en el sistema entonces no existe
            if(idNum > numClientes())
                printf("No existe usuario con ID: %i.", idNum);
            else{
                --idNum;

                original = clientes[idNum];

                printf("\nDatos del usuario buscado: ");
                printf("%s-%s-%s-%s-%s-%s-%s-%lf\n", clientes[idNum].Id_cliente, clientes[idNum].Nomb_cliente,
                                                   clientes[idNum].Dir_cliente, clientes[idNum].Poblacion,
                                                   clientes[idNum].Provincia, clientes[idNum].email,
                                                   clientes[idNum].Contrasenia, clientes[idNum].Cartera);

                unsigned op;

                do {
                    printf("\nOpciones de modificacion (CLIENTES):\n\n");
                    printf("1. Modificar nombre.\n");
                    printf("2. Modificar direccion.\n");
                    printf("3. Modificar poblacion.\n");
                    printf("4. Modificar provincia.\n");
                    printf("5. Modificar email.\n");
                    printf("6. Modificar contrasena.\n");
                    printf("7. Modificar cartera.\n");
                    printf("8. Volver.\n\n");

                    printf("Inserte la opcion: ");

                    if(scanf("%u", &op) != 1 || op < 1 || op > 8){
                        system("cls");
                        fflush(stdin);
                        fprintf(stderr, "Entrada no valida\n\n");
                    } else{
                        switch(op){
                            case 1: getNombre(&clientes[idNum]); break;
                            case 2: getDireccion(&clientes[idNum]); break;
                            case 3: getPoblacion(&clientes[idNum]); break;
                            case 4: getProvincia(&clientes[idNum]); break;
                            case 5: getEmail(&clientes[idNum]); break;
                            case 6: getContrasenia(&clientes[idNum]); break;
                            case 7: clientes[idNum].Cartera = obtenerCartera(); break;
                            case 8: break;
                            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
                        }

                        system("cls");
                    }

                } while(op < 1 || op > 8);       
            }

            // si se ha producido algun cambio, es necesario modificar Clientes.txt
            if(existeCambiosClientes(clientes[idNum], original) && idNum <= numClientes()){
                modificarFicheroClientes(clientes[idNum]);
                printf("Cliente modificado.\n");
            }
        }

        printf("\nDesea buscar otro usuario? (1 = si, 0 = no): ");

        if(scanf("%i", &idNum) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        }

    } while(idNum != 0);

    free(clientes);
}

static void buscadorCliente(){
    system("cls");

    int op;

    do {
        printf("\nOpciones de busqueda (CLIENTES):\n\n");
        printf("1. Buscar por ID.\n");
        printf("2. Buscar por nombre.\n");
        printf("3. Buscar por correo.\n");
        printf("4. Buscar por provincia.\n");
        printf("5. Buscar por poblacion.\n");
        printf("6. Volver.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 6){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida\n\n");
        } else{
            switch(op){
                case 1: buscarIDclientes(); break;
                case 2: buscarConTextoClientes(NOMBRE); break;
                case 3: buscarConTextoClientes(CORREO); break;
                case 4: buscarConTextoClientes(PROVINCIA); break;
                case 5: buscarConTextoClientes(POBLACION); break;
                case 6: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 6);
}

static void buscarIDclientes(){
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
            if(idNum > numClientes())
                printf("No existe usuario con ID: %i.", idNum);
            else{
                tCliente *clientes = crearListaClientes();
                cargarClientes(clientes);

                --idNum;

                printf("\nDatos del usuario buscado: ");
                printf("%s-%s-%s-%s-%s-%s-%s-%lf\n", clientes[idNum].Id_cliente, clientes[idNum].Nomb_cliente,
                                                   clientes[idNum].Dir_cliente, clientes[idNum].Poblacion,
                                                   clientes[idNum].Provincia, clientes[idNum].email,
                                                   clientes[idNum].Contrasenia, clientes[idNum].Cartera);

                free(clientes);
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

static void desgloseCompletoClientes(tCliente cliente){
    printf("Coincidencia: %s-%s-%s-%s-%s-%s-%s-%lf\n", cliente.Id_cliente, cliente.Nomb_cliente, cliente.Dir_cliente,
                                                            cliente.Poblacion, cliente.Provincia, cliente.email,
                                                            cliente.Contrasenia, cliente.Cartera);
}

static void buscarEnClientes(BusquedaClientes tipo, const char *str, unsigned tamStr){
    unsigned i = 0, cont = 0;
    tCliente *clientes = crearListaClientes();
    cargarClientes(clientes);

    while(i < numClientes()){
        switch(tipo){
            case NOMBRE: 
                if(strncmp(str, clientes[i].Nomb_cliente, tamStr) == 0){
                    desgloseCompletoClientes(clientes[i]);
                    ++cont;
                }
                break;
            case CORREO: 
                if(strncmp(str, clientes[i].email, tamStr) == 0) 
                    desgloseCompletoClientes(clientes[i]);
                    // no hacemos ++cont ya que no se van a repetir dos emails
                break;
            case PROVINCIA: 
                if(strncmp(str, clientes[i].Provincia, tamStr) == 0){
                    desgloseCompletoClientes(clientes[i]);
                    ++cont;
                }
                break;
            case POBLACION: 
                if(strncmp(str, clientes[i].Poblacion, tamStr) == 0){
                    desgloseCompletoClientes(clientes[i]);
                    ++cont;
                }
                break;
            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
        }
            
        ++i;
    }

    if(tipo != CORREO)  // dos emails no se repiten
        printf("Resultados encontrados: %u.\n", cont);
    
    free(clientes);
    system("pause");
}

static void buscarConTextoClientes(BusquedaClientes tipo){
    system("cls");

    // Por temas de legibilidad en el programa, se indica que tipo de busqueda se hará
    // se hace esto también para no tener que repetir el codigo en todos los casos que hay
    // de búsqueda.
    switch(tipo){
        case NOMBRE: 
            printf("Tipo de Buscador: por nombre.\n\n"); 
            printf("Inserte el nombre a buscar.\n"); 
            char *nombre = NULL;

            while(!nombre)
                nombre = obtenerNombreCliente();

            buscarEnClientes(tipo, nombre, NOM);

            free(nombre);
            break;

        case CORREO: 
            printf("Tipo de Buscador: por email.\n\n"); 
            printf("Inserte el email a buscar.\n"); 
            char *email = NULL;

            while(!email)
                email = obtenerEmail();

            buscarEnClientes(tipo, email, EMAIL);

            free(email);            
            break;
        case PROVINCIA: 
            printf("Tipo de Buscador: por provincia.\n\n"); 
            printf("Inserte la provincia a buscar.\n"); 
            char *provincia = NULL;

            while(!provincia)
                provincia = obtenerProvincia();

            buscarEnClientes(tipo, provincia, POB);

            free(provincia);
            break;
        case POBLACION: 
            printf("Tipo de Buscador: por poblacion.\n\n"); 
            printf("Inserte el poblacion a buscar.\n"); 
            char *poblacion = NULL;

            while(!poblacion)
                poblacion = obtenerNombreCliente();

            buscarEnClientes(tipo, poblacion, POB);

            free(poblacion);
            break;
        default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
    }
}

void modificarFicheroClientes(tCliente clienteMod){
    FILE *pf, *temp;
    char buffer[MAX_LIN_FICH_CLI];
    char *fich = "../datos/Clientes.txt";
    char *fichTemp = "../datos/Temp-Clientes.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    // Buscar la ID en el fichero y cambiar la linea por los datos de clienteMod
    while(fgets(buffer, MAX_LIN_FICH_CLI, pf) != NULL){
        char idFich[ID];
        
        strncpy(idFich, buffer, ID-1);    // En id se almacena los 7 primeros caracteres de cada linea

        // En temp se guardara el fichero modificado
        if(strncmp(idFich, clienteMod.Id_cliente, ID-1) == 0){
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numClientes
            if(numClientes() == atoi(idFich))
                fprintf(temp, "%s-%s-%s-%s-%s-%s-%s-%lf", clienteMod.Id_cliente, clienteMod.Nomb_cliente, clienteMod.Dir_cliente,
                                                            clienteMod.Poblacion, clienteMod.Provincia, clienteMod.email,
                                                            clienteMod.Contrasenia, clienteMod.Cartera);
        
            else
                fprintf(temp, "%s-%s-%s-%s-%s-%s-%s-%lf\n", clienteMod.Id_cliente, clienteMod.Nomb_cliente, clienteMod.Dir_cliente,
                                                            clienteMod.Poblacion, clienteMod.Provincia, clienteMod.email,
                                                            clienteMod.Contrasenia, clienteMod.Cartera);
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

static int existeCambiosClientes(tCliente nuevo, tCliente original){
    int boole = 1;

    if(nuevo.Nomb_cliente == original.Nomb_cliente && nuevo.Dir_cliente == original.Dir_cliente
        && nuevo.Poblacion == original.Poblacion && nuevo.Provincia == original.Provincia && nuevo.email == original.email
        && nuevo.Contrasenia == original.Contrasenia && nuevo.Cartera == original.Cartera)
        boole = 0;
    
    return boole;
}

static char *obtenerNombreCliente(){
    int i = 0;
    char c, *nomCliente;

    nomCliente = (char *) calloc(NOM, sizeof(char));

    if(nomCliente == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba el nombre completo (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < NOM){    // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomCliente[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomCliente) > NOM-1){
        fprintf(stderr, "El nombre completo excede los 20 caracteres.");
        free(nomCliente);
        return NULL;
    } 
    
    if(strlen(nomCliente) == 0){
        fprintf(stderr, "El nombre completo no puede estar vacio.");
        free(nomCliente);
        return NULL;
    }

    return nomCliente;
}

static char *obtenerDireccion(){
    int i = 0;
    char c, *nomDireccion;

    nomDireccion = (char *) calloc(DIR, sizeof(char));

    if(nomDireccion == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de su direccion (maximo 50 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < DIR){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomDireccion[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomDireccion) > DIR-1){
        fprintf(stderr, "El nombre de la direccion excede los 50 caracteres.");
        free(nomDireccion);
        return NULL;
    }

    if(strlen(nomDireccion) == 0){
        fprintf(stderr, "El nombre de la direccion no puede estar vacio.");
        free(nomDireccion);
        return NULL;
    }

    return nomDireccion;
}

static char *obtenerPoblacion(){
    int i = 0;
    char c, *nomPoblacion;

    nomPoblacion = (char *) calloc(POB, sizeof(char));

    if(nomPoblacion == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de poblacion (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < POB){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomPoblacion[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomPoblacion) > POB-1){
        fprintf(stderr, "El nombre de la poblacion excede los 20 caracteres.");
        free(nomPoblacion);
        return NULL;
    }

    if(strlen(nomPoblacion) == 0){
        fprintf(stderr, "El nombre de la poblacion no puede estar vacio.");
        free(nomPoblacion);
        return NULL;
    }

    return nomPoblacion;
}

static char *obtenerProvincia(){
    int i = 0;
    char c, *nomProvincia;

    nomProvincia = (char *) calloc(POB, sizeof(char));

    if(nomProvincia == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de provincia (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < POB){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomProvincia[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomProvincia) > POB-1){
        fprintf(stderr, "El nombre de la provincia excede los 20 caracteres.");
        free(nomProvincia);
        return NULL;
    }

    if(strlen(nomProvincia) == 0){
        fprintf(stderr, "El nombre de la provincia no puede estar vacio.");
        free(nomProvincia);
        return NULL;
    }

    return nomProvincia;
}

static char *obtenerEmail(){
    int i = 0;
    char c, *nomEmail;

    nomEmail = (char *) calloc(EMAIL, sizeof(char));

    if(nomEmail == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba el email (maximo 30 caracteres): ");
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
