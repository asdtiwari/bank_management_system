#include <stdio.h>
#include <conio.h>
#include <string.h>

void maskPassword(char *password) {
    int i = 0;
    char ch;

    while(1) {
        ch = getch(); // Read char without echoing
        if(ch == 13) { // enter key pressed
            password[i] = '\0';
            printf("\n");
            break;
        } else if(ch == 8) { // Backspace
            if(i > 0) {
                --i;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
}

void encryptPassword(char *password) {
    int len = strlen(password);
    for(int i = 0; i < len; ++i) {
        password[i] = password[i] + 1; // simple ceaser cipher shift by 1
    }
}

void printHeader(char *header) {
    int size = strlen(header);
    int extraTimes = size + 4;

    printf("\n ");
    for(int i = 0; i < extraTimes; ++i) {
        printf("_");
    }
    printf("\n|");
    for(int i = 0; i < extraTimes; ++i) {
        printf(" ");
    }
    printf("|");
    printf("\n|  %s  |", header);
    printf("\n|");
    for(int i = 0; i < extraTimes; ++i) {
        printf("_");
    }
    printf("|\n\n");
}

void refreshScreenMessage(char *message) {
    if(strlen(message) > 0) {
        printf("\n\n%s", message);
    }
    printf("\n\nPress ENTER to Continue... ");
    while(getchar() != '\n');
}