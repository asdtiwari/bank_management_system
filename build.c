#include <stdio.h>
#include <windows.h>

int main() {
	const char *app = "gcc src/main.c src/admin.c src/customer.c src/transaction.c src/utils.c src/encrypt.c src/decrypt.c -Iinclude -o bin/app -Wall -g -mconsole";
	const char *bank_management_system = "gcc src/bank_management_system.c -o bank_management_system -Wall -g -mconsole";

/* 
	-Iinclude means check header inside "include" folder
	-Wall enables warnings
	-g add debugging symbols for gdb / lldb etc.
	-mconsole tells console based mingw project
	2> build_errors.txt means redirect stderr to build_errors.txt file
*/

	printf("Compiling project...\n");

	int result1 = system(app);
	int result2 = system(bank_management_system);

	if(result1 == 0 && result2 == 0) {
		printf("Compilation Successful! Run bank_management_system.exe\n");
	} else {
		printf("Compilation Failed! Check errors above. \n");
	}

	Sleep(3000);

	return 0;
}