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
	int operador;

	printf("<<<<<<<<    CALCULADORA    >>>>>>>>\n");

	do
	{
		//Ingreso de números y validación
		utn_getFloat(&numeroA, "\n\n\nIngresar el 1er operando: ", "Error! Solo se pueden ingresar números");
		utn_getFloat(&numeroB, "\nIngresar el 2do operando: ", "Error! Solo se pueden ingresar números");

		//Menú de opciones
		printf("\n1) Calcular la suma (%0.2f + %0.2f)", numeroA, numeroB);
		printf("\n2) Calcular la resta (%0.2f - %0.2f)", numeroA, numeroB);
		printf("\n3) Calcular la división (%0.2f / %0.2f)", numeroA, numeroB);
		printf("\n4) Calcular la multiplicación (%0.2f * %0.2f)", numeroA, numeroB);
		printf("\n5) Calcular el factorial (%0.2f!) (%0.2f!)", numeroA, numeroB);
		printf("\n6) Salir\n");

		//Ingreso de operador
		utn_getNumero(&operador, "\nIngrese el número correspondiente a la operación: ", "Hubo un error! Debe ingresar un número según las opciónes del menú\n", 1, 6);

		switch(operador)
		{
			case 1:
			{
				utn_sumar(numeroA, numeroB, &resultado);
				printf("El resultado de %0.2f + %0.2f es: %0.2f", numeroA, numeroB, resultado);
				break;
			}
			case 2:
			{
				utn_restar(numeroA, numeroB, &resultado);
				printf("El resultado de %0.2f - %0.2f es: %0.2f", numeroA, numeroB, resultado);
				break;
			}
			case 3:
			{
				if(utn_dividir(numeroA, numeroB, &resultado, "Error. No se puede dividir por cero\n") == 0)
				{
					printf("El resultado de %0.2f / %0.2f es: %0.2f", numeroA, numeroB, resultado);
				}
				break;
			}
			case 4:
			{
				utn_multiplicar(numeroA, numeroB, &resultado);
				printf("El resultado de %0.2f * %0.2f es: %0.2f", numeroA, numeroB, resultado);
				break;
			}
			case 5:
			{
				utn_factorial(numeroA, &resultado);
				printf("\nEl factorial de %0.2f es: %0.2f", numeroA, resultado);
				utn_factorial(numeroB, &resultado);
				printf(" y el factorial de %0.2f es: %0.2f", numeroB, resultado);
				break;
			}
		}
	}while(operador != 6);

	return EXIT_SUCCESS;
}
