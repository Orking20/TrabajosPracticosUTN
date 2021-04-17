/*
 * utn.h
 *
 *  Created on: 27 mar. 2021
 *      Author: Mateo Luchetti Capalbo
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNumero(int* pNumero, const char* pTexto, const char* mensajeError, int min, int max);
int utn_getFloat(float* pNumero, const char* pTexto, const char* mensajeError);

int utn_sumar(float numeroA, float numeroB, float* pResultado);
int utn_restar(float numeroA, float numeroB, float* pResultado);
int utn_dividir(float dividendo, float divisor, float* pResultado, const char* pDivisionPorCero);
int utn_multiplicar(float dividendo, float divisor, float* pResultado);
int utn_factorial(float numero, float* pResultado);

#endif /* UTN_H_ */
