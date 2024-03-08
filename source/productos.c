#include <stdio.h>
#include <stdlib.h>
#include "productos.h"
#include "clientes.h"

static void consultaProductos (){
    FILE *f;
    
    f = fopen("../datos/Productos.txt", "r");

    if (f == NULL){
        fprintf (stderr, "Error en la apertura de fichero.\n");
        exit (1);
    }

    char buffer[MAX_LIN_FICH_PROD];
    
    // leemos linea a linea el fichero Productos.txt
    while(fgets(buffer, MAX_LIN_FICH_PROD, f) != NULL)
        printf("%s", buffer);

    fclose(f);
}

/*void cargarProductos (t_productos *info_prod){
    int i;
    char buffer[]
}*/

