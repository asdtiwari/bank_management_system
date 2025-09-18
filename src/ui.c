#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "auth.h"
#include "admin.h"
#include "customer.h"
#include "utils.h"

void showManual() {
    system("cls");
    
    printHeader("How to use");

    printf("1) Select Login --> Enter Account No. & Password\n");
    printf("2) Admin: Manage customers, Transfer, History\n");
    printf("3) Customer: Deposit, Withdraw, Transfer, History\n");
    
    refreshScreenMessage("");
}

void showAbout() {
    system("cls");

    printHeader("About");

    printf("%-10s : %s\n", "Title", "Bank Management System in C");
    printf("%-10s : %s\n", "Author", "Akhilesh Tiwari");
    printf("%-10s : %s\n", "Feature", "Role-based auth, File-based persistence, Transaction logs");
    printf("%-10s : %s\n", "Scope", "Academic demo with pro-level C techniques");

    refreshScreenMessage("");
}

void showHomePage() {
    int choice;
    
    while(1) {
        system("cls");

        printHeader("Welcome to Bank Management System");

        printf("1. Login\n");
        printf("2. How to use\n");
        printf("3. About\n");
        printf("4. Exit\n");
        printf("\nChoose option: ");
        while(scanf("%d", &choice) == 0) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number: ");
        }
        while(getchar() != '\n');

        switch(choice) {
            case 1: loginScreen(); break;
            case 2: showManual(); break;
            case 3: showAbout(); break;
            case 4: 
                refreshScreenMessage("Exiting from the Application.");
                return;
            default:
                refreshScreenMessage("Invalid Choice.");
        }
    }
}