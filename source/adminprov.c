#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adminprov.h"

/* FUNCIONES PUBLICAS */

// TODO: TERMINAR ESTA FUNCIÓN
void menuAdminProv(tAdminProv *adminprov){
    printf("MENU ADMINPROV");
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
    int i;
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
    int i = 0, fin = 0;

    while(i < numAdminProvs() && !fin){
        if(strcmp(infoAdminProv[i].email, email) == 0 && strcmp(infoAdminProv[i].Contrasenia, psw) == 0)
            fin = 1;

        ++i;
    }

    if(fin == 1)
        fin = i;    // devolvemos en que posicion se ha encontrado del vector infocli

    return fin;
}


/* FUNCIONES PRIVADAS */

static unsigned numAdminProvs(){
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
