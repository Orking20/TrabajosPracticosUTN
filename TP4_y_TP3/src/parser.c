#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Dirección del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	char idEmployee[10];
	char bufferNombre[128];
	char bufferHorasTrabajadas[10];
	char bufferSueldo[10];
	Employee* auxiliarEmployee = NULL;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", idEmployee, bufferNombre, bufferHorasTrabajadas, bufferSueldo) == 4)
			{
				auxiliarEmployee = employee_newParametros(idEmployee, bufferNombre, bufferHorasTrabajadas, bufferSueldo);
				if(auxiliarEmployee != NULL)
				{
					if(!ll_add(pArrayListEmployee, auxiliarEmployee))
					{
						retorno = 0;
					}
				}
			}
		}while(!feof(pFile));
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char* Dirección del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* auxiliarEmployee = NULL;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			auxiliarEmployee = employee_new();
			if(auxiliarEmployee != NULL && fread(auxiliarEmployee, sizeof(Employee), 1, pFile) == 1)
			{
				if(!ll_add(pArrayListEmployee, auxiliarEmployee))
				{
					retorno = 0;
				}
			}
			else
			{
				employee_delete(auxiliarEmployee);
			}
		}while(!feof(pFile));
	}

    return retorno;
}
