#include <stdio.h>
#include <stdlib.h>

#include "clientes.h"

int main(){
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
            fprintf(stderr, "\nEntrada no valida. Opcion Incorrecta.\n");
        }

	} while(op < 0 || op > 2);

	system("pause");

	return 0;
}
