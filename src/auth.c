#include <string.h>
#include "auth.h"
#include "file_handler.h"

#define ADMIN_ACCNO 9999
#define ADMIN_PASSWORD "benjo234"

// Authenticate and return Role
Role authenticate(int accNo, const char *password) {
    if(accNo == ADMIN_ACCNO && strcmp(password, ADMIN_PASSWORD) == 0) {
        return ROLE_ADMIN;
    }

    Customer customer;
    if(loadCustomerFromFile(accNo, &customer)) {
        if(strcmp(password, customer.password) == 0) {
            return ROLE_CUSTOMER;
        }
    }
    
    return ROLE_INVALID;
}