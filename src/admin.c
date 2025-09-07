#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "customer.h"
#include "file_handler.h"
#include "utils.h"
#include "transaction.h"

void adminMenu() {

    int choice;
    while(1) { 
        system("cls");

        printf("\n===== Admin Menu =====\n");
        printf("1. Create New Customer\n");
        printf("2. View Customer Details\n");
        printf("3. Update Customer Details\n");
        printf("4. View All Customers\n");
        printf("5. View Bank Stats\n");
        printf("6. Remove Customer\n");
        printf("7. Exit Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1:
                createCustomer();               
                break;

            case 2:
                viewCustomerDetails();
                break;

            case 3:
                modifyCustomer();
                break;

            case 4:
                viewAllCustomer();
                break;

            case 5:
                viewBankStats();
                break;

            case 6:
                deleteCustomer();
                break;

            case 7:
                printf("Exiting Admin Menu...\n");
                return;

            default: 
                printf("Invalid choice. Try again.\n");
        }
    }
}

void createCustomer() {
    system("cls"); // fresh screen

    Customer customer;

    printf("\n==== Create New Customer =====\n");

    printf("Account No: ");
    while(scanf("%d", &customer.accNo) == 0) {
        printf("Enter valid account number");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    printf("Name: ");
    scanf("%[^\n]", customer.name);
    while(getchar() != '\n');

    printf("Password: ");
    maskPassword(customer.password);
    encryptPassword(customer.password);

    printf("Initial Balance: ");
    while(scanf("%lf", &customer.balance) == 0 || customer.balance < 0) {
        printf("Please Enter valid amount");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    printf("Mobile: ");
    scanf("%s", customer.mobile);
    while(getchar() != '\n');

    printf("Email: ");
    scanf("%s", customer.email);
    while(getchar() != '\n');

    if(saveCustomerInFile(&customer)) {
        printf("Customer created successfully!\n");
    } else {
        printf("Failed to create customer.\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

void viewCustomerDetails() {
    system("cls");

    Customer customer;

    printf("\n--- View Customer Details ---\n");
    printf("Enter Account No: ");
    scanf("%d", &customer.accNo);
    while(getchar() != '\n');

    if(loadCustomerFromFile(customer.accNo, &customer)) {
        printf("\n Account No: %d\n Name: %s\n Balance: %.2lf\n Mobile: %s\n Email: %s\n", customer.accNo, customer.name, customer.balance, customer.mobile, customer.email);
    } else {
        printf("Customer not found.\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

void deleteCustomer() {
    system("cls");

    int accNo;
    printf("\n===== Delete Customer =====\n");
    
    printf("Enter Account Number to delete: ");
    while(scanf("%d", &accNo) == 0) {
        printf("Please enter valid account number\n");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    
    deleteCustomerTransaction(accNo);
    
    if(deleteCustomerFromFile(accNo)) {
        printf("\n Customer deleted successfully.\n");
    } else {
        printf("\n Customer not found with Account No: %d\n", accNo);
    }

    printf("\nPress Enter to continue...");
    getchar();
    
}

void modifyCustomer() {
    system("cls");

    Customer customer;
    printf("\n===== Modify Customer =====\n");
    printf("Enter Account Number to modify: ");
    while(scanf("%d", &customer.accNo) == 0) {
        printf("Please enter valid account number\n");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    if(!loadCustomerFromFile(customer.accNo, &customer)) {
        printf("\n Customer not found.\n");
        printf("\nPress Enter to continue...");
        getchar();
        return;
    }

    printf("\nCurrent Name: %s\nEnter New name: ", customer.name);
    scanf("%[^\n]", customer.name);
    while(getchar() != '\n');

    printf("Enter New Password: ");
    maskPassword(customer.password);
    encryptPassword(customer.password);

    printf("\nCurrent Mobile: %s\nEnter New Mobile: ", customer.mobile);
    scanf("%s", customer.mobile);
    while(getchar() != '\n');

    printf("\nCurrent Email: %s\nEnter New Email: ", customer.email); 
    scanf("%s", customer.email);
    while(getchar() != '\n');

    if(modifyCustomerInFile(&customer)) {
        printf("\n Customer details modified successfully!\n");
    } else {
        printf("\n Failed to modify customer.\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

void viewAllCustomer() {
    viewAllCustomersFromFile();
}

void viewBankStats() {
    viewBankStatisticsFromFile();
}