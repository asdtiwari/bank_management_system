#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
#include "customer.h"

#define TRANSACTION_FILE "data/transactions.dat"

int logTransaction(Transaction *txn) {
    FILE *fp = fopen(TRANSACTION_FILE, "ab");
    if(fp == NULL) return 0;

    fwrite(txn, sizeof(Transaction), 1, fp);
    fclose(fp);
    return 1;
}

int viewTransactions(int accNo) {
    system("cls");
    
    FILE *fp = fopen(TRANSACTION_FILE, "rb");
    if(fp == NULL) {
        printf("No transaction history found. \n");
        return 0;
    }

    Transaction txn;
    int found = 0;
    printf("\n--- Transaction History ---\n");
    printf("%-20s | %-30s | %-20s\n", "Date Time", "Type", "Amount");
    while(fread(&txn, sizeof(Transaction), 1, fp)) {
        if(txn.accNo == accNo) {
            printf("%-20s | %-30s | %-20.2lf\n", txn.timestamp, txn.type, txn.amount);
            found = 1;
        }
    }

    if(!found) {
        printf("No transactions for account no %d.\n", accNo);
    }

    fclose(fp);

    printf("\nPress Enter to continue...");
    getchar();

    return found;
}

int deleteCustomerTransaction(int accNo) {
    FILE *fp = fopen(TRANSACTION_FILE, "rb");
    FILE *tempFp = fopen("data/temp.dat", "wb");

    if(fp == NULL || tempFp == NULL) {
        if(fp == NULL) fclose(fp);
        if(tempFp == NULL) fclose(tempFp);
        return 0;
    }

    Customer customer;
    int found = 0;

    while(fread((&customer), sizeof(Customer), 1, fp)) {
        if(customer.accNo == accNo) {
            found = 1;
            continue;
        }
        fwrite(&customer, sizeof(Customer), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    remove(TRANSACTION_FILE);
    rename("data/temp.dat", TRANSACTION_FILE);

    return found;
}