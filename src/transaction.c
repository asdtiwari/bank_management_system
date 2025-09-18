#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
#include "customer.h"
#include "utils.h"

#define TRANSACTION_FILE "data/transactions.dat"

int logTransaction(Transaction *txn) {
    FILE *fp = fopen(TRANSACTION_FILE, "ab");
    if(fp == NULL) return 0;

    fwrite(txn, sizeof(Transaction), 1, fp);
    fclose(fp);
    return 1;
}

int viewTransactions(long int accNo) {
    system("cls");

    printHeader("Transactions History");
    
    FILE *fp = fopen(TRANSACTION_FILE, "rb");
    if(fp == NULL) {
        refreshScreenMessage("No transaction history found.");
        return 0;
    }

    Transaction txn;
    int found = 0;
    char* format = "%-10s | %-20s | %-30s | %-20s\n";
    printf(format, "Account No", "Date Time", "Type", "Amount");

    while(fread(&txn, sizeof(Transaction), 1, fp)) {
        if(accNo == 0 || txn.accNo == accNo) { // accNo == 0 means admin want to see all transaction
            printf("%-10ld | %-20s | %-30s | %-20.2lf\n", txn.accNo, txn.timestamp, txn.type, txn.amount);
            found = 1;
        }
    }

    if(accNo != 0 && !found) {
        printf("No transactions for account no %ld.\n", accNo);
    } else if(!found) {
        printf("No transaction is found in your bank.\n");
    }

    fclose(fp);

    refreshScreenMessage("");

    return found;
}

void viewAllTransactions() {
    viewTransactions(0); // 0 means everyone's account
}

int deleteCustomerTransaction(long int accNo) {
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