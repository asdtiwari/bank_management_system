#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
	int accNo;
	double amount;
	char type[10]; // "CREDTI", "DEBIT", "TRANSFER"
	char timestamp[30];
} Transaction;

void logTransaction(Transaction t);
void showTransactionHistory(int accNo);

#endif