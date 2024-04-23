#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descuentosClientes.h"

static void consultarDescuentos(const char *id_cliente, descuentosClientes *descuentos, int num_descuentos) {

    printf("Códigos promocionales y cheques regalo asignados al cliente %s:\n", id_cliente);
    for (int i = 0; i < num_descuentos; i++) {
        if (strcmp(descuentos[i].Id_cliente, id_cliente) == 0) {
            printf("Codigo: %s \nFecha Asignacion:%s \nFecha Caducidad: %s \nEstado: %s\n", 
                    descuentos[i].Id_cod, 
                    descuentos[i].fechaAsignacion, descuentos[i].fechaCaducidad,
                    descuentos[i].Estado ? "Aplicado" : "No aplicado");
        }
    }
}

void menuDescuentosCliente(const char *idCliente){

    FILE *fichero;
    char linea[100];
    descuentosClientes *descuentos;
    int num_descuentos = 0;

    descuentos = (descuentosClientes*)calloc(2, sizeof(descuentosClientes));

    fichero = fopen("../datos/DescuentosClientes.txt", "r");
    if (fichero == NULL) {
        perror("Error al abrir el fichero.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), fichero)) {
        sscanf(linea, "%7s-%10s-%10s-%10s-%d",
                descuentos[num_descuentos].Id_cliente,
                descuentos[num_descuentos].Id_cod,
                descuentos[num_descuentos].fechaAsignacion,
                descuentos[num_descuentos].fechaCaducidad,
                &descuentos[num_descuentos].Estado);

        descuentos = (descuentosClientes*)realloc(descuentos, (num_descuentos+2) * sizeof(descuentosClientes));
        num_descuentos++;
    }

    consultarDescuentos(idCliente, descuentos, num_descuentos);

    fclose(fichero);

}

int main(){

    const char *id = "0000001";

    menuDescuentosCliente(id);

    return 0;
}