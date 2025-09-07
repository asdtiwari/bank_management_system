#ifndef AUTH_H
#define AUTH_H

#include "customer.h"
#include "role.h"

Role authenticate(int accNo, const char *password);

#endif