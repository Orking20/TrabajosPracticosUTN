/*
 * utn.h
 *
 *  Created on: 25 mar. 2021
 *      Author: mateo
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNumero(int* pNumero, char* pMensaje, char* pMensajeError, int min, int max, int reintentos);
int utn_getDecimal(float* pNumero, char* pMensaje, char* pMensajeError, float min, float max, int reintentos);
int utn_getTexto(char* pString, int limite, char* pMensaje, char* pMensajeError);
int utn_getPalabra(char* pString, int limite, char* pMensaje, char* pMensajeError);
int utn_getCaracter(char* pChar, char* pMensaje, char* pMensajeError, char min, char max, int reintentos);

int utn_getCadenaMayusculas(char* pString, int limite, char* pMensaje, char* pMensajeError);
int utn_getCadenaMinusculas(char* pString, int limite, char* pMensaje, char* pMensajeError);

int utn_getNombre(char* pNombre, char* pMensaje, char* pMensajeError);
int utn_getDescripcion(char* pDescripcion, char* pMensaje, char* pMensajeError);
int utn_getDni(char* pDni, char* pMensaje, char* pMensajeError);
int utn_getCuit(char* pCuit, char* pMensaje, char* pMensajeError);
int utn_getEdad(int* pEdad, char* pMensaje, char* pMensajeError);
int utn_getPrecio(float* pPrecio, char* pMensaje, char* pMensajeError);
int utn_getTelefono(char* pTelefono, char* pMensaje, char* pMensajeError);
int utn_getCelular(char* pCelular, char* pMensaje, char* pMensajeError);
int utn_getEmail(char* pEmail, char* pMensaje, char* pMensajeError);
int utn_getSitioWeb(char* pSitioWeb, char* pMensaje, char* pMensajeError);
int utn_getTarjetaCredito(char* pTarjeta, char* pMensaje, char* pMensajeError);
int utn_getDireccion(char* pDireccion, char* pMensaje, char* pMensajeAltura, char* pMensajeError, char* pMensajeErrorAltura);
int utn_getNombreArchivo(char* pArchivo, char* pMensaje, char* pMensajeError);
int utn_getEstadoCivil(char* pEstadoCivil, char* pMensaje, char* pMensajeError);
int utn_getSexo(char* pSexo, char* pMensaje, char* pMensajeError);

#endif /* UTN_H_ */
