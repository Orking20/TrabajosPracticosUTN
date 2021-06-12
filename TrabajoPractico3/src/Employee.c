#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"

static int contador = 0;

/*
 * brief Asigna espacio en la memoria heap para un Employee
 * \return Retora el espacio de memoria obtenido o si no lo pudo conseguir NULL*/
Employee* employee_new(void)
{
	return (Employee*)malloc(sizeof(Employee));
}

/*
 * brief Asigna espacio en la memoria para un nuevo empleado y asigna valores a sus campos
 * \param char* idStr Asigna un valor a idStr
 * \param char* nombreStr Asigna un valor a nombreStr
 * \param char* horasTrabajadasStr Asigna un valor a horasTrabajadasStr
 * \param char* sueldoStr Asigna un valor a sueldoStr
 * \return Retora el espacio de memoria con valores cargados o NULL*/
Employee* employee_newParametros(char* idStr, char* nombreStr, char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* auxEmployee = employee_new();

	if(auxEmployee != NULL)
	{
		if(employee_setId(auxEmployee, atoi(idStr)) < 0 ||
		   employee_setNombre(auxEmployee, nombreStr) < 0 ||
		   employee_setHorasTrabajadas(auxEmployee, atoi(horasTrabajadasStr)) < 0 ||
		   employee_setSueldo(auxEmployee, atoi(sueldoStr)) < 0)
		{
			employee_delete(auxEmployee);
			auxEmployee = NULL;
		}
	}

	return auxEmployee;
}

/*
 * brief Libera el espacio de memoria entregado por parametro
 * \param Employee* this Puntero que va a ser liberado
 * \return Retora 0 (EXITO) o -1 (ERROR)*/
int employee_delete(Employee* this)
{
	int retorno = -1;

	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}

	return retorno;
}

//ID

void setearValorMaximoId(int id)
{
	contador = id;
}

int generarId(void)
{
	contador++;
	return contador;
}

//----------------Setters----------------

/*
 * brief Comprueba que id sea válido y lo asigna a la estructura
 * \param Employee* this Donde se guardará el dato obtenido
 * \param int id Dato que se evaluará y guardará en la estructura
 * \return Retora 0 (EXITO) o -1 (ERROR)*/
int employee_setId(Employee* this, int id)
{
	int retorno = -1;

	if(this != NULL && isValidId(id))
	{
		this->id = id;
		retorno = 0;
	}

	return retorno;
}

/*
 * brief Comprueba que nombre sea válido y lo asigna a la estructura
 * \param Employee* this Donde se guardará el dato obtenido
 * \param char* nombre Dato que se evaluará y guardará en la estructura
 * \return Retora 0 (EXITO) o -1 (ERROR)*/
int employee_setNombre(Employee* this, char* nombre)
{
	int retorno = -1;

	if(this != NULL && isValidNombre(nombre))
	{
		strncpy(this->nombre, nombre, sizeof(this->nombre));
		retorno = 0;
	}

	return retorno;
}

/*
 * brief Comprueba que horasTrabajadas sea válido y lo asigna a la estructura
 * \param Employee* this Donde se guardará el dato obtenido
 * \param int horasTrabajadas Dato que se evaluará y guardará en la estructura
 * \return Retora 0 (EXITO) o -1 (ERROR)*/
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int retorno  = -1;

	if(this != NULL && isValidHorasTrabajadas(horasTrabajadas))
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno  = 0;
	}

	return retorno;
}

/*
 * brief Comprueba que sueldo sea válido y lo asigna a la estructura
 * \param Employee* this Donde se guardará el dato obtenido
 * \param int sueldo Dato que se evaluará y guardará en la estructura
 * \return Retora 0 (EXITO) o -1 (ERROR)*/
int employee_setSueldo(Employee* this, int sueldo)
{
	int retorno = -1;

	if(this != NULL && isValidSueldo(sueldo))
	{
		this->sueldo = sueldo;
		retorno = 0;
	}

	return retorno;
}

//----------------Getters----------------

/*
 * brief Obtiene el valor de id
 * \param Employee* this Dato que queremos obtener
 * \param int* flagError Nos avisa si hay algún error
 * \return Retora el valor dentro de id o NULL*/
int employee_getId(Employee* this, int* flagError)
{
	*flagError = -1;
	int auxId = -1;

	if(this != NULL && flagError != NULL)
	{
		auxId = this->id;
		*flagError = 0;
	}

	return auxId;
}

/*
 * brief Obtiene el valor de nombre
 * \param Employee* this Dato que queremos obtener
 * \param int* flagError Nos avisa si hay algún error
 * \return Retora el valor dentro de nombre o NULL*/
char* employee_getNombre(Employee* this, int* flagError)
{
	*flagError = -1;
	char* auxnombre = NULL;

	if(this != NULL && flagError != NULL)
	{
		auxnombre = this->nombre;
		*flagError = 0;
	}

	return auxnombre;
}

/*
 * brief Obtiene el valor de horasTrabajadas
 * \param Employee* this Dato que queremos obtener
 * \param int* flagError Nos avisa si hay algún error
 * \return Retora el valor dentro de horasTrabajadas o NULL*/
int employee_getHorasTrabajadas(Employee* this, int *flagError)
{
	*flagError = -1;
	int auxHorasTrabajadas = -1;

	if(this != NULL && flagError != NULL)
	{
		auxHorasTrabajadas = this->horasTrabajadas;
		*flagError = 0;
	}

	return auxHorasTrabajadas;
}

/*
 * brief Obtiene el valor de sueldo
 * \param Employee* this Dato que queremos obtener
 * \param int* flagError Nos avisa si hay algún error
 * \return Retora el valor dentro de sueldo o NULL*/
int employee_getSueldo(Employee* this, int* flagError)
{
	*flagError = -1;
	int auxSueldo = -1;

	if(this != NULL && flagError != NULL)
	{
		auxSueldo = this->sueldo;
		*flagError = 0;
	}

	return auxSueldo;
}

//----------------Validaciones----------------

/*
 * brief Comprueba que el ID sea válido
 * \param int id El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)*/
int isValidId(int id)
{
	int retorno = -1;

	if(id > 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}

/*
 * brief Comprueba que la nombre sea válida
 * \param char* nombre El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)*/
int isValidNombre(char* nombre)
{
	int retorno = -1;

	if(nombre != NULL)
	{
		retorno = 1;
	}

	return retorno;
}

/*
 * brief Comprueba que la apellido sea válida
 * \param int horasTrabajadas El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)*/
int isValidHorasTrabajadas(int horasTrabajadas)
{
	int retorno = -1;

	if(horasTrabajadas >= 0 && horasTrabajadas <= 1500)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}

/*
 * brief Comprueba que el sueldo sea válido
 * \param int sueldo El dato a comprobar que sea válido
 * \return Retora 1 si es válido, 0 si no es válido o -1 (ERROR)*/
int isValidSueldo(int sueldo)
{
	int retorno = -1;

	if(sueldo >= 0 && sueldo <= 1000000)
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}
