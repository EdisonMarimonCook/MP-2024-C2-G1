#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transportista.h"
#include "usuarios.h"   // existeEmail()

/* FUNCIONES PUBLICAS */

void administracionTransportistas(){
    system("cls");

    int op;

    imprimirTransportistas(); // listado de transportistas

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
                case 1: registrarTransportista(); break;    // usuarios.h
                case 2: bajaTransportista(); break;
                case 3: buscadorTransportistas(); break;
                case 4: modificarTransportistas(); break;
                case 5: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 5);
}

void menuTransportista(tTransportista *transportista){
    system("cls");

    int op, fin = 0;

    do {
        printf("Menu: Tipo Transportista.\n\n");
        printf("\t\tTransportista: %s\n\n", transportista->Nombre);
        printf("1. Perfil.\n");
        printf("2. Repartos.\n");
        printf("3. Retornos.\n");
        printf("4. Salir del sistema.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 4){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            // Menu Transportista
            switch(op){
                case 1: perfilTransportista(transportista); break;
                case 2: break;
                case 3: break;
                case 4: fin = 1; break;
                default: fprintf(stderr, "Se ha producido un error\n"); exit(1);
            }
        }

    } while(op < 1 || op > 4 || !fin);
}

void perfilTransportista(tTransportista *transportista){
    system("cls");

    int op;
    tTransportista original = *transportista;

    do {
        printf("Perfil.\n\n");
        printf("\t1. Nombre de transportista: %s\n", transportista->Nombre);
        printf("\t2. Email: %s\n", transportista->email);
        printf("\t3. Contrasena: %s\n", transportista->Contrasenia);
        printf("\t4. Nombre de empresa: %s\n", transportista->Nomb_empresa);
        printf("\t5. Ciudad de reparto: %s\n", transportista->Ciudad);
        printf("\t6. Volver.\n\n");

        printf("Pulse opcion si desea modificar algun dato: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 6){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else{
            switch(op){
                case 1: getNombreTransportista(transportista); break;
                case 2: getEmailTransportista(transportista); break;
                case 3: getContraseniaTransportista(transportista); break;
                case 4: getNombreEmpresa(transportista); break;
                case 5: getCiudad(transportista); break;
                case 6: break;
                default: fprintf(stderr, "Se ha producido un inesperado.\n"); exit(1);
            }

            system("cls"); 
        }

    } while(op < 1 || op > 6);

    // si se ha producido algun cambio, es necesario modificar Transportistas.txt
    if(existeCambiosTransportistas(*transportista, original))
        modificarFicheroTransportistas(*transportista);
}

tTransportista *crearListaTransportistas(){
    tTransportista *transportista;

    // Reservamos la memoria necesaria gracias a la función numTransportistas()
    if(numTransportistas() == 0)
        transportista = (tTransportista *) calloc(numTransportistas()+1, sizeof(tTransportista)); 
    else
        transportista = (tTransportista *) calloc(numTransportistas(), sizeof(tTransportista));

    if(transportista == NULL){   // Comprobamos si surge algún error en la asignación
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }

    return transportista;    // Devolvemos dicho vector.
}

void cargarTransportistas(tTransportista *infotransp){
    unsigned i;
    char buffer[MAX_LIN_FICH_TRANS];

    if(numTransportistas() != 0){    // Comprobamos si existe algún usuario en Transportistas.txt
        FILE *pf;

        pf = fopen("../datos/Transportistas.txt", "r");    // Abrimos el fichero en tipo lectura.

        if(pf == NULL){     // Comprobamos si su apertura es correcta.
            fprintf(pf, "Error en la apertura de archivos.\n");
            exit(1);
        }

        for(i = 0; i < numTransportistas(); ++i){   // Recorremos el vector
            // Cogemos línea por línea, ya que sabemos que MAX_LIN_FICH es el máximo que ocupara cada línea de Usuarios.txt
            // Tras recoger una línea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
            if(fgets(buffer, MAX_LIN_FICH_TRANS, pf) != NULL){
                buffer[strcspn(buffer, "\n")] = '\0';
                sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]", infotransp[i].Id_transp, infotransp[i].Nombre, 
                                                                      infotransp[i].email, infotransp[i].Contrasenia, 
                                                                      infotransp[i].Nomb_empresa, infotransp[i].Ciudad);
            }
        }

        fclose(pf); // Cerramos fichero.
    }
}

