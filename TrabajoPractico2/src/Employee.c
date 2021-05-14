/*
 * Employee.c
 *
 *  Created on: 28 abr. 2021
 *      Author: mateo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Employee.h"

/**
 * brief Initialize the value of all the employees to empty values
 * \param Employee* pEmployee: Array that contains all the employees and will be objective of the function
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) if it could initialize the values or -1 (ERROR) if not*/
int initEmployees(Employee* pEmployee, int length)
{
	int answer = -1;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i++)
		{
			pEmployee[i].id = 0;
			strncpy(pEmployee[i].name, "", sizeof(pEmployee[i].name));
			strncpy(pEmployee[i].lastName, "", sizeof(pEmployee[i].lastName));
			pEmployee[i].salary = 0.0;
			pEmployee[i].sector = 0;
			pEmployee[i].isEmpty = 1;
		}
		answer = 0;
	}

	return answer;
}

/**
 * brief Ask the user to add the data of one employee
 * \param Employee* pEmployee: Array where there save the values
 * \param int index: Position where there will be saved the data
 * \return 0 (SUCCES) if it could to add the values or -1 (ERROR) if not*/
int addEmployees(Employee* pEmployee, int index)
{
	int answer = -1;
	Employee bufferEmployee;

	if(pEmployee != NULL && index >= 0)
	{
		if(!utn_getNombre(bufferEmployee.name, "\nPlease enter the name: ", "Error. That name is invalid\n") &&
		   !utn_getNombre(bufferEmployee.lastName, "Please enter the last name: ", "Error. That last name is invalid\n") &&
		   !utn_getPrecio(&bufferEmployee.salary, "Please enter the salary: ", "Error. That salary is invalid\n") &&
		   !utn_getNumero(&bufferEmployee.sector, "Please enter the sector: ", "Error. That sector is invalid\n", 1, 3, 2))
		{
			bufferEmployee.id = index + 1;
			bufferEmployee.isEmpty = 0;
			pEmployee[index] = bufferEmployee;
			answer = 0;
		}
		else
		{
			printf("\nYou entered a invalid data.");
		}
	}

	return answer;
}

/**
 * brief Ask the user to modified the data selected of one employee
 * \param Employee* pEmployee: Array where there save the values
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) if it could to modified the value or -1 (ERROR) if not*/
int updateEmployees(Employee* pEmployee, int length)
{
	int answer = -1;
	Employee bufferEmployee;
	int idEmployee;
	int updateOption;

	if(pEmployee != NULL && length > 0)
	{
		if(findEmployee(pEmployee, length) == 1)
		{
			showEmployeesWithId(pEmployee, length);
			if(!utn_getNumero(&idEmployee, "\nPlease enter the ID of the Employee to modified\n", "\nError. That ID not exist\n", 1, length, 3))
			{
				for(int i = 0; i < length; i++)
				{
					if(idEmployee == pEmployee[i].id)
					{
						utn_getNumero(&updateOption, "What do you want to modified? (1. Name - 2. Last name - 3. Salary - 4. Sector - 0. Cancel): ", "\nError. You have to choose the option do you want with the correspond number (1. Name - 2. Last name - 3. Salary - 4. Sector - 0. Cancel)", 0, 4, 3);
						switch(updateOption)
						{
							case 1:
							{
								utn_getNombre(bufferEmployee.name, "\nPlease enter the new name: ", "Error. That name is invalid\n");
								strncpy(pEmployee[i].name, bufferEmployee.name, sizeof(pEmployee[i].name));
								break;
							}
							case 2:
							{
								utn_getNombre(bufferEmployee.lastName, "\nPlease enter the new last name: ", "Error. That last name is invalid\n");
								strncpy(pEmployee[i].lastName, bufferEmployee.lastName, sizeof(pEmployee[i].lastName));
								break;
							}
							case 3:
							{
								utn_getPrecio(&bufferEmployee.salary, "Please enter the new salary: ", "Error. That salary is invalid\n");
								pEmployee[i].salary = bufferEmployee.salary;
								break;
							}
							case 4:
							{
								utn_getNumero(&bufferEmployee.sector, "Please enter the new sector: ", "Error. That sector is invalid\n", 1, 3, 2);
								pEmployee[i].sector = bufferEmployee.sector;
								break;
							}
							default:
							{
								printf("\nNo data has been saved");
								break;
							}
						}
						answer = 0;
					}
				}
			}
			if(answer == -1)
			{
				printf("\nThat ID is not exist.");
			}
		}
		else
		{
			printf("\nError. There is not employees yet. First you have to add one.");
		}
	}

	return answer;
}

