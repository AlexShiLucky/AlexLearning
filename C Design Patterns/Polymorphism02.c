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

    if(NULL != pPersonObj)
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
	struct _person *pSuper;
	char *pDepartment;
	char *pCompany;
	int salary;
};

employee_t * new_Employee(const char *pFName, const char *pLName, const char *pDepartment, const char *pCompany, int salary) 	// constructor
{
	employee_t *pEmpObj;
	person_t *pPersonObj;

	pPersonObj = new_Person(pFName, pLName);	// calling base class construtor
	//allocating memory
	pEmpObj = malloc(sizeof(employee_t));
	if (NULL == pEmpObj) {
		pPersonObj->fpDelete(pPersonObj);
		return NULL;
	}
    pEmpObj->pSuper = pPersonObj;

	// initialising derived class members
	pEmpObj->pDepartment = malloc(sizeof(char)*(strlen(pDepartment)+1));
	strcpy(pEmpObj->pDepartment, pDepartment);

	pEmpObj->pCompany = malloc(sizeof(char)*(strlen(pCompany)+1));
	strcpy(pEmpObj->pCompany, pCompany);

	pEmpObj->salary = salary;


	// Changing base class interface to access derived class functions
	pPersonObj->fpDelete = delete_employee;     // Person destructor pointing to destrutor of Employee
	pPersonObj->fpDisplay = employee_displayinfo;
	pPersonObj->fpWriteToFile = employee_writetofile;

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

	// destroy base Obj
	delete_person(pPersonObj);
}

static void employee_displayinfo(void *pObj)
{
    employee_t *pEmpObj = (employee_t *)pObj;
	person_t *pPersonObj = pEmpObj->pSuper;

	// displaying Person info
	person_displayinfo(pPersonObj);

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
	person_writetofile(pPersonObj, pFileName);

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

    PersonObj = EmployeeObj->pSuper;
	// displaying employee info
	PersonObj->fpDisplay(EmployeeObj);
	// writing empolyee info in the employeedata.txt file
	PersonObj->fpWriteToFile(EmployeeObj, "employeedata.txt");
	// calling destrutor
	PersonObj->fpDelete(EmployeeObj);

    return 0;
}
