#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
int employee_delete(Employee* this);

void setearValorMaximoId(int id);
int generarId(void);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this, int* flagError);

int employee_setNombre(Employee* this,char* nombre);
char* employee_getNombre(Employee* this, int* flagError);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this, int *flagError);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this, int* flagError);

int isValidId(int id);
int isValidNombre(char* nombre);
int isValidHorasTrabajadas(int horasTrabajadas);
int isValidSueldo(int sueldo);

#endif // employee_H_INCLUDED