unsigned numTransportistas(){
    // Sabemos que el fichero Transportistas.txt tendrá tantas lineas como transportistas en el sistema ESIZON
    char buffer[MAX_LIN_FICH_TRANS];
    FILE *pf;
    unsigned i = 0;

    pf = fopen("../datos/Transportistas.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    // Hasta que no se llegue al fin de fichero, contamos linea a linea
    while(!feof(pf)){
        fgets(buffer, MAX_LIN_FICH_TRANS, pf);
        ++i;
    }

    fclose(pf);

    return i;
}

void guardarNuevoTransportista(char *destino, tTransportista datos){
    FILE *pf;

    pf = fopen(destino, "a");   // append

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }
    
    fprintf(pf, "\n%s-%s-%s-%s-%s-%s", datos.Id_transp, datos.Nombre, datos.email,
                                       datos.Contrasenia, datos.Nomb_empresa, datos.Ciudad);

    fclose(pf);
}

int inicioValidoTransportistas(tTransportista *transp, char *email, char *psw){
    int fin = 0;
    unsigned i = 0;
    
    while(i < numTransportistas() && !fin){
        if(strcmp(transp[i].email, email) == 0 && strcmp(transp[i].Contrasenia, psw) == 0)
            fin = 1;

        ++i;
    }

    if(fin == 1)
        fin = i;    // devolvemos en que posicion se ha encontrado del vector transp

    return fin;
}

void getNombreTransportista(tTransportista *transportista){  
    char *nombre = NULL;

    while(!nombre)
        nombre = obtenerNombreTransportista();

    strncpy(transportista->Nombre, nombre, NOM);
    free(nombre);
}

void getEmailTransportista(tTransportista *transportista){
    char *email = NULL;

    while(!email)
        email = obtenerEmail();

    char copia[EMAIL];

    strncpy(transportista->email, email, EMAIL);
    strncpy(copia, email, EMAIL);     // para poder liberar la memoria y llamar de nuevo a la funcion sin problemas
    free(email);

    // Comprobamos si el Email introducido ya existe
    if(existeEmail(copia)){
        fprintf(stderr, "El email ya esta registrado en ESIZON.\n");
        getEmailTransportista(transportista);
    }    
}

void getContraseniaTransportista(tTransportista *transportista){
    char *psw = NULL;

    while(!psw)
        psw = obtenerContrasenia();

    strncpy(transportista->Contrasenia, psw, PASS);
    free(psw); 
}

void getNombreEmpresa(tTransportista *transportista){  
    char *nombre = NULL;

    while(!nombre)
        nombre = obtenerNombreEmpresa();

    strncpy(transportista->Nomb_empresa, nombre, NOM);
    free(nombre);
}

void getCiudad(tTransportista *transportista){
    char *ciudad = NULL;

    while(!ciudad)
        ciudad = obtenerCiudad();

    strncpy(transportista->Ciudad, ciudad, CIUDAD);
    free(ciudad);
}


/* FUNCIONES PRIVADAS */

static void bajaTransportista(){
    system("cls");
    
    int idNum;
    tTransportista *transportistas = crearListaTransportistas();
    cargarTransportistas(transportistas);

    do {
        imprimirTransportistas();

        printf("\n\nIndique la ID del transportista a eliminar (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de usuarios en el sistema entonces no existe
            if(idNum > numTransportistas())
                printf("No existe usuario con ID: %i.", idNum);
            else{
                --idNum;

                // eliminar cliente de idNum y reemplazar posiciones
                for(; idNum < numTransportistas()-1; ++idNum){
                    transportistas[idNum] = transportistas[idNum+1];    // reemplazamos
                    generarID(transportistas[idNum].Id_transp, idNum+1, ID_TR-1); // regeneramos la ID
                }

                recrearFicheroTransportistas(transportistas, numTransportistas()-1);  // modificamos fichero
            }
        }

        do {
            printf("\nDesea buscar otro transportista? (1 = si, 0 = no): ");

            if(scanf("%i", &idNum) != 1){
                system("cls");
                fflush(stdin);
                fprintf(stderr, "Entrada no valida.\n\n");
            }
        } while(idNum != 1 && idNum != 0);

    } while(idNum != 0);

    free(transportistas);
}

