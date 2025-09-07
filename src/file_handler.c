#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handler.h"

#define DATA_FILE "data/customers.dat"

int saveCustomerInFile(Customer *customer) {
    FILE *fp = fopen(DATA_FILE, "ab"); // ab stands append binary
    if(fp == NULL) return 0;

    fwrite(customer, sizeof(Customer), 1, fp);
    fclose(fp);
    return 1;
}

int loadCustomerFromFile(int accNo, Customer *customer) {
    FILE *fp = fopen(DATA_FILE, "rb"); // rb stands for read binary
    if(fp == NULL) return 0;

    while(fread(customer, sizeof(Customer), 1, fp)) {
        if(customer->accNo == accNo) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int updateCustomerInFile(Customer *customer) {
    FILE *fp = fopen(DATA_FILE, "r+b"); // binary read and write but not create file if file is not present
    if(fp == NULL) return 0;

    Customer temp;
    while(fread(&temp, sizeof(Customer), 1, fp)) {
        if(temp.accNo == customer-> accNo) {
            fseek(fp, -(long)sizeof(Customer), SEEK_CUR);
            fwrite(customer, sizeof(Customer), 1, fp);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int deleteCustomerFromFile(int accNo) {
    FILE *fp = fopen("data/customers.dat", "rb");
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

    remove("data/customers.dat");
    rename("data/temp.dat", "data/customers.dat");

    return found;
}

int modifyCustomerInFile(Customer *customer) {
    FILE *fp = fopen("data/customers.dat", "r+b");
    if(fp == NULL) return 0;

    Customer temp;
    while(fread(&temp, sizeof(Customer), 1, fp)) {
        if(temp.accNo == customer->accNo) {
            fseek(fp, -(long)sizeof(Customer), SEEK_CUR);
            fwrite(customer, sizeof(Customer), 1, fp);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void viewAllCustomersFromFile() {
    system("cls"); // fresh screen

    FILE *fp = fopen("data/customers.dat", "rb");
    if(fp == NULL) {
        printf("\nNo customer records found.\n");
        return;
    }

    Customer customer;
    printf("\n===== All Customers =====\n");
    printf("%10s | %-25s | %-12s | %-25s\n\n", "Acc No", "Name", "Mobile", "Email");
    while(fread(&customer, sizeof(Customer), 1, fp)) {
        printf("%10d | %-25s | %-12s | %-25s\n", customer.accNo, customer.name, customer.mobile, customer.email);
    }

    fclose(fp);

    printf("\nPress Enter to continue...");
    getchar();
}

void viewBankStatisticsFromFile() {
    system("cls"); // fresh screen

    FILE *fp = fopen("data/customers.dat", "rb");
    if(fp == NULL) {
        printf("\nNo customer records found.\n");
        return;
    }

    Customer customer;
    int totalCustomers = 0;
    double totalBanlance = 0;

    while(fread(&customer, sizeof(Customer), 1, fp)) {
        ++totalCustomers;
        totalBanlance += customer.balance;
    }

    fclose(fp);

    printf("\n===== Bank Statistics =====\n");
    printf("Total Customers : %d\n", totalCustomers);
    printf("Total Bank Balance : %.2lf\n", totalBanlance);

    printf("\nPress Enter to continue...");
    getchar();
}