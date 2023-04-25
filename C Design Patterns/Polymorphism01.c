#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct _person person_t;
typedef struct _employee employee_t;

static void delete_person(person_t * const pPersonObj);
static void person_displayinfo(person_t * const pPersonObj);
static void person_writetofile(person_t * const pPersonObj, const char *pFileName);

static void delete_employee(person_t * const pPersonObj);
static void employee_displayinfo(person_t * const pPersonObj);
static void employee_writetofile(person_t * const pPersonObj, const char *pFileName);

struct _person {
    void *pDerivedObj;
    char *pFirstName;
    char *pLastName;

    // interface to access member functions
    void (*fpDisplay)(struct _person *);
    void (*fpWriteToFile)(struct _person *, const char *);
    void (*fpDelete)(struct _person *);
};

person_t * new_Person(const char *pFName, const char *pLName) 	// constructor
{
	person_t *pObj = NULL;

	// allocating memory
	pObj = (person_t *)malloc(sizeof(person_t));
	if (pObj == NULL) return NULL;
	pObj->pDerivedObj = pObj;               // pointing to itself

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

static void delete_person(person_t * const pPersonObj)          // destructor
{
    if(NULL != pPersonObj)
	{
		free(pPersonObj->pFirstName);
		free(pPersonObj->pLastName);
		free(pPersonObj);
	}
}

static void person_displayinfo(person_t * const pPersonObj)
{
	printf("FirstName: %s\n", pPersonObj->pFirstName);
	printf("LastName: %s\n", pPersonObj->pLastName);
}

static void person_writetofile(person_t * const pPersonObj, const char *pFileName)
{
	// code for writing Person information to file
    printf("Write person's information to file: %s\n", pFileName);
}

// Note: interface for this class is in the base class object since all functions are virtual.
// If there are any additional functions in Employee add interface for those functions in this class
struct _employee {
	struct _person *pBaseObj;
	char *pDepartment;
	char *pCompany;
	int salary;
};

person_t * new_Employee(const char *pFName, const char *pLName, const char *pDepartment, const char *pCompany, int salary) 	// constructor
{
	employee_t *pEmpObj;
	person_t *pObj;

	pObj = new_Person(pFName, pLName);	// calling base class construtor
	//allocating memory
	pEmpObj = malloc(sizeof(employee_t));
	if (NULL == pEmpObj) {
		pObj->fpDelete(pObj);
		return NULL;
	}
	pObj->pDerivedObj = pEmpObj;        // pointing to derived object

	// initialising derived class members
	pEmpObj->pDepartment = malloc(sizeof(char)*(strlen(pDepartment)+1));
	strcpy(pEmpObj->pDepartment, pDepartment);

	pEmpObj->pCompany = malloc(sizeof(char)*(strlen(pCompany)+1));
	strcpy(pEmpObj->pCompany, pCompany);

	pEmpObj->salary = salary;


	// Changing base class interface to access derived class functions
	pObj->fpDelete = delete_employee;     // Person destructor pointing to destrutor of Employee
	pObj->fpDisplay = employee_displayinfo;
	pObj->fpWriteToFile = employee_writetofile;

	return pObj;
}

static void delete_employee(person_t * const pPersonObj) 	// destructor
{
	employee_t *pEmpobj;

	pEmpobj = pPersonObj->pDerivedObj;

	// destroy derived obj
	free(pEmpobj->pCompany);
	free(pEmpobj->pDepartment);
	free(pEmpobj);

	// destroy base Obj
	//pPersonObj->fpDelete(pPersonObj);
    delete_person(pPersonObj);
}

static void employee_displayinfo(person_t * const pPersonObj)
{
	employee_t *pEmpObj;

	// displaying Person info
	//pPersonObj->fpDisplay(pPersonObj);
    person_displayinfo(pPersonObj);
	pEmpObj = pPersonObj->pDerivedObj;

	// displaying Employee specific info
	printf("Department: %s\n", pEmpObj->pDepartment);
	printf("Company: %s\n", pEmpObj->pCompany);
	printf("salary: %d\n", pEmpObj->salary);
}

static void employee_writetofile(person_t * const pPersonObj, const char *pFileName)
{
	// writing Person information
	//pPersonObj->fpWriteToFile(pPersonObj, pFileName);
    person_writetofile(pPersonObj, pFileName);

	// code to write Employee specific info
    printf("Write employee's specific information to file: %s\n", pFileName);
}

int main (int argc, char * argv[], char * envp[])
{
	person_t *PersonObj = new_Person("Anjali", "Jaiswal");
	person_t *EmployeeObj = new_Employee("Gauri", "Jaiswal","HR", "TCS", 40000);

	// accessing Person object

	// displaying Person info
	PersonObj->fpDisplay(PersonObj);
	// writing Person info in the persondata.txt file
	PersonObj->fpWriteToFile(PersonObj, "persondata.txt");
	// calling destructor
	PersonObj->fpDelete(PersonObj);

	// accessing to employee object

	// displaying employee info
	EmployeeObj->fpDisplay(EmployeeObj);
	// writing empolyee info in the employeedata.txt file
	EmployeeObj->fpWriteToFile(EmployeeObj, "employeedata.txt");
	// calling destrutor
	EmployeeObj->fpDelete(EmployeeObj);

    return 0;
}
