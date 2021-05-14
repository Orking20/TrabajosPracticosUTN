/*
 ============================================================================
 Name        : TrabajoPractico2.c
 Author      : Mateo Luchetti Capalbo
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Employee.h"
#include "Reports.h"
#define QTY_EMPLOYEE 100

int main(void)
{
	int menuOption;
	Employee arrayEmployee[QTY_EMPLOYEE];

	initEmployees(arrayEmployee, QTY_EMPLOYEE);

	do
	{
		utn_getNumero(&menuOption,  "\n\n1) Create\n"
									"2) Update\n"
									"3) Delete\n"
									"4) Reports\n"
									"0) Exit\n",
									"\nError. Choose one of the options of the menu writing the correspond number", 0, 4, 3);

		switch(menuOption)
		{
			case 1:
			{
				addEmployees(arrayEmployee, findEmployeeIndexEmpty(arrayEmployee, QTY_EMPLOYEE));
				break;
			}
			case 2:
			{
				updateEmployees(arrayEmployee, QTY_EMPLOYEE);
				break;
			}
			case 3:
			{
				removeEmployee(arrayEmployee, QTY_EMPLOYEE);
				break;
			}
			case 4:
			{
				report(arrayEmployee, QTY_EMPLOYEE);
				break;
			}
		}
	}while(menuOption != 0);

	return EXIT_SUCCESS;
}
