#include <stdio.h>
#include <stdlib.h>

typedef struct _person person_t;
typedef struct _employee employee_t;

static void delete_person(void *pObj);
static void person_displayinfo(void *pObj);
static void person_writetofile(void *pObj, const char *pFileName);

static void delete_employee(void *pObj);
static void employee_displayinfo(void *pObj);
static void employee_writetofile(void *pObj, const char *pFileName);

struct _person {
    char *pFirstName;
    char *pLastName;

    // interface to access member functions
    void (*fpDisplay)(void *);
    void (*fpWriteToFile)(void *, const char *);
    void (*fpDelete)(void *);
};

person_t * new_Person(const char *pFName, const char *pLName) 	// constructor
{
	person_t *pObj = NULL;

	// allocating memory
	pObj = (person_t *)malloc(sizeof(person_t));
	if (pObj == NULL) return NULL;

	pObj->pFirstName = malloc(sizeof(char)*(strlen(pFName)+1));
	strcpy(pObj->pFirstName, pFName);

	pObj->pLastName = malloc(sizeof(char)*(strlen(pLName)+1));
	strcpy(pObj->pLastName, pLName);

	// Initializing interface for access to functions
	pObj->fpDelete = delete_person;			// destructor pointing to destrutor of itself
	pObj->fpDisplay = person_displayinfo;
	pObj->fpWriteToFile = person_writetofile;

	return pObj;
}

static void delete_person(void *pObj)          // destructor
{
    person_t *pPersonObj = (person_t *)pObj;

    if (NULL != pPersonObj)
	{
		free(pPersonObj->pFirstName);
		free(pPersonObj->pLastName);
		free(pPersonObj);
	}
}

static void person_displayinfo(void *pObj)
{
    person_t *pPersonObj = (person_t *)pObj;

	printf("FirstName: %s\n", pPersonObj->pFirstName);
	printf("LastName: %s\n", pPersonObj->pLastName);
}

static void person_writetofile(void *pObj, const char *pFileName)
{
    person_t *pPersonObj = (person_t *)pObj;

	// code for writing Person information to file
    printf("Write person's information to file: %s\n", pFileName);
}

// Note: interface for this class is in the base class object since all functions are virtual.
// If there are any additional functions in Employee add interface for those functions in this class
struct _employee {
    struct _person base;
	struct _person *pSuper;
	char *pDepartment;
	char *pCompany;
	int salary;
};

employee_t * new_Employee(const char *pFName, const char *pLName, const char *pDepartment, const char *pCompany, int salary) 	// constructor
{
	employee_t *pEmpObj;
	person_t *pPersonObj;

	pPersonObj = new_Person(pFName, pLName);	    // calling base class construtor
	//allocating memory
	pEmpObj = malloc(sizeof(employee_t));
	if (NULL == pEmpObj) {
		pPersonObj->fpDelete(pPersonObj);
		return NULL;
	}
    pEmpObj->pSuper = pPersonObj;
    pEmpObj->base   =*pPersonObj;
    // Changing base class interface to access derived class functions
	pEmpObj->base.fpDelete = delete_employee;       // Person destructor pointing to destrutor of Employee
	pEmpObj->base.fpDisplay = employee_displayinfo;
	pEmpObj->base.fpWriteToFile = employee_writetofile;

	// initialising derived class members
	pEmpObj->pDepartment = malloc(sizeof(char)*(strlen(pDepartment)+1));
	strcpy(pEmpObj->pDepartment, pDepartment);

	pEmpObj->pCompany = malloc(sizeof(char)*(strlen(pCompany)+1));
	strcpy(pEmpObj->pCompany, pCompany);

	pEmpObj->salary = salary;

	return pEmpObj;
}

static void delete_employee(void *pObj) 	// destructor
{
    employee_t *pEmpObj = (employee_t *)pObj;
	person_t *pPersonObj = pEmpObj->pSuper;

	// destroy derived obj
	free(pEmpObj->pCompany);
	free(pEmpObj->pDepartment);
	free(pEmpObj);

	// destroy super Obj
	pPersonObj->fpDelete(pPersonObj);
}

static void employee_displayinfo(void *pObj)
{
    employee_t *pEmpObj = (employee_t *)pObj;
	person_t *pPersonObj = pEmpObj->pSuper;

	// displaying Person info
	pPersonObj->fpDisplay(pPersonObj);

	// displaying Employee specific info
	printf("Department: %s\n", pEmpObj->pDepartment);
	printf("Company: %s\n", pEmpObj->pCompany);
	printf("salary: %d\n", pEmpObj->salary);
}

static void employee_writetofile(void *pObj, const char *pFileName)
{
	employee_t *pEmpObj = (employee_t *)pObj;
	person_t *pPersonObj = pEmpObj->pSuper;

	// writing Person information
	pPersonObj->fpWriteToFile(pPersonObj, pFileName);

	// code to write Employee specific info
    printf("Write employee's specific information to file: %s\n", pFileName);
}

int main (int argc, char * argv[], char * envp[])
{
	person_t *PersonObj = new_Person("Anjali", "Jaiswal");
	employee_t *EmployeeObj = new_Employee("Gauri", "Jaiswal","HR", "TCS", 40000);

	// accessing Person object

	// displaying Person info
	PersonObj->fpDisplay(PersonObj);
	// writing Person info in the persondata.txt file
	PersonObj->fpWriteToFile(PersonObj, "persondata.txt");
	// calling destructor
	PersonObj->fpDelete(PersonObj);

	// accessing to employee object

	// displaying employee info
	((person_t *)EmployeeObj)->fpDisplay(EmployeeObj);
	// writing empolyee info in the employeedata.txt file
	((person_t *)EmployeeObj)->fpWriteToFile(EmployeeObj, "employeedata.txt");
	// calling destrutor
	((person_t *)EmployeeObj)->fpDelete(EmployeeObj);

    return 0;
}
