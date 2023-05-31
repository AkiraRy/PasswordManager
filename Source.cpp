#define FMT_HEADER_ONLY
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include "Utilities.h"

/*
* finish delete password
* finish mechanism to choose personal color
*/


int main() {
    PasswordPass* ppass = launch();
    simulateApp(ppass);
        
    return 0;
}
