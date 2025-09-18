#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "auth.h"
#include "file_handler.h"
#include "utils.h"
#include "admin.h"

#define ADMIN_ACCNO 666666
#define ADMIN_PASSWORD "benjo234"

// Authenticate and return Role
Role authenticate(long int accNo, const char *password) {
    if(accNo == ADMIN_ACCNO && strcmp(password, ADMIN_PASSWORD) == 0) {
        return ROLE_ADMIN;
    }

    Customer customer;
    if(loadCustomerFromFile(accNo, &customer)) {
        if(strcmp(password, customer.password) == 0) {
            return ROLE_CUSTOMER;
        }
    }
    
    return ROLE_INVALID;
}

void loginScreen() {
	system("cls");

    long int accNo;
	char password[20];

	printHeader("Login Screen");
	
	printf("Enter Account Number: ");
	if(scanf("%ld", &accNo) == 0 || accNo < 100000 || accNo > 9999999999) {
		while(getchar() != '\n');
		refreshScreenMessage("Invalid account number.");
		return;
	}
	while(getchar() != '\n');

	printf("Enter Password: ");
	maskPassword(password);
	encryptPassword(password);

	Role userRole = authenticate(accNo, password);

	if(userRole == ROLE_ADMIN) {
		printf("\nLogin Successful as Admin!\n");
		adminMenu();
	} else if(userRole == ROLE_CUSTOMER) {
		printf("\nLogin succesful as Customer!\n");
		customerMenu(accNo);
	} else {
		refreshScreenMessage("Invalid credentails.");
	}
}