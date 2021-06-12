#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

static int buscarIdMaximo(LinkedList* pArrayLinkedList, int* idMaximo);
static int buscarEmpleado(LinkedList* pLinkedList);
static int buscarPorId(LinkedList* pLinkedList, int id);
static int ordenarPorId(void* elemento1, void* elemento2);
static int ordenarPorNombre(void* pEmployee1, void* pEmployee2);
static int ordenarPorHorasTrabajadas(void* elemento1, void* elemento2);
static int ordenarPorSueldo(void* elemento1, void* elemento2);

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Dirección del archivo
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile = NULL;

	pFile = fopen(path, "r");

	if(pArrayListEmployee != NULL && pFile != NULL)
	{
		if(!parser_EmployeeFromText(pFile, pArrayListEmployee))
		{
			fclose(pFile);
			printf("\nSe ha cargado exitosamente!");
			retorno = 0;
		}
		else
		{
			printf("\nError. El archivo no pudo abrirse");
		}
	}

    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo dataBinary.bin (modo binario).
 *
 * \param path char* Dirección del archivo
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile = NULL;

	pFile = fopen(path, "rb");

	if(path != NULL && pArrayListEmployee != NULL && pFile != NULL)
	{
		if(!parser_EmployeeFromBinary(pFile, pArrayListEmployee))
		{
			fclose(pFile);
			printf("\nSe ha cargado exitosamente!");
			retorno = 0;
		}
		else
		{
			printf("\nError. El archivo no pudo abrirse");
		}
	}

    return retorno;
}

