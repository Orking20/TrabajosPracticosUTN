/*
 * Employee.h
 *
 *  Created on: 28 abr. 2021
 *      Author: mateo
 */

#ifndef employee_H_
#define employee_H_
#define TAM_NAME 51
#define TAM_LAST_NAME 51

typedef struct
{
	int id;
	char name[TAM_NAME];
	char lastName[TAM_LAST_NAME];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int initEmployees(Employee* pEmployee, int length);
int addEmployees(Employee* pEmployee, int index);
int updateEmployees(Employee* pEmployee, int length);
int removeEmployee(Employee* pEmployee, int length);

int printEmployees(Employee* pEmployee, int length);
int showEmployeesWithId(Employee* pEmployee, int length);
int findEmployeeIndexEmpty(Employee* pEmployee, int length);
int findEmployeeById(Employee* pEmployee, int length, int id);
int findEmployee(Employee* pEmployee, int length);

#endif /* employee_H_ */
