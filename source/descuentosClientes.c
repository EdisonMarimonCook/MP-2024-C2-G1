#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "descuentosClientes.h"

/* FUNCIONES PUBLICAS */

float obtenerDescuento(const char *id_cliente, const char *id_cod) {
    FILE *fichero_descuentos;
    char linea[150];
    char estado[9];
    float importe;
    float descuento_euros = 0.0;

    fichero_descuentos = fopen("../datos/Descuentos.txt", "r");
    if (fichero_descuentos == NULL) {
        printf("Error al abrir el fichero de descuentos.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), fichero_descuentos)) {
        char id_cod_leido_descuentos[MAX_ID_COD];

        if(sscanf(linea, "%[^-]-%*[^-]-%*[^-]-%[^-]-%f-%*[^\n]", id_cod_leido_descuentos, estado, &importe) != 3)
            printf("Error leyendo fichero_descuentos.\n");
        
        if (strcmp(id_cod, id_cod_leido_descuentos) == 0 && strcmp(estado, "activo") == 0) {
            FILE *fichero_clientes;
            char linea_cliente[100];
            char id_cliente_leido[8];

            fichero_clientes = fopen("../datos/DescuentosClientes.txt", "r");
            
            if (fichero_clientes == NULL) {
                printf("Error al abrir el fichero de descuentos de clientes.\n");
                exit(1);
            }
            
            while (fgets(linea_cliente, sizeof(linea_cliente), fichero_clientes)) {
                char id_cod_leido_clientes[11];
                sscanf(linea_cliente, "%[^-]-%[^-]-%*[^-]-%*[^\n]", id_cliente_leido, id_cod_leido_clientes);

                if (strcmp(id_cliente, id_cliente_leido) == 0 && strcmp(id_cod, id_cod_leido_clientes) == 0) {
                    descuento_euros = importe;
                    break;
                }
            }

            fclose(fichero_clientes);
        }
    }

    fclose(fichero_descuentos);
    system("pause");
    return descuento_euros;
}

void menuDescuentosCliente(const char *idCliente){
    system("cls");

    FILE *fichero;
    char linea[MAX_LIN_FICH_DESC_CLI];
    descuentosClientes *descuentos;
    int num_descuentos = 0;

    descuentos = (descuentosClientes*)calloc(2, sizeof(descuentosClientes));

    if(descuentos == NULL){
        fprintf(stderr, "Error en asignacion de memoria.\n");
        exit(1);
    }

    fichero = fopen("../datos/DescuentosClientes.txt", "r");
    if (fichero == NULL) {
        perror("Error al abrir el fichero.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), fichero)) {
        sscanf(linea, "%[^-]-%[^-]-%[^-]-%[^-]-%d",
                descuentos[num_descuentos].Id_cliente,
                descuentos[num_descuentos].Id_cod,
                descuentos[num_descuentos].fechaAsignacion,
                descuentos[num_descuentos].fechaCaducidad,
                &descuentos[num_descuentos].Estado);

        descuentos = (descuentosClientes*)realloc(descuentos, (num_descuentos+2) * sizeof(descuentosClientes));
        
        if(descuentos == NULL){
            fprintf(stderr, "Error en asignacion de memoria.");
            exit(1);
        }
        
        num_descuentos++;
    }

    consultarDescuentos(idCliente, descuentos, num_descuentos);

    fclose(fichero);
    
    // por estética
    system("pause");
    system("cls");
}

/* FUNCIONES PRIVADAS */

static void consultarDescuentos(const char *id_cliente, descuentosClientes *descuentos, int num_descuentos) {
    if(num_descuentos == 0)
        printf("No se han encontrado codigos promocionales y cheques de regalo para el cliente.\n");
    else{
        printf("Códigos promocionales y cheques regalo asignados al cliente %s:\n", id_cliente);
        
        int i = 0;

        for(; i < num_descuentos; i++) {
            if (strcmp(descuentos[i].Id_cliente, id_cliente) == 0) {
                printf("Codigo: %s \nFecha Asignacion:%s \nFecha Caducidad: %s \nEstado: %s\n", 
                        descuentos[i].Id_cod, 
                        descuentos[i].fechaAsignacion, descuentos[i].fechaCaducidad,
                        descuentos[i].Estado ? "Aplicado" : "No aplicado");
            }
        }
    }    
}