static void recrearFicheroTransportistas(tTransportista *transportistas, int numTransp){
    FILE *pf, *temp;
    char *fich = "../datos/Transportistas.txt";
    char *fichTemp = "../datos/Temp-Transportistas.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    int i;

    for(i = 0; i < numTransp; ++i){
        if(i+1 == numTransp)
            fprintf(temp, "%s-%s-%s-%s-%s-%s", transportistas[i].Id_transp, transportistas[i].Nombre, 
                                               transportistas[i].email, transportistas[i].Contrasenia, 
                                               transportistas[i].Nomb_empresa, transportistas[i].Ciudad);
        else
            fprintf(temp, "%s-%s-%s-%s-%s-%s\n", transportistas[i].Id_transp, transportistas[i].Nombre, 
                                                 transportistas[i].email, transportistas[i].Contrasenia, 
                                                 transportistas[i].Nomb_empresa, transportistas[i].Ciudad);
    }
                
    // cerramos ficheros
    fclose(pf);
    fclose(temp);

    // Tenemos que renombrar temp y eliminar pf
    remove(fich);
    rename(fichTemp, fich); // fichTemp pasa a ser fich
}

static void buscadorTransportistas(){
    system("cls");

    int op;

    do {
        printf("\nOpciones de busqueda (CLIENTES):\n\n");
        printf("1. Buscar por ID.\n");
        printf("2. Buscar por nombre.\n");
        printf("3. Buscar por correo.\n");
        printf("4. Buscar por nombre de empresa.\n");
        printf("5. Buscar por ciudad de reparto.\n");
        printf("6. Volver.\n\n");

        printf("Inserte la opcion: ");

        if(scanf("%i", &op) != 1 || op < 1 || op > 6){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida\n\n");
        } else{
            switch(op){
                case 1: buscarIDtransportistas(); break;
                case 2: buscarConTextoTransportistas(NOMBRE_TR); break;
                case 3: buscarConTextoTransportistas(CORREO_TR); break;
                case 4: buscarConTextoTransportistas(NOMBRE_EMP); break;
                case 5: buscarConTextoTransportistas(NOM_CIUDAD); break;
                case 6: break;
                default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
            }

            system("cls");
        }

    } while(op < 1 || op > 6);
}

