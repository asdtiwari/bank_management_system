#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "file_handler.h"
#include "transaction.h"
#include "utils.h"

void viewBalance(Customer *customer) {
    system("cls");

    printHeader("Account Information");
    
    printf("\n%-15s: %.2lf\n", "Current Balance", customer->balance);

    refreshScreenMessage("");
}

void deposit(Customer *customer) {
    system("cls");

    printHeader("Deposit Window");

    double amount; 
    time_t now;
    char datetime[20];
    Transaction txn;

    printf("\nEnter amount to deposit: ");
    if(scanf("%lf", &amount) == 0 || amount <= 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid amount.");
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

    printf("\nAmount deposited Successfully");

    refreshScreenMessage("");
}


void withdraw(Customer *customer) {
    system("cls");

    printHeader("Withdraw Window");

    double amount; 
    time_t now;
    char datetime[20];
    Transaction txn;

    printf("\nEnter amount to withdraw: ");
    if(scanf("%lf", &amount) == 0 || amount <= 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid amount.");
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

        printf("\nAmount withdrawn successfully!");
    } else {
        printf("\nInsufficient balance!\n");
    }

    refreshScreenMessage("");
}

void transfer(Customer *sender) {
    system("cls");

    printHeader("Transfer Window");

    long int toAccount;
    printf("\nEnter Reciever Account Number: ");
    if(scanf("%ld", &toAccount) == 0) {
        while(getchar() != '\n');
        refreshScreenMessage("Invalid Account number.");
    }
    while(getchar() != '\n');

    Customer receiver;

    if(!loadCustomerFromFile(toAccount, &receiver)) {
        printf("\nReciever account not found.\n");
        refreshScreenMessage("");
        return;
    }

    double amount;
    printf("\nEnter amount to transfer: ");
    while(scanf("%lf", &amount) == 0) {
        while(getchar() != '\n');
        printf("\nPlease enter valid amount: ");
    }
    while(getchar() != '\n');

    if(sender->balance < amount) {
        printf("\nInsufficient balance for transfer!");
        refreshScreenMessage("");
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
    sprintf(txnSender.type, "TRANSFER_OUT to %ld", receiver.accNo);
    txnSender.amount = amount;
    strcpy(txnSender.timestamp, datetime);

    txnReceiver.accNo = toAccount;
    sprintf(txnReceiver.type, "TRANSFER_IN from %ld", sender->accNo);
    txnReceiver.amount = amount;
    strcpy(txnReceiver.timestamp, datetime);

    logTransaction(&txnSender);
    logTransaction(&txnReceiver);

    printf("\nTransfer successful.\nAvailable Balance: %.2lf\n", sender->balance);

    refreshScreenMessage("");
}

void customerMenu(long int accNo) {
    int choice;
    Customer customer;

    if(!loadCustomerFromFile(accNo, &customer)) {
        refreshScreenMessage("Customer not found.Press ENTER to Continue");
        return;
    }

    while(1) {
        system("cls"); // Fresh screen every time

        printHeader("Customer Services");

        printf("1. View Balance\n");
        printf("2. Deposit Amount\n");
        printf("3. Withdraw Amount\n");
        printf("4. Money Transfer to A/C\n");
        printf("5. View Transaction History\n");
        printf("6. Exit Cusomter Menu\n");
        printf("\nEnter your choice: ");
        while(scanf("%d", &choice) == 0) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number: ");
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
                refreshScreenMessage("Exiting Customer Menu.");
                return;
            
            default:
                refreshScreenMessage("Invalid choice.");
        }
    }
}