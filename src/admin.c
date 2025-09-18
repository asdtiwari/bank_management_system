#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "customer.h"
#include "file_handler.h"
#include "utils.h"
#include "transaction.h"

void createCustomer() {
    system("cls"); // fresh screen

    Customer customer;

    printHeader("Create New Customer");

    printf("Account No.: ");
    long int accNo;
    if(scanf("%ld", &accNo) == 0 || accNo < 100000l || accNo > 9999999999l) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid account number. It should be of 6-10 digits.");
    }
    while(getchar() != '\n');
    customer.accNo = accNo;

    Customer isExisting;
    if(loadCustomerFromFile(customer.accNo, &isExisting) != 0) {
        refreshScreenMessage("Account No.already taken.");
        return;
    }

    printf("Name: ");
    scanf("%[^\n]", customer.name);
    while(getchar() != '\n');

    printf("Password: ");
    maskPassword(customer.password);
    encryptPassword(customer.password);

    printf("Initial Balance: ");
    while(scanf("%lf", &customer.balance) == 0 || customer.balance < 0) {
        while(getchar() != '\n');
        printf("Please Enter valid amount: ");
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

    refreshScreenMessage("");
}

void viewCustomerDetails() {
    system("cls");

    Customer customer;

    printHeader("View Customer Details");

    printf("Enter Account No.: ");
    if(scanf("%ld", &customer.accNo) == 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid input.");
        return;
    }
    while(getchar() != '\n');

    if(loadCustomerFromFile(customer.accNo, &customer)) {
        printf("\n%-15s: %ld \n%-15s: %s \n%-15s: %.2lf \n%-15s: %s \n%-15s: %s \n", "Account No.", customer.accNo, "Name", customer.name, "Balance", customer.balance, "Mobile", customer.mobile, "Email", customer.email);
    } else {
        printf("Customer not found.\n");
    }

    refreshScreenMessage("");
}

void modifyCustomer() {
    system("cls");

    Customer customer;
    printHeader("Modify Customer");

    printf("Enter Account Number to modify: ");
    if(scanf("%ld", &customer.accNo) == 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid Acc No.");
        return;
    }
    while(getchar() != '\n');

    if(!loadCustomerFromFile(customer.accNo, &customer)) {
        refreshScreenMessage("Customer not found.");
        return;
    }

    printf("\nCurrent Name: %s\nEnter New name: ", customer.name);
    scanf("%[^\n]", customer.name);
    while(getchar() != '\n');

    printf("\nEnter New Password: ");
    maskPassword(customer.password);
    encryptPassword(customer.password);

    printf("\nCurrent Mobile: %s\nEnter New Mobile: ", customer.mobile);
    scanf("%s", customer.mobile);
    while(getchar() != '\n');

    printf("\nCurrent Email: %s\nEnter New Email: ", customer.email); 
    scanf("%s", customer.email);
    while(getchar() != '\n');

    if(modifyCustomerInFile(&customer)) {
        printf("\nCustomer details modified successfully!\n");
    } else {
        printf("\nFailed to modify customer.\n");
    }

    refreshScreenMessage("");
}

void deleteCustomer() {
    system("cls");

    long int accNo;
    printHeader("Delete Customer");
    
    printf("Enter Account Number to delete: ");
    if(scanf("%ld", &accNo) == 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid Acc No.");
        return;
    }
    while(getchar() != '\n');
    
    deleteCustomerTransaction(accNo);
    
    if(deleteCustomerFromFile(accNo)) {
        printf("\nCustomer deleted successfully.\n");
    } else {
        printf("\nCustomer not found with Account No: %ld\n", accNo);
    }

    refreshScreenMessage("");
}

void moneyTransfer() {
    system("cls");

    long int fromAcc;
    Customer sender;

    printHeader("Money Transfer");

    printf("Enter Sender Account No.: ");
    if(scanf("%ld", &fromAcc) == 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid Account No.");
        return;
    }
    while(getchar() != '\n');

    if(loadCustomerFromFile(fromAcc, &sender) == 0) {
        refreshScreenMessage("Account doesn't exists.");
        return;
    }

    transfer(&sender);
}

void viewCustomerTransaction() {
    system("cls");

    printHeader("View All Transaction");

    long int accNo;
    printf("\nEnter Customer account No.: ");
    if(scanf("%ld", &accNo) == 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid account No.");
        return;
    }
    while(getchar() != '\n');

    Customer customer;
    if(loadCustomerFromFile(accNo, &customer) == 0) {
        refreshScreenMessage("Account doesn't exists.");
        return;
    }

    viewTransactions(accNo);
}

void adminMenu() {

    int choice;
    while(1) { 
        system("cls");

        printHeader("Admin Menu");

        printf("1. Create New Customer\n");
        printf("2. View Customer Details\n");
        printf("3. Update Customer Details\n");
        printf("4. View All Customers\n");
        printf("5. View Bank Stats\n");
        printf("6. Remove Customer\n");
        printf("7. Money Transfer\n");
        printf("8. View Customer Transaction\n");
        printf("9. View All Transactions\n");
        printf("10. Exit Admin Menu\n");
        printf("\nEnter your choice: ");
        if(scanf("%d", &choice) == 0) {
            while(getchar() != '\n');
            refreshScreenMessage("Invalid input.");
            continue;
        }
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
                viewAllCustomersFromFile();
                break;

            case 5:
                viewBankStatisticsFromFile();
                break;

            case 6:
                deleteCustomer();
                break;

            case 7: 
                moneyTransfer();
                break;

            case 8:
                viewCustomerTransaction();
                break;

            case 9:
                viewAllTransactions();
                break;

            case 10:
                refreshScreenMessage("Exiting Admin Menu.");
                return;

            default: 
                refreshScreenMessage("Invalid choice.");
        }
    }
}