#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "customer.h"

int saveCustomerInFile(Customer *customer);
int loadCustomerFromFile(long int accNo, Customer *customer);
int updateCustomerInFile(Customer *customer);
int deleteCustomerFromFile(long int accNo);
int modifyCustomerInFile(Customer *customer);
void viewAllCustomersFromFile();
void viewBankStatisticsFromFile();

#endif