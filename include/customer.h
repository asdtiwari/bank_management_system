#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    int accNo;
    char name[50];
    char password[20];
    double balance;
    char mobile[15];
    char email[50];
} Customer;

void customerMenu(int accNo);
void viewBalance(Customer *customer);
void deposit(Customer *customer);
void withdraw(Customer *customer);
void transfer(Customer *sender);
void viewTransaction(Customer *customer);

#endif