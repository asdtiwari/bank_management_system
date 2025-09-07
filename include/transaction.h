#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <time.h>

typedef struct {
	int accNo;
	char type[30]; // "CREDTI", "DEBIT", "TRANSFER_IN [acNo]", "TRANSFER_OUT [acNo]"
	double amount;
	char timestamp[30];
} Transaction;

int logTransaction(Transaction *txn);
int viewTransactions(int accNo);
int deleteCustomerTransaction(int accNo);

#endif