#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "file_handler.h"
#include "transaction.h"

void customerMenu(int accNo) {
    int choice;
    Customer customer;

    if(!loadCustomerFromFile(accNo, &customer)) {
        printf("Customer not found");
        return;
    }

    while(1) {
        system("cls"); // Fresh screen every time

        printf("\n===== Customer Menu =====\n");
        printf("1. View Balance\n");
        printf("2. Deposit Amount\n");
        printf("3. Withdraw Amount\n");
        printf("4. Money Transfer to A/C\n");
        printf("5. View Transaction History\n");
        printf("6. Exit Cusomter Menu\n");
        printf("Enter your choice: ");
        while(scanf("%d", &choice) == 0) {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');

        switch(choice) {
            case 1:
                viewBalance(&customer);
                break;

            case 2:
                deposit(&customer);
                break;

            case 3:
                withdraw(&customer);
                break;

            case 4:
                transfer(&customer);
                break;
            
            case 5:
                viewTransactions(accNo);
                break;

            case 6:
                printf("Exiting Customer Menu...\n");
                return;
            
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void viewBalance(Customer *customer) {
    system("cls");
    
    printf("\n Current Balance: %.2lf\n", customer->balance);

    printf("\nPress Enter to continue...");
    getchar();    
}

void deposit(Customer *customer) {
    system("cls");

    double amount; 
    time_t now;
    char datetime[20];
    Transaction txn;

    printf("\n Enter amount to deposit: ");
    if(scanf("%lf", &amount) == 0 || amount <= 0) {
        printf("Invalid amount!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    customer->balance += amount;
    updateCustomerInFile(customer);

    time(&now);
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    strcpy(txn.timestamp, datetime);
    txn.accNo = customer->accNo;
    strcpy(txn.type, "DEPOSIT");
    txn.amount = amount;

    logTransaction(&txn);

    printf("Amount deposited Successfully\n");

    printf("\nPress Enter to continue...");
    getchar();
}

void withdraw(Customer *customer) {
    system("cls");

    double amount; 
    time_t now;
    char datetime[20];
    Transaction txn;

    printf("\n Enter amout to withdraw: ");
    if(scanf("%lf", &amount) == 0 || amount <= 0) {
        printf("Invalid amount!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');
    
    if(customer->balance >= amount) {
        customer->balance -= amount;
        updateCustomerInFile(customer);

        time(&now);
        strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));

        strcpy(txn.timestamp, datetime);
        txn.accNo = customer->accNo;
        strcpy(txn.type, "WITHDRAW");
        txn.amount = amount;

        logTransaction(&txn);

        printf("Amount withdrawn successfully!\n");
    } else {
        printf("Insufficient balance!\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

void transfer(Customer *sender) {
    system("cls");

    int toAccount;
    printf("\nEnter Account Number to transfer: ");
    while(scanf("%d", &toAccount) == 0) {
        printf("Enter valid account number\n");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    double amount;
    printf("\nEnter amount to transfer: ");
    while(scanf("%lf", &amount) == 0) {
        printf("Enter correct amount\n");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    Customer receiver;

    if(!loadCustomerFromFile(toAccount, &receiver)) {
        printf("\n Reciever account not found.\n");
        
        printf("\nPress Enter to continue...");
        getchar();
        
        return;
    }

    if(sender->balance < amount) {
        printf("\nInsufficient balance for transfer!");

        printf("\nPress Enter to continue...");
        getchar();
        
        return;
    }

    sender->balance -= amount;
    receiver.balance += amount;

    updateCustomerInFile(sender);
    updateCustomerInFile(&receiver);

    Transaction txnSender, txnReceiver;
    time_t now;
    char datetime[20];
    time(&now);
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));

    txnSender.accNo = sender->accNo;
    sprintf(txnSender.type, "TRANSFER_OUT to %d", receiver.accNo);
    txnSender.amount = amount;
    strcpy(txnSender.timestamp, datetime);

    txnReceiver.accNo = toAccount;
    sprintf(txnReceiver.type, "TRANSFER_IN from %d", sender->accNo);
    txnReceiver.amount = amount;
    strcpy(txnReceiver.timestamp, datetime);

    logTransaction(&txnSender);
    logTransaction(&txnReceiver);

    printf("\nTransfer successful. \nAvailable Balance: %.2lf\n", sender->balance);

    printf("\nPress Enter to continue...");
    getchar();
}