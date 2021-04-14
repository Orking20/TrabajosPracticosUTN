/*
 * utn.c
 *
 *  Created on: 27 mar. 2021
 *      Author: Mateo Luchetti Capalbo
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>

static int getInt(int *pResultado);
static int getFloat(float *pResultado);
static int esNumerica(char* cadena);
static int esDecimal(char* cadena);
static int myGets(char* cadena, int longitud);

/**
 * \brief Le pide al usuario un número entero entre un rango
 * \param int* pNumero: Puntero donde se almacena el número ingresado por el usuario
 * \param const char* pTexto: Texto para que el usuario sepa que ingresar
 * \param const char* mensajeError: Texto que nos indica que hubo un error
 * \param int min: El rango mínimo para ingresar un número
 * \param int max: El rango máximo para ingresar un número
 * \return Retorna 0 (EXITO) si se obtiene un número entre el rango o -1 (ERROR) si no*/
int utn_getNumero(int* pNumero, const char* pTexto, const char* mensajeError, int min, int max)
{
	int retorno = -1;
	int bufferInt;

	if(pNumero != NULL && pTexto != NULL && mensajeError != NULL && min <= max)
	{
		do
		{
			printf(pTexto);
			__fpurge(stdin);
			if(getInt(&bufferInt) == 0)
			{
				if(bufferInt >= min && bufferInt <= max)
				{
					retorno = 0;
					*pNumero = bufferInt;
					break;
				}
			}

			printf(mensajeError);
		}while(bufferInt < min || bufferInt > max);
	}

	return retorno;
}

/**
 * \brief Le pide al usuario un número racional
 * \param float* pNumero: Puntero donde se almacena el número ingresado por el usuario
 * \param const char* pTexto: Texto para que el usuario sepa que ingresar
 * \param const char* sError: Texto que nos indica que hubo un error
 * \return Retorna 0 (EXITO) si se obtiene un número racional o -1 (ERROR) si no*/
float utn_getFloat(float* pNumero, const char* pTexto, const char* mensajeError)
{
	int retorno = -1;
	float bufferFloat;

	if(pNumero != NULL && pTexto != NULL && mensajeError != NULL)
	{
		printf(pTexto);
		__fpurge(stdin);
		if(getFloat(&bufferFloat) == 0)
		{
			retorno = 0;
			*pNumero = bufferFloat;
		}
		else
		{
			printf(mensajeError);
		}
	}
	else
	{
		printf(mensajeError);
	}

	return retorno;
}

/**
 * \brief Transforma una cadena de caractéres a números si es posible
 * \param int* pResultado: Puntero donde se almacenará el número ingresado
 * \return Retorna 0 (EXITO) si se obtiene un número entero o -1 (ERROR) si no*/
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[64];

	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer))
		{
			*pResultado = atoi(buffer);
			retorno = 0;
		}
	}

	return retorno;
}

/**
 * \brief Transforma una cadena de caractéres a números decimales si es posible
 * \param float* pResultado: Puntero donde se almacenará el número ingresado
 * \return Retorna 0 (EXITO) si se obtiene un número decimal o -1 (ERROR) si no*/
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[64];

	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esDecimal(buffer))
		{
			*pResultado = atof(buffer);
			retorno = 0;
		}
	}

	return retorno;
}

/**
 * \brief Verifica que la cadena recibida contenga solamente números positivos o negativos
 * \param char* cadena: Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es numérica, 0 (falso) si no o -1 si hubo algún error con los argumentos*/
static int esNumerica(char* cadena)
{
	int retorno = -1;
	int signo = 1;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		retorno = 0;
		for(int i = 0; cadena[i] != '\0'; i++)
		{
			if(cadena[i] >= '0' && cadena[i] <= '9')
			{
				if(i == 0 && cadena[i] == '-' && signo)
				{
					signo = 0;
				}
				retorno = 1;
			}
		}
	}

	return retorno;
}

/**
 * \brief Verifica que la cadena recibida contenga solamente números decimales positivos o negativos
 * \param char* cadena: Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es decimal, 0 (falso) si no o -1 si hubo algún error con los argumentos*/