/** \brief Alta de empleados
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int idEmployee;
	char bufferNombre[128];
	int bufferHorasTrabajadas;
	int bufferSueldo;
	Employee* auxiliarEmployee = NULL;

	if(pArrayListEmployee != NULL)
	{
		if(buscarEmpleado(pArrayListEmployee) == 1)
		{
			if(!utn_getNombre(bufferNombre, "\nIngrese el nombre: ", "\nError. Ese nombre no es válido\n") &&
			   !utn_getNumero(&bufferHorasTrabajadas, "Ingrese la cantidad de horas trabajadas: ", "\nError. El número ingresado no es válido\n", 0, 1500, 3) &&
			   !utn_getNumero(&bufferSueldo, "Ingrese el sueldo: ", "\nError. Ese sueldo no es válido\n", 0, 10000000, 3))
			{
				auxiliarEmployee = employee_new();

				buscarIdMaximo(pArrayListEmployee, &idEmployee);
				setearValorMaximoId(idEmployee);

				idEmployee = generarId();
				if(!employee_setId(auxiliarEmployee, idEmployee) &&
				   !employee_setNombre(auxiliarEmployee, bufferNombre) &&
				   !employee_setHorasTrabajadas(auxiliarEmployee, bufferHorasTrabajadas) &&
				   !employee_setSueldo(auxiliarEmployee, bufferSueldo))
				{
					if(!ll_add(pArrayListEmployee, auxiliarEmployee))
					{
						retorno = 0;
					}
				}
				else if(!employee_delete(auxiliarEmployee))
				{
					retorno = -1;
				}
			}
		}
		else
		{
			printf("\nAntes de dar de alta un nuevo empleado tienes que cargar los empleados en la opción 1 o 2 del menú");
		}
	}

    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int indice;
	int auxiliarId;
	char bufferNombre[128];
	int bufferHorasTrabajadas;
	int bufferSueldo;
	Employee* auxiliarEmployee = NULL;

	if(pArrayListEmployee != NULL)
	{
		if(buscarEmpleado(pArrayListEmployee) == 1)
		{
			utn_getNumero(&auxiliarId, "\nIngrese el ID del empleado que desea editar: ", "\nError. Ese ID no es válido", 1, 100000, 3);
			indice = buscarPorId(pArrayListEmployee, auxiliarId);
			if(indice >= 0)
			{
				auxiliarEmployee = (Employee*)ll_get(pArrayListEmployee, indice);
				if(auxiliarEmployee != NULL &&
				   !utn_getNombre(bufferNombre, "\nIngrese el nombre: ", "\nError. Ese nombre no es válido\n") &&
				   !utn_getNumero(&bufferHorasTrabajadas, "Ingrese la cantidad de horas trabajadas: ", "\nError. El número ingresado no es válido\n", 0, 1500, 3) &&
				   !utn_getNumero(&bufferSueldo, "Ingrese el sueldo: ", "\nError. Ese sueldo no es válido\n", 0, 10000000, 3))
				{
					employee_setNombre(auxiliarEmployee, bufferNombre);
					employee_setHorasTrabajadas(auxiliarEmployee, bufferHorasTrabajadas);
					employee_setSueldo(auxiliarEmployee, bufferSueldo);
					retorno = 0;
				}
			}
			else
			{
				printf("\nEse ID no coincide con ningún otro");
			}
		}
		else
		{
			printf("\nAntes de editar un empleado tienes que cargar los empleados en la opción 1 o 2 del menú");
		}
	}

    return retorno;
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retorna 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int auxiliarId;
	int indice;
	char confirmacion[24];
	Employee* auxiliarEmployee = NULL;

	if(pArrayListEmployee != NULL)
	{
		if(buscarEmpleado(pArrayListEmployee) == 1)
		{
			if(!utn_getNumero(&auxiliarId, "\nIngrese el ID del empleado que desea eliminar: ", "\nError. Ese ID no es válido", 1, 100000, 3))
			{
				indice = buscarPorId(pArrayListEmployee, auxiliarId);
				if(indice >= 0)
				{
					auxiliarEmployee = (Employee*)ll_get(pArrayListEmployee, indice);
					if(auxiliarEmployee != NULL &&
					   !utn_getRespuestaSiNo(confirmacion, "\nEstas seguro que quieres eliminar este empleado? (si/no)", "\nError. Solo puedes ingresar 'si' o 'no'") &&
					   strncmp(confirmacion, "si", 24) == 0)
					{
						if(!ll_remove(pArrayListEmployee, indice) && !employee_delete(auxiliarEmployee))
						{
							printf("\nSe ha eliminado con éxito");
							retorno = 0;
						}
					}
				}
			}
			else
			{
				printf("\nEse ID no coincide con ningún otro");
			}
		}
		else
		{
			printf("\nAntes de eliminar un empleado tienes que cargar los empleados en la opción 1 o 2 del menú");
		}
	}

    return retorno;
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int length = ll_len(pArrayListEmployee);
	Employee* pEmployee = NULL;

	if(pArrayListEmployee != NULL)
	{
		printf("ID\tNombre\t\t\tHoras Trabajadas\tSueldo\n--------------------------------------------------------------------------------\n");
		for(int i = 0; i < length; i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee,i);
			printf("\n%-7d %-23s %-23d %-8d", pEmployee->id, pEmployee->nombre, pEmployee->horasTrabajadas, pEmployee->sueldo);
		}

		retorno = 0;
	}

    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int opcion;
	int orden;

	if(pArrayListEmployee != NULL)
	{
		printf("\nAl ordenar puede tardar unos segundos...");
		if(!utn_getNumero(&opcion, "\n¿Por que campo quiere ordenar (1-ID | 2-Nombre | 3-Horas trabajadas | 4-Sueldo)? ", "\nError. Solo puedes ingresar 1, 2, 3 o 4", 1, 4, 3) &&
		   !utn_getNumero(&orden, "\nIngrese el orden (1-Ascendente | 0-Descendente): ", "\nError. Solo puedes ingresar 1 o 0", 0, 1, 3))
		{
			switch(opcion)
			{
				case 1:
				{
					if(!ll_sort(pArrayListEmployee, ordenarPorId, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 2:
				{
					if(!ll_sort(pArrayListEmployee, ordenarPorNombre, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 3:
				{
					if(!ll_sort(pArrayListEmployee, ordenarPorHorasTrabajadas, orden))
					{
						retorno = 0;
					}
					break;
				}
				case 4:
				{
					if(!ll_sort(pArrayListEmployee, ordenarPorSueldo, orden))
					{
						retorno = 0;
					}
					break;
				}
			}
		}
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee = NULL;
	FILE* pFile;
	int flagError;

	pFile = fopen(path, "w");

	if(path != NULL && pArrayListEmployee != NULL && pFile != NULL)
	{
		for(int i = 0; i < ll_len(pArrayListEmployee); i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			fprintf(pFile, "%d,%s,%d,%d\n", employee_getId(pEmployee, &flagError), employee_getNombre(pEmployee, &flagError), employee_getHorasTrabajadas(pEmployee, &flagError), employee_getSueldo(pEmployee, &flagError));
		}

		fclose(pFile);
		printf("\nSe ha guardado correctamente!");
		retorno = 0;
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee = NULL;
	FILE* pFile = NULL;

	pFile = fopen(path, "w+");

	if(path != NULL && pArrayListEmployee != NULL && pFile != NULL)
	{
		for(int i= 0; i < ll_len(pArrayListEmployee); i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			fwrite(pEmployee, sizeof(Employee), 1, pFile);
		}

		fclose(pFile);
		printf("\nSe ha guardado correctamente!");
		retorno = 0;
	}

    return retorno;
}

/** \brief Busca el ID máximo
 *
 * \param pArrayLinkedList LinkedList* Listado de todos los empleados
 * \param idMaximo int*
 * \return Retora 0 (EXITO) o -1 (ERROR)
 *
 */
static int buscarIdMaximo(LinkedList* pArrayLinkedList, int* idMaximo)
{
	int retorno = -1;
	int i;
	Employee* AuxiliarEmployee = NULL;
	int flagError;
	int auxiliarId;
	int auxiliarMaxId;

	if(pArrayLinkedList != NULL && idMaximo != NULL)
	{
		for(i = 0; i < ll_len(pArrayLinkedList); i++)
		{
			AuxiliarEmployee = (Employee*)ll_get(pArrayLinkedList, i);
			auxiliarId = employee_getId(AuxiliarEmployee, &flagError);
			if(!flagError && (i == 0 || auxiliarId > auxiliarMaxId))
			{
				auxiliarMaxId = auxiliarId;
			}
		}
		if(i == 0)
		{
			auxiliarMaxId = 0;
		}
		*idMaximo = auxiliarMaxId;
		retorno = 0;
	}

	return retorno;
}

