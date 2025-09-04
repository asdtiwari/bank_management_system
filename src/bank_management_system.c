#include <windows.h>
#include <stdio.h>

int main() {
/* 
	/C means exit on program end
	/K means console remain open
*/
	system("start /MAX cmd /C bin\\app.exe");
	Sleep(5000);

	return 0;
}