/**
 * brief Ask the user to remove the data of one employee by the ID
 * \param Employee* pEmployee: Array where contains the values and will be remove one employee
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) if it could to remove the values or -1 (ERROR) if not*/
int removeEmployee(Employee* pEmployee, int length)
{
	int answer = -1;
	int idEmployee;

	if(pEmployee != NULL && length > 0)
	{
		if(findEmployee(pEmployee, length) == 1)
		{
			showEmployeesWithId(pEmployee, length);
			if(!utn_getNumero(&idEmployee, "\nPlease enter the ID of the employee to remove\n", "\nError. That Id is not exist\n", 1, length, 3))
			{
				for(int i = 0; i < length; i++)
				{
					if(idEmployee == pEmployee[i].id)
					{
						pEmployee[i].id = 0;
						strncpy(pEmployee[i].name, "", sizeof(pEmployee[i].name));
						strncpy(pEmployee[i].lastName, "", sizeof(pEmployee[i].lastName));
						pEmployee[i].salary = 0.0;
						pEmployee[i].sector = 0;
						pEmployee[i].isEmpty = 1;
					}
				}
			}
		}
		else
		{
			printf("\nError. There is not employees yet. First you have to add one.");
		}
	}

	return answer;
}

/**
 * brief Show all the data of the employees except the ID
 * \param Employee* pEmployee: Array that contains all the employees and will be objective of the function
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) or -1 (ERROR)*/
int printEmployees(Employee* pEmployee, int length)
{
	int answer = -1;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i++)
		{
			if(!pEmployee[i].isEmpty)
			{
				printf("Name: %-15s Last name: %-20s Salary: %-10.2f Sector: %-10d\n", pEmployee[i].name, pEmployee[i].lastName, pEmployee[i].salary, pEmployee[i].sector);
			}
		}
		answer = 0;
	}

	return answer;
}

/**
 * brief Show all the data of the employees including the ID
 * \param Employee* pEmployee: Array that contains all the employees and will be objective of the function
 * \param int length: Length of the array pEmployee
 * \return 0 (SUCCESS) or -1 (ERROR)*/
int showEmployeesWithId(Employee* pEmployee, int length)
{
	int answer = -1;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i++)
		{
			if(!pEmployee[i].isEmpty)
			{
				printf("ID: %-10d Name: %-15s Last name: %-20s Salary: %-10.2f Sector: %-10d\n", pEmployee[i].id, pEmployee[i].name, pEmployee[i].lastName, pEmployee[i].salary, pEmployee[i].sector);
			}
		}
		answer = 0;
	}

	return answer;
}

/**
 * brief Search inside of pEmployee a empty position
 * \param Employee* pEmployee: Array that contains all the employees and will be objective of the function
 * \param int length: Length of the array pEmployee
 * \return the position closer at 0 that is empty or -1 if is not positions emptys or have a error*/
int findEmployeeIndexEmpty(Employee* pEmployee, int length)
{
	int answer = -1;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i++)
		{
			if(pEmployee[i].isEmpty)
			{
				answer = i;
				break;
			}
		}
	}

	return answer;
}

/**
 * brief Search the position where the struct Employee and other struct have the same ID
 * \param Employee* pEmployee: Array that contains all the employees and will be objective of the function
 * \param int length: Length of the array pEmployee
 * \param int id: ID that will be compared with the ID of another struct
 * \return the position where the IDs be equals or -1 in case of error*/
int findEmployeeById(Employee* pEmployee, int length, int id)
{
	int answer = -1;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i++)
		{
			if(pEmployee[i].id == id)
			{
				answer = i;
				break;
			}
		}
	}

	return answer;
}

/**
 * brief Search inside of pEmployee if there are for least one data charged
 * \param Employee* pEmployee: Array that contains all the employees and will be objective of the function
 * \param int length: Length of the array pEmployee
 * \return 1 if there are at least one employee, 0 if there is none or -1 in case of error*/
int findEmployee(Employee* pEmployee, int length)
{
	int answer = -1;

	if(pEmployee != NULL && length > 0)
	{
		for(int i = 0; i < length; i ++)
		{
			if(!pEmployee[i].isEmpty)
			{
				answer = 1;
				break;
			}
			answer = 0;
		}
	}

	return answer;
}
