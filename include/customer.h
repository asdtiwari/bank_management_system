#ifndef CUSTOMER_H
#define CUSTOMER_H

void customerMenu(int accNo);
void deposit(int accNo, double amount);
void withdraw(int accNo, double amount);
void transfer(int fromAcc, int toAcc, double amount);
void viewTransaction(int accNo);

#endif