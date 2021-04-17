/*
 ============================================================================
 Name        : TrabajoPractico1.c
 Author      : Mateo Luchetti Capalbo
 Version     :
 Copyright   : Your copyright notice
 Description : Calculadora que puede sumar, restar, multiplicar, dividir y
 	 	 	   encontrar el factorial de dos números
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "utn.h"

int main(void)
{
	float numeroA;
	float numeroB;
	float resultado;
	int opcionMenu;
	int flagPrimeraVez = 1;

	printf("<<<<<<<<    CALCULADORA    >>>>>>>>\n");

	do
	{
		//Menú
		menu(&opcionMenu, &numeroA, &numeroB, &flagPrimeraVez);

		//
		if(flagPrimeraVez == 0)
		{
			switch(opcionMenu)
			{
				case 1:
				{
					utn_getFloat(&numeroA, "\n\n\nIngresar 1er operando: ", "Error! Solo se pueden ingresar números");
					break;
				}
				case 2:
				{
					utn_getFloat(&numeroB, "\nIngresar 2do operando: ", "Error! Solo se pueden ingresar números");
					break;
				}
				case 3:
				{
					utn_sumar(numeroA, numeroB, &resultado);
					printf("\nEl resultado de %0.2f + %0.2f es: %0.2f", numeroA, numeroB, resultado);
					break;
				}
				case 4:
				{
					utn_restar(numeroA, numeroB, &resultado);
					printf("\nEl resultado de %0.2f - %0.2f es: %0.2f", numeroA, numeroB, resultado);
					break;
				}
				case 5:
				{
					if(utn_dividir(numeroA, numeroB, &resultado, "\nError. No se puede dividir por cero") == 0)
					{
						printf("\nEl resultado de %0.2f / %0.2f es: %0.2f", numeroA, numeroB, resultado);
					}
					break;
				}
				case 6:
				{
					utn_multiplicar(numeroA, numeroB, &resultado);
					printf("\nEl resultado de %0.2f * %0.2f es: %0.2f", numeroA, numeroB, resultado);
					break;
				}
				case 7:
				{
					utn_factorial(numeroA, &resultado);
					printf("\nEl factorial de %0.2f es: %0.2f", numeroA, resultado);
					utn_factorial(numeroB, &resultado);
					printf(" y el factorial de %0.2f es: %0.2f", numeroB, resultado);
					break;
				}
				case 8:
				{
					utn_sumar(numeroA, numeroB, &resultado);
					printf("\nEl resultado de %0.2f + %0.2f es: %0.2f", numeroA, numeroB, resultado);

					utn_restar(numeroA, numeroB, &resultado);
					printf("\nEl resultado de %0.2f - %0.2f es: %0.2f", numeroA, numeroB, resultado);

					if(utn_dividir(numeroA, numeroB, &resultado, "\nError. No se puede dividir por cero") == 0)
					{
						printf("\nEl resultado de %0.2f / %0.2f es: %0.2f", numeroA, numeroB, resultado);
					}

					utn_multiplicar(numeroA, numeroB, &resultado);
					printf("\nEl resultado de %0.2f * %0.2f es: %0.2f", numeroA, numeroB, resultado);

					utn_factorial(numeroA, &resultado);
					printf("\nEl factorial de %0.2f es: %0.2f", numeroA, resultado);
					utn_factorial(numeroB, &resultado);
					printf(" y el factorial de %0.2f es: %0.2f", numeroB, resultado);
					break;
				}
			}
		}
		else
		{
			continue;
		}
	}while(opcionMenu != 9);

	return EXIT_SUCCESS;
}
