#ifndef AUTH_H
#define AUTH_H

#include "customer.h"
#include "role.h"

Role authenticate(long int accNo, const char *password);
void loginScreen();

#endif