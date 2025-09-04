#ifndef UTILS_H
#define UTILS_H

int login();
void maskPassword(char *password);
char* getTimeStamp();
void encryptPassword(char *password);
int validateAmount(double amount);

#endif