#define FMT_HEADER_ONLY
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include "Utilities.h"

int main() {
    PasswordPass* ppass = launch();
    simulateApp(ppass);
        
    return 0;
}
