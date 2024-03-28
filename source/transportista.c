#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transportista.h"
#include "usuarios.h"   // existeEmail()

/* FUNCIONES PUBLICAS */

// TODO: renombrar en adminprov y probablemente en clientes funcion de guardarAdminProv y 
// terminar registro de transportistas en usuarios.c

void infoTransportistas(){
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
                case 1: registrarTransportista(); break;
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
                case 1: getNombreTransportista(transportista, TRANSPORTISTA); break;
                case 2: getEmailTransportista(transportista); break;
                case 3: getContraseniaTransportista(transportista); break;
                case 4: getNombreTransportista(transportista, EMPRESA); break;
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

void getNombreTransportista(tTransportista *transportista, tNombre t){
    char *nombre = NULL;

    while(!nombre)
        nombre = obtenerNombreTransportistaOempresa(t);

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

void getCiudad(tTransportista *transportista){
    char *ciudad = NULL;

    while(!ciudad)
        ciudad = obtenerCiudad();

    strncpy(transportista->Ciudad, ciudad, CIUDAD);
    free(ciudad);
}


/* FUNCIONES PRIVADAS */

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
            // si se añade una linea de mas al final del fichero, tendremos problemas con el numClientes
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

static char *obtenerNombreTransportistaOempresa(tNombre t){
    int i = 0;
    char c, *nombre;

    nombre = (char *) calloc(NOM, sizeof(char));

    if(nombre == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    if(t == TRANSPORTISTA) 
        printf("\nEscriba su nombre de transportista (maximo 20 caracteres): ");
    else // t es o TRANSPORTISTA o EMPRESA
        printf("\nEscriba el nombre de su empresa (maximo 20 caracteres): ");
    
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
