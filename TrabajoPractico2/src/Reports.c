/*
 * Informes.c
 *
 *  Created on: 14 may. 2021
 *      Author: mateo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"
#include "Reports.h"

static int sortEmployeesByLastName(Employee* pEmployee, int length, int* order);
static int sortEmployeesBySector(Employee* pEmployee, int length, int* order);
static int salaryInfo(Employee* pEmployee, int length);

/*
 * brief Show all the information of the employees
 * \param Employee* pEmployee: Array where contains the values of the employees
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) or -1 (ERROR)*/
int report(Employee* pEmployee, int length)
{
	int retorno = -1;
	int order;

	if(pEmployee != NULL && length > 0)
	{
		if(findEmployee(pEmployee, length) == 1)
		{
			utn_getNumero(&order, "\nDo you want to sort them in ascending [1] or descending [0] order? ", "\nError. You can only put 1 or 0", 0, 1, 3);
			sortEmployeesByLastName(pEmployee, length, &order);
			sortEmployeesBySector(pEmployee, length, &order);
			salaryInfo(pEmployee, length);
		}
		else
		{
			printf("\nError. There is not employees yet. First you have to add one.");
		}
	}

	return retorno;
}

/**
 * brief Sort all the employees by last name alphabetically
 * \param Employee* pEmployee: Array where contains the values to sort
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) if it could to sort the values or -1 (ERROR) if not*/
static int sortEmployeesByLastName(Employee* pEmployee, int length, int* order)
{
	int answer = -1;
	int flagSwap = 0;
	Employee auxiliar;

	if(pEmployee != NULL && length > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < length - 1; i++)
			{
				switch(*order)
				{
					case 0:
					{
						if(strcmp(pEmployee[i].lastName, pEmployee[i + 1].lastName) < 0)
						{
							auxiliar = pEmployee[i];
							pEmployee[i] = pEmployee[i + 1];
							pEmployee[i + 1] = auxiliar;
							flagSwap = 1;
						}
						break;
					}
					case 1:
					{
						if(strcmp(pEmployee[i].lastName, pEmployee[i + 1].lastName) > 0)
						{
							auxiliar = pEmployee[i];
							pEmployee[i] = pEmployee[i + 1];
							pEmployee[i + 1] = auxiliar;
							flagSwap = 1;
						}
						break;
					}
				}
			}
		}while(flagSwap);

		printf("\n\n\nLIST BY NAMES:\n");
		printEmployees(pEmployee, length);
		answer = 0;
	}

	return answer;
}

/**
 * brief Sort all the employees by sector
 * \param Employee* pEmployee: Array where contains the values to sort
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) if it could to sort the values or -1 (ERROR) if not*/
static int sortEmployeesBySector(Employee* pEmployee, int length, int* order)
{
	int answer = -1;
	int flagSwap = 0;
	Employee auxiliar;

	if(pEmployee != NULL && length > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < length - 1; i++)
			{
				switch(*order)
				{
					case 0:
					{
						if(pEmployee[i].sector < pEmployee[i + 1].sector)
						{
							auxiliar = pEmployee[i];
							pEmployee[i] = pEmployee[i + 1];
							pEmployee[i + 1] = auxiliar;
							flagSwap = 1;
						}
						break;
					}
					case 1:
					{
						if(pEmployee[i].sector > pEmployee[i + 1].sector)
						{
							auxiliar = pEmployee[i];
							pEmployee[i] = pEmployee[i + 1];
							pEmployee[i + 1] = auxiliar;
							flagSwap = 1;
						}
						break;
					}
				}
			}
		}while(flagSwap);

		printf("\n\n\nLIST BY SECTOR:\n");
		printEmployees(pEmployee, length);
		answer = 0;
	}

	return answer;
}

/**
 * brief Show the total of salary, the average salary and the quantity of employees that exceed the salary
 * \param Employee* pEmployee: Array where contains the values of all employees
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) if it could show all the information or -1 (ERROR) if not*/
static int salaryInfo(Employee* pEmployee, int length)
{
	int retorno = 0;
	float totalSalary = 0;
	int counter = 0;
	float average;
	int exceedAverage = 0;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i++)
		{
			if(!pEmployee[i].isEmpty)
			{
				totalSalary += pEmployee[i].salary;
				counter++;
			}
		}

		average = totalSalary / counter;

		for(int i = 0; i < length; i++)
		{
			if(pEmployee[i].salary > average)
			{
				exceedAverage++;
			}
		}

		printf("\n\n\nTotal salary: %.2f\nAverage salary: %.2f\nEmployees that exceed the average salary: %d", totalSalary, average, exceedAverage);
		retorno = 0;
	}

	return retorno;
}
