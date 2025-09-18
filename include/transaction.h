#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <time.h>

typedef struct {
	long int accNo;
	char type[30]; // "CREDTI", "DEBIT", "TRANSFER_IN", "TRANSFER_OUT"
	double amount;
	char timestamp[30];
} Transaction;

int logTransaction(Transaction *txn);
int viewTransactions(long int accNo);
void viewAllTransactions();
int deleteCustomerTransaction(long int accNo);

#endif