static void buscarIDtransportistas(){
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
            if(idNum > numTransportistas())
                printf("No existe usuario con ID: %i.", idNum);
            else{
                tTransportista *transportistas = crearListaTransportistas();
                cargarTransportistas(transportistas);

                --idNum;

                printf("\nDatos del usuario buscado: ");
                printf("%s-%s-%s-%s-%s-%s\n", transportistas[idNum].Id_transp, transportistas[idNum].Nombre, 
                                              transportistas[idNum].email, transportistas[idNum].Contrasenia, 
                                              transportistas[idNum].Nomb_empresa, transportistas[idNum].Ciudad);

                free(transportistas);
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

static void buscarConTextoTransportistas(BusquedaTransp tipo){
    system("cls");

    // Por temas de legibilidad en el programa, se indica que tipo de busqueda se hará
    // se hace esto también para no tener que repetir el codigo en todos los casos que hay
    // de búsqueda.
    switch(tipo){
        case NOMBRE_TR: 
            printf("Tipo de Buscador: por nombre.\n\n"); 
            printf("Inserte el nombre a buscar.\n"); 
            char *nombre = NULL;

            while(!nombre)
                nombre = obtenerNombreTransportista();

            buscarEnTransportistas(tipo, nombre, NOM);

            free(nombre);
            break;

        case CORREO_TR: 
            printf("Tipo de Buscador: por email.\n\n"); 
            printf("Inserte el email a buscar.\n"); 
            char *email = NULL;

            while(!email)
                email = obtenerEmail();

            buscarEnTransportistas(tipo, email, EMAIL);

            free(email);            
            break;
        case NOMBRE_EMP: 
            printf("Tipo de Buscador: por nombre de empresa.\n\n"); 
            printf("Inserte el nombre de empresa a buscar.\n"); 
            char *nomEmp = NULL;

            while(!nomEmp)
                nomEmp = obtenerNombreEmpresa();

            buscarEnTransportistas(tipo, nomEmp, NOM);

            free(nomEmp);
            break;
        case NOM_CIUDAD: 
            printf("Tipo de Buscador: por ciudad.\n\n"); 
            printf("Inserte la ciudad a buscar.\n"); 
            char *ciudad = NULL;

            while(!ciudad)
                ciudad = obtenerCiudad();

            buscarEnTransportistas(tipo, ciudad, CIUDAD);

            free(ciudad);
            break;
        default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
    }
}

static void buscarEnTransportistas(BusquedaTransp tipo, const char *str, unsigned tamStr){
    unsigned i = 0, cont = 0;
    tTransportista *transportistas = crearListaTransportistas();
    cargarTransportistas(transportistas);

    while(i < numTransportistas()){
        switch(tipo){
            case NOMBRE_TR: 
                if(strncmp(str, transportistas[i].Nombre, tamStr) == 0){
                    desgloseCompletoTransportistas(transportistas[i]);
                    ++cont;
                }
                break;
            case CORREO_TR: 
                if(strncmp(str, transportistas[i].email, tamStr) == 0) 
                    desgloseCompletoTransportistas(transportistas[i]);
                    // no hacemos ++cont ya que no se van a repetir dos emails
                break;
            case NOMBRE_EMP: 
                if(strncmp(str, transportistas[i].Nomb_empresa, tamStr) == 0){
                    desgloseCompletoTransportistas(transportistas[i]);
                    ++cont;
                }
                break;
            case NOM_CIUDAD: 
                if(strncmp(str, transportistas[i].Ciudad, tamStr) == 0){
                    desgloseCompletoTransportistas(transportistas[i]);
                    ++cont;
                }
                break;
            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
        }
            
        ++i;
    }

    if(tipo != CORREO_TR)  // dos emails no se repiten
        printf("Resultados encontrados: %u.\n", cont);
    
    free(transportistas);
    system("pause");
}

static void desgloseCompletoTransportistas(tTransportista transportista){
    printf("Coincidencia: %s-%s-%s-%s-%s-%s\n", transportista.Id_transp, transportista.Nombre, 
                                                transportista.email, transportista.Contrasenia, 
                                                transportista.Nomb_empresa, transportista.Ciudad);
}

static void modificarTransportistas(){
    system("cls");
    
    int idNum;
    tTransportista original;
    tTransportista *transportistas = crearListaTransportistas();
    cargarTransportistas(transportistas);

    do {
        imprimirTransportistas();

        printf("\n\nIndique la ID (formato 1, 2, ...): ");
        
        if(scanf("%i", &idNum) != 1 || idNum <= 0){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        } else {
            // Si la ID introducida es mayor al numero de transportistas en el sistema entonces no existe
            if(idNum > numTransportistas())
                printf("No existe transportista con ID: %i.", idNum);
            else{
                --idNum;

                original = transportistas[idNum];

                printf("\nDatos del transportista buscado: ");
                printf("%s-%s-%s-%s-%s-%s\n", transportistas[idNum].Id_transp, transportistas[idNum].Nombre,
                                                   transportistas[idNum].email, transportistas[idNum].Contrasenia,
                                                   transportistas[idNum].Nomb_empresa, transportistas[idNum].Ciudad);

                unsigned op;

                do {
                    printf("\nOpciones de modificacion (TRANSPORTISTA):\n\n");
                    printf("1. Modificar nombre.\n");
                    printf("2. Modificar email.\n");
                    printf("3. Modificar contrasena.\n");
                    printf("4. Modificar nombre de empresa.\n");
                    printf("5. Modificar ciudad.\n");
                    printf("6. Volver.\n\n");

                    printf("Inserte la opcion: ");

                    if(scanf("%u", &op) != 1 || op < 1 || op > 6){
                        system("cls");
                        fflush(stdin);
                        fprintf(stderr, "Entrada no valida\n\n");
                    } else{
                        switch(op){
                            case 1: getNombreTransportista(&transportistas[idNum]); break;
                            case 2: getEmailTransportista(&transportistas[idNum]); break;
                            case 3: getContraseniaTransportista(&transportistas[idNum]); break;
                            case 4: getNombreEmpresa(&transportistas[idNum]); break;
                            case 5: getCiudad(&transportistas[idNum]); break;
                            case 6: break;
                            default: fprintf(stderr, "Se ha producido un error inesperado.\n"); exit(1);
                        }

                        system("cls");
                    }

                } while(op < 1 || op > 6);       
            }

            // si se ha producido algun cambio, es necesario modificar Transportistas.txt
            if(existeCambiosTransportistas(transportistas[idNum], original) && idNum <= numTransportistas()){
                modificarFicheroTransportistas(transportistas[idNum]);
                printf("Transportista modificado.\n");
            }
        }

        printf("\nDesea buscar otro transportista? (1 = si, 0 = no): ");

        if(scanf("%i", &idNum) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");
        }

    } while(idNum != 0);

    free(transportistas);
}


static void imprimirTransportistas(){
    FILE *pf;

    pf = fopen("../datos/Transportistas.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    char buffer[MAX_LIN_FICH_TRANS];  

    printf("\tListado de Transportistas:\n\n");

    // leemos linea a linea el fichero Transportistas.txt
    while(fgets(buffer, MAX_LIN_FICH_TRANS, pf) != NULL)
        printf("%s", buffer);

    fclose(pf);  
}

static void modificarFicheroTransportistas(tTransportista transportistaMod){
    FILE *pf, *temp;
    char buffer[MAX_LIN_FICH_TRANS];
    char *fich = "../datos/Transportistas.txt";
    char *fichTemp = "../datos/Temp-Transportistas.txt";

    pf = fopen(fich, "r");
    temp = fopen(fichTemp, "w");

    if(pf == NULL || temp == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    // Buscar la ID en el fichero y cambiar la linea por los datos de transportistaMod
    while(fgets(buffer, MAX_LIN_FICH_TRANS, pf) != NULL){
        char idFich[ID_TR];
        
        strncpy(idFich, buffer, ID_TR-1);    // En id se almacena los 7 primeros caracteres de cada linea

        // En temp se guardara el fichero modificado
        if(strncmp(idFich, transportistaMod.Id_transp, ID_TR-1) == 0){
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numTransportistas
            if(numTransportistas() == atoi(idFich))
                fprintf(temp, "%s-%s-%s-%s-%s-%s", transportistaMod.Id_transp, transportistaMod.Nombre, transportistaMod.email,
                                                   transportistaMod.Contrasenia, transportistaMod.Nomb_empresa, transportistaMod.Ciudad);
        
            else
                fprintf(temp, "%s-%s-%s-%s-%s-%s\n", transportistaMod.Id_transp, transportistaMod.Nombre, transportistaMod.email,
                                                     transportistaMod.Contrasenia, transportistaMod.Nomb_empresa, transportistaMod.Ciudad);
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


static int existeCambiosTransportistas(tTransportista nuevo, tTransportista original){
    int boole = 1;

    if(nuevo.Nombre == original.Nombre && nuevo.email == original.email
        && nuevo.Contrasenia == original.Contrasenia && nuevo.Nomb_empresa == original.Nomb_empresa 
        && nuevo.Ciudad == original.Ciudad)
        boole = 0;
    
    return boole;
}

static char *obtenerNombreTransportista(){
    int i = 0;
    char c, *nombre;

    nombre = (char *) calloc(NOM, sizeof(char));

    if(nombre == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba su nombre de transportista (maximo 20 caracteres): ");    
    fflush(stdin);

    while((c = getchar()) != '\n' && i < NOM){    // Recogemos caracter a caracter para controlar el tamaño de entrada
        nombre[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nombre) > NOM-1){
        fprintf(stderr, "El nombre excede los 20 caracteres.");
        free(nombre);
        return NULL;
    } 
    
    if(strlen(nombre) == 0){
        fprintf(stderr, "El nombre no puede estar vacio.");
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

static char *obtenerNombreEmpresa(){
    int i = 0;
    char c, *nombre;

    nombre = (char *) calloc(NOM, sizeof(char));

    if(nombre == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscriba su nombre de su empresa (maximo 20 caracteres): ");    
    fflush(stdin);

    while((c = getchar()) != '\n' && i < NOM){    // Recogemos caracter a caracter para controlar el tamaño de entrada
        nombre[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nombre) > NOM-1){
        fprintf(stderr, "El nombre excede los 20 caracteres.");
        free(nombre);
        return NULL;
    } 
    
    if(strlen(nombre) == 0){
        fprintf(stderr, "El nombre no puede estar vacio.");
        free(nombre);
        return NULL;
    }

    return nombre;
}

static char *obtenerCiudad(){
    int i = 0;
    char c, *nomCiudad;

    nomCiudad = (char *) calloc(CIUDAD, sizeof(char));

    if(nomCiudad == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    printf("\nEscribe el nombre de la ciudad de reparto (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < CIUDAD){        // Recogemos caracter a caracter para controlar el tamaño de entrada
        nomCiudad[i] = c;
        i++;
    }

    // Comprobamos si el tamaño es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la función
    if(strlen(nomCiudad) > CIUDAD-1){
        fprintf(stderr, "El nombre de la ciudad de reparto excede los 20 caracteres.");
        free(nomCiudad);
        return NULL;
    }

    if(strlen(nomCiudad) == 0){
        fprintf(stderr, "El nombre de la ciudad de reparto no puede estar vacio.");
        free(nomCiudad);
        return NULL;
    }

    return nomCiudad;
}