/** brief Busca si hay Empleados cargados

 * \param pLinkedList LinkedList*  Listado de todos los empleados
 * \return Retora 1 si hay por lo menos un Empleado, 0 si no hay ninguno o -1 si hay un error
 *
 */
static int buscarEmpleado(LinkedList* pLinkedList)
{
	int retorno = -1;

	if(pLinkedList != NULL)
	{
		retorno = 0;
		for(int i = 0; i < ll_len(pLinkedList); i++)
		{
			retorno = 1;
			break;
		}
	}

	return retorno;
}

/** brief Busca la posición donde los IDs son iguales
 *
 * \param pLinkedList LinkedList* Lista de todos los empleados donde se compararan los IDs
 * \param id int ID que se va a comparar con todos los IDs de los empleados
 * \return Retora la posición donde los IDs son iguales o -1 (ERROR) si no hay IDs iguales
 *
 */
static int buscarPorId(LinkedList* pLinkedList, int id)
{
	int respuesta = -1;
	int flagError;
	Employee* auxiliarEmployee = NULL;

	if(pLinkedList != NULL)
	{
		for(int i = 0; i < ll_len(pLinkedList); i++)
		{
			auxiliarEmployee = ll_get(pLinkedList, i);
			if(employee_getId(auxiliarEmployee, &flagError) == id && !flagError)
			{
				respuesta = i;
				break;
			}
		}
	}

	return respuesta;
}

/** \brief Ordena los empleados por ID
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
static int ordenarPorId(void* elemento1, void* elemento2)
{
	int retorno;
	Employee* pEmployee1 = NULL;
	Employee* pEmployee2 = NULL;
	int id1;
	int id2;
	int flagError;

	pEmployee1 = (Employee*)elemento1;
	pEmployee2 = (Employee*)elemento2;

	if(pEmployee1 != NULL && pEmployee2 != NULL)
	{
		id1 = employee_getId(pEmployee1, &flagError);
		id2 = employee_getId(pEmployee2, &flagError);

		if(id1 < id2)
		{
			retorno = -1;
		}
		else if(id1 > id2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los empleados por nombre
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
static int ordenarPorNombre(void* elemento1, void* elemento2)
{
	int retorno;
	Employee* pEmployee1 = NULL;
	Employee* pEmployee2 = NULL;
	char* nombre1;
	char* nombre2;
	int flagError;

	pEmployee1 = (Employee*)elemento1;
	pEmployee2 = (Employee*)elemento2;

	if(pEmployee1 != NULL && pEmployee2 != NULL)
	{
		nombre1 = employee_getNombre(pEmployee1, &flagError);
		nombre2 = employee_getNombre(pEmployee2, &flagError);

		if(strncmp(nombre1, nombre2, 128) < 0)
		{
			retorno = -1;
		}
		else if(strncmp(nombre1, nombre2, 128) > 0)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los empleados por horas trabajadas
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
static int ordenarPorHorasTrabajadas(void* elemento1, void* elemento2)
{
	int retorno;
	Employee* pEmployee1 = NULL;
	Employee* pEmployee2 = NULL;
	int horasTrabajadas1;
	int horasTrabajadas2;
	int flagError;

	pEmployee1 = (Employee*)elemento1;
	pEmployee2 = (Employee*)elemento2;

	if(pEmployee1 != NULL && pEmployee2 != NULL)
	{
		horasTrabajadas1 = employee_getHorasTrabajadas(pEmployee1, &flagError);
		horasTrabajadas2 = employee_getHorasTrabajadas(pEmployee2, &flagError);

		if(horasTrabajadas1 < horasTrabajadas2)
		{
			retorno = -1;
		}
		else if(horasTrabajadas1 > horasTrabajadas2)
		{
			retorno = 1;
		}
	}

	return retorno;
}

/** \brief Ordena los empleados por sueldo
 *
 * \param pArrayListEmployee LinkedList* Listado de todos los empleados
 * \return int Retora 0 (EXITO) o -1 (ERROR)
 *
 */
static int ordenarPorSueldo(void* elemento1, void* elemento2)
{
	int retorno;
	Employee* pEmployee1 = NULL;
	Employee* pEmployee2 = NULL;
	int sueldo1;
	int sueldo2;
	int flagError;

	pEmployee1 = (Employee*)elemento1;
	pEmployee2 = (Employee*)elemento2;

	if(pEmployee1 != NULL && pEmployee2 != NULL)
	{
		sueldo1 = employee_getSueldo(pEmployee1, &flagError);
		sueldo2 = employee_getSueldo(pEmployee2, &flagError);

		if(sueldo1 < sueldo2)
		{
			retorno = -1;
		}
		else if(sueldo1 > sueldo2)
		{
			retorno = 1;
		}
	}

	return retorno;
}
