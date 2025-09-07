#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "auth.h"
#include "role.h"
#include "admin.h"
#include "customer.h"
#include "utils.h"

int main() {
	int accNo;
	char password[20];

	int failLogin = 0;
	while(1) {
		system("cls");
		if(failLogin) {
			printf("!!! Re-try login attempt failed !!!\n");
		}
		failLogin = 0;
		printf("==== Welcome to Bank Management =====\n");
		printf("Enter Account Number: ");
		scanf("%d", &accNo);
		while(getchar() != '\n');

		printf("Enter Password: ");
		maskPassword(password);
		encryptPassword(password);

		Role userRole = authenticate(accNo, password);

		if(userRole == ROLE_ADMIN) {
			printf("\n Login Successful as Admin!\n");
			adminMenu();
		} else if(userRole == ROLE_CUSTOMER) {
			printf("\n Login succesful as Customer!\n");
			customerMenu(accNo);
		} else {
			printf("\n Invalid credentails. Try again.\n");
			failLogin = 1;
			Sleep(2000);
		}
	}
	getchar();

	return 0;
}