#define FMT_HEADER_ONLY
#include <iostream>
#include <string>
#include <vector>
#include "PPass.h"
#include "Decryption.h"
#include "Encryption.h"
#include "Password.h"
#include "Utilities.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <random>

/*  
* 
DECRYPTED
gugol|haslo1|gmail
gugo2|haslo2|gmail
*/


int main() {


    PasswordPass* ppass = launch();
    simulateApp(ppass);
        
    return 0;
}