static int esDecimal(char* cadena)
{
	int retorno = -1;
	int punto = 1;
	int signo = 1;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		retorno = 0;
		for(int i = 0; cadena[i] != '\0'; i++)
		{
			if(cadena[i] >= '0' && cadena[i] <= '9')
			{
				if(i == 0 && cadena[i] == '-' && signo)
				{
					signo = 0;
				}
				if(cadena[i] == '.' && punto)
				{
					punto = 0;
				}
				retorno = 1;
			}
		}
	}

	return retorno;
}

/**
* \brief Verifica que en la cadena no quede un enter
* \param char* cadena: Puntero al espacio de memoria donde se copiará la cadena obtenida
* \param longitud: Define el tamaño de la cadena
* \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
*/
static int myGets(char* cadena, int longitud)
{
	int retorno = -1;

	if(cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin) == cadena)
	{
		__fpurge(stdin);
		if(cadena[strlen(cadena) - 1] == '\n')
		{
			cadena[strlen(cadena) - 1] = '\0';
		}
		retorno = 0;
	}

	return retorno;
}

/**
 * \brief Suma dos números y por medio de un puntero devuelve el resultado
 * \param float numeroA: Primer número de la operación
 * \param float numeroB: Segundo número de la operación
 * \param float* pResultado: El resultado de la suma, que va a llegar al main mediante un puntero
 * \return Retorna 0 (EXITO) si se pudo completar la suma o -1 (ERROR) si no*/
int utn_sumar(float numeroA, float numeroB, float* pResultado)
{
	int retorno = -1;
	float resultado;

	if(pResultado != NULL)
	{
		resultado = numeroA + numeroB;
		retorno = 0;
	}

	*pResultado = resultado;
	return retorno;
}

/**
 * \brief Resta dos números y por medio de un puntero devuelve el resultado
 * \param float numeroA: Primer número de la operación
 * \param float numeroB: Segundo número de la operación
 * \param float* pResultado: El resultado de la resta, que va a llegar al main mediante un puntero
 * \return Retorna 0 (EXITO) si se pudo completar la resta o -1 (ERROR) si no*/
int utn_restar(float numeroA, float numeroB, float* pResultado)
{
	int retorno = -1;
	float resultado;

	if(pResultado != NULL)
	{
		resultado = numeroA - numeroB;
		retorno = 0;
	}

	*pResultado = resultado;
	return retorno;
}

/**
 * \brief Divide dos números y por medio de un puntero devuelve el resultado
 * \param float numeroA: Primer número de la operación
 * \param float numeroB: Segundo número de la operación
 * \param float* pResultado: El resultado de la división, que va a llegar al main mediante un puntero
 * \param const char* pDivisionPorCero: Mensaje de error si el divisor es cero
 * \return Retorna 0 (EXITO) si se pudo completar la division o -1 (ERROR) si no o si el divisor es 0*/
int utn_dividir(float dividendo, float divisor, float* pResultado, const char* pDivisionPorCero)
{
	int retorno = -1;
	float resultado;

	if(pResultado != NULL)
	{
		if(divisor != 0)
		{
			resultado = dividendo / divisor;
			retorno = 0;
		}
		else
		{
			printf(pDivisionPorCero);
		}
	}

	*pResultado = resultado;
	return retorno;
}

/**
 * \brief Multiplica dos números y por medio de un puntero devuelve el resultado
 * \param float numeroA: Primer número de la operación
 * \param float numeroB: Segundo número de la operación
 * \param float* pResultado: El resultado de la multiplicación, que va a llegar al main mediante un puntero
 * \return Retorna 0 (EXITO) si se pudo completar la multiplicación o -1 (ERROR) si no*/
int utn_multiplicar(float dividendo, float divisor, float* pResultado)
{
	int retorno = -1;
	float resultado;

	if(pResultado != NULL)
	{
		resultado = dividendo * divisor;
		retorno = 0;
	}

	*pResultado = resultado;
	return retorno;
}

/**
 * \brief Factorisa un número ingresado y lo devuelve mediante un puntero
 * \param float numero: Número a ser factoriado
 * \param float* pResultado: El resultado de la factorización, que va a llegar al main mediante un puntero
 * \return Retorna 0 (EXITO) si se pudo completar la factorisación o -1 (ERROR) si no*/
int utn_factorial(float numero, float* pResultado)
{
	int retorno = -1;
	int acumulador = 1;

	if(pResultado != NULL)
	{
		for(int i = 1; i <= numero; i++)
		{
			acumulador *= i;
		}
		*pResultado = acumulador;
		retorno = 0;
	}

	return retorno;
}
