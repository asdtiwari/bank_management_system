#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "customer.h"

int saveCustomerInFile(Customer *customer);
int loadCustomerFromFile(int accNo, Customer *customer);
int updateCustomerInFile(Customer *customer);
int deleteCustomerFromFile(int accNo);
int modifyCustomerInFile(Customer *customer);
void viewAllCustomersFromFile();
void viewBankStatisticsFromFile();

#